#include <iostream>
#include "stubs.hpp"

StubAutenticacao::StubAutenticacao() : containerGerentes(nullptr) {
    // Container sera definido via setContainer
}

StubPessoal::StubPessoal() {
    // Semente de usuario de teste: gerente
    try {
        Nome n("Teste Gerente");
        Email e("teste@hotel.com");
        Ramal r("01");
        // Senha de 5 caracteres que respeita as regras: contem maiuscula, minuscula, digito e caractere especial
        Senha s("A1b!2");
        Gerente g(n, e, r, s);
        containerGerentes.adicionar(g);
    } catch (...) {
        // se ocorrer qualquer validacao, nao falhamos — util apenas para testes locais
    }

    // Semente de hospede de teste
    try {
        Nome nh("Hospede Teste");
        Email eh("hospede@teste.com");
        Endereco end("Rua Teste, 123");
        // Numero de cartao de 16 digitos (utilizar um cartao de teste que passe no algoritmo de Luhn)
        Cartao c("4532015112830366");
        Hospede h(nh, eh, end, c);
        containerHospedes.adicionar(h);
    } catch (...) {
        // ignore
    }
}

bool StubAutenticacao::autenticar(const Email& email, const Senha& senha) {
    if (!containerGerentes) return false;
    Gerente* g = containerGerentes->buscar(email);
    if (!g) return false;
    return g->getSenha().getValor() == senha.getValor();
}

bool StubPessoal::criarUsuario(const Gerente& g) { return containerGerentes.adicionar(g); }
bool StubPessoal::lerUsuario(Gerente& g) {
    Gerente* encontrado = containerGerentes.buscar(g.getEmail());
    if (!encontrado) return false;
    g = *encontrado;
    return true;
}
bool StubPessoal::editarUsuario(const Gerente& g) {
    Gerente* existente = containerGerentes.buscar(g.getEmail());
    if (!existente) return false;
    Gerente atualizado = *existente; // preserva o email (PK)
    atualizado.setNome(g.getNome());
    atualizado.setRamal(g.getRamal());
    atualizado.setSenha(g.getSenha());
        return containerGerentes.atualizar(atualizado);
}


bool StubPessoal::criarHospede(const Hospede& h) { return containerHospedes.adicionar(h); }
bool StubPessoal::lerHospede(Hospede& h) {
    Hospede* encontrado = containerHospedes.buscar(h.getEmail());
    if (!encontrado) return false;
    h = *encontrado;
    return true;
}
bool StubPessoal::editarHospede(const Hospede& h) {
    Hospede* existente = containerHospedes.buscar(h.getEmail());
    if (!existente) return false;
    Hospede atualizado = *existente; // preserva o email (PK)
    atualizado.setNome(h.getNome());
    atualizado.setEndereco(h.getEndereco());
    atualizado.setCartao(h.getCartao());
    return containerHospedes.atualizar(atualizado);
}
bool StubPessoal::excluirHospede(const Email& e) {
    if (reservaContainer) reservaContainer->removerPorHospede(e);
    return containerHospedes.remover(e);
}

// Novo: remover gerente em cascata: remover hoteis associados e suas reservas
// Retorna false se a remocao do gerente falhar por qualquer motivo.
bool StubPessoal::excluirUsuario(const Email& e) {
    // se tivermos um container de hoteis, remover os hoteis e reservas associadas
    if (hotelContainer) {
        auto removidos = hotelContainer->removerPorGerente(e);
        if (reservaContainer) {
            for (const auto &cod : removidos) {
                reservaContainer->removerPorHotel(cod);
            }
        }
    }
        return containerGerentes.remover(e);
}
vector<Hospede> StubPessoal::listarHospedes() { return containerHospedes.listarTodos(); }

bool StubGerenciamento::criarHotel(const Hotel& h) { return container.adicionarHotel(h); }
bool StubGerenciamento::lerHotel(Hotel& h) {
    Hotel* encontrado = container.buscarHotel(h.getCodigo());
    if (!encontrado) return false;
    h = *encontrado;
    return true;
}
bool StubGerenciamento::editarHotel(const Hotel& h) {
    Hotel* existente = container.buscarHotel(h.getCodigo());
    if (!existente) return false;
    Hotel atualizado = *existente; // preserva o codigo (PK)
    atualizado.setNome(h.getNome());
    atualizado.setEndereco(h.getEndereco());
    atualizado.setTelefone(h.getTelefone());
    return container.atualizarHotel(atualizado);
}
bool StubGerenciamento::excluirHotel(const Codigo& cod) {
    if (reservaContainer) reservaContainer->removerPorHotel(cod);
    return container.removerHotel(cod);
}

bool StubGerenciamento::criarQuarto(const Codigo& cod, const Quarto& q) {
    // Fazer uma copia mutavel para possivel ajuste de ramal
    Quarto qc = q;
    // Se conhecemos o hotel e o gerente responsavel, usar o ramal do gerente
    Hotel* h = container.buscarHotel(cod);
    if (h && gerentesContainer) {
        Email gerenteEm = h->getGerenteEmail();
        if (!gerenteEm.getValor().empty()) {
            Gerente* g = gerentesContainer->buscar(gerenteEm);
            if (g) {
                try { qc.setRamal(g->getRamal()); } catch(...) { /* ignorar validacoes */ }
            }
        }
    }
    return container.adicionarQuarto(cod, qc);
}

bool StubGerenciamento::lerQuarto(const Codigo& cod, Quarto& q) {
    auto lista = container.listarQuartos(cod);
    // se numero nao for fornecido em 'q', retornamos o primeiro quarto existente
    if (q.getNumero().getValor().empty()) {
        if (!lista.empty()) {
            q = lista.front();
            return true;
        }
        return false;
    }
    for (auto& item : lista) {
        if (item.getNumero().getValor() == q.getNumero().getValor()) {
            q = item;
            return true;
        }
    }
    return false;
}

bool StubGerenciamento::editarQuarto(const Codigo& cod, const Quarto& q) {
    auto lista = container.listarQuartos(cod);
    for (auto& item : lista) {
        if (item.getNumero().getValor() == q.getNumero().getValor()) {
            Quarto atualizado = item;
            atualizado.setCapacidade(q.getCapacidade());
            atualizado.setValor(q.getValor());
            atualizado.setRamal(q.getRamal());
            return container.editarQuarto(cod, atualizado);
        }
    }
    return false;
}

bool StubGerenciamento::excluirQuarto(const Codigo& cod, const Numero& num) {
    return container.removerQuarto(cod, num);
}

vector<Hotel> StubGerenciamento::listarHoteis() { return container.listarHoteis(); }
vector<Quarto> StubGerenciamento::listarQuartos(Codigo cod) { return container.listarQuartos(cod); }

bool StubGerenciamento::lerGerente(Gerente& g) {
    if (!gerentesContainer) return false;
    Gerente* encontrado = gerentesContainer->buscar(g.getEmail());
    if (!encontrado) return false;
    g = *encontrado;
    return true;
}

bool StubReserva::criarReserva(const Hospede& hospede, const Reserva& reserva) {
    // Aceitamos reservas quando o email do hospede na reserva bate com o hospede informado.
    if (!reserva.getHospede()) return false;
    if (reserva.getHospede()->getEmail().getValor() != hospede.getEmail().getValor()) return false;

    // Se tivermos um container de hospedes, tentamos apontar a reserva para o hospede persistente
    Reserva rcopy = reserva;
    if (hospedesContainer) {
        Hospede* encontrado = hospedesContainer->buscar(reserva.getHospede()->getEmail());
        if (!encontrado) {
            // hospede nao existe no container: adicionamos uma copia persistente
            hospedesContainer->adicionar(hospede);
            encontrado = hospedesContainer->buscar(hospede.getEmail());
        }
        if (encontrado) rcopy.setHospede(encontrado);
    }

    // Se possuirmos o container de hoteis, apontamos o hotel/quarto para as instancias persistentes
    if (hoteisContainer) {
        if (reserva.getHotel()) {
            Hotel* h = hoteisContainer->buscarHotel(reserva.getHotel()->getCodigo());
            if (h) rcopy.setHotel(h);
        }
        if (reserva.getQuarto() && reserva.getHotel()) {
            Quarto* q = hoteisContainer->buscarQuarto(reserva.getHotel()->getCodigo(), reserva.getQuarto()->getNumero());
            if (q) rcopy.setQuarto(q);
        }
    }

    return container.adicionar(rcopy);
}
bool StubReserva::cancelarReserva(const Codigo& cod) { return container.remover(cod); }
vector<Reserva> StubReserva::listarReservas(Email e) { return container.listarPorEmail(e); }

bool StubReserva::lerReserva(Reserva& r) {
    return container.buscarReserva(r.getCodigo(), r);
}

bool StubReserva::editarReserva(const Reserva& r) {
    return container.atualizarReserva(r);
}

bool StubReserva::excluirReserva(const Codigo& cod) {
    return container.remover(cod);
}
