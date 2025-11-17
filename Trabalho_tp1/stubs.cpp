#include <iostream>
#include "stubs.hpp"

StubAutenticacao::StubAutenticacao() : containerGerentes(nullptr) {
    // Container sera definido via setContainer
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
bool StubPessoal::excluirUsuario(const Email& e) { return containerGerentes.remover(e); }

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
std::vector<Hospede> StubPessoal::listarHospedes() { return containerHospedes.listarTodos(); }

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
    return container.adicionarQuarto(cod, q);
}

bool StubGerenciamento::lerQuarto(const Codigo& cod, Quarto& q) {
    auto lista = container.listarQuartos(cod);
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
            atualizado.setDescricao(q.getDescricao());
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

std::vector<Hotel> StubGerenciamento::listarHoteis() { return container.listarHoteis(); }
std::vector<Quarto> StubGerenciamento::listarQuartos(Codigo cod) { return container.listarQuartos(cod); }

bool StubReserva::criarReserva(const Hospede& hospede, const Reserva& reserva) {
    if (reserva.getHospede() != &hospede) return false;
    return container.adicionar(reserva);
}
bool StubReserva::cancelarReserva(const Codigo& cod) { return container.remover(cod); }
std::vector<Reserva> StubReserva::listarReservas(Email e) { return container.listarPorEmail(e); }

bool StubReserva::lerReserva(Reserva& r) {
    return container.buscarReserva(r.getCodigo(), r);
}

bool StubReserva::editarReserva(const Reserva& r) {
    return container.atualizarReserva(r);
}

bool StubReserva::excluirReserva(const Codigo& cod) {
    return container.remover(cod);
}
