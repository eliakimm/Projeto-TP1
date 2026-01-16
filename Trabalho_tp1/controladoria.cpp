#include "controladoria.hpp"
#include <iostream>
#include "pricing.hpp"
using namespace std;

// Removidas implementacoes obsoletas de 'Controladoria' (merge incorreto).
// O arquivo abaixo implementa as classes de apresentacao (CntrApresentacao*).
bool CntrApresentacaoAutenticacao::autenticarGerente() {
    string emailStr, senhaStr, line;
    cout << "\n=== Login Gerente ===\n";
    cout << "Email: ";
    getline(cin, emailStr);
    cout << "Senha: ";
    getline(cin, senhaStr);

    try {
        Email email(emailStr);
        Senha senha(senhaStr);
        if (servico && servico->autenticar(email, senha)) {
            cout << "Autenticado com sucesso!\n";
            return true;
        }
    } catch (const invalid_argument& e) {
        cerr << "Erro: " << e.what() << '\n';
    }
    cout << "Falha na autenticacao.\n";
    return false;
}

void CntrApresentacaoPessoal::executar(const Email& email) {
    menu(email);
}

// ==================== Pessoal ====================
void CntrApresentacaoPessoal::menu(const Email& email) {
    int opcao;
    do {
        cout << "==========================================\n"
                  << "               Menu Pessoal               \n"
                  << "==========================================\n"
                  << "[1] - Ver minha conta\n"
                  << "[2] - Editar minha conta\n"
                  << "[3] - Excluir minha conta\n"
                  << "[0] - Voltar\n"
                  << "==========================================\n"
                  << "-> Escolha: ";
        string line;
        getline(cin, line);
        try { opcao = stoi(line); } catch(...) { opcao = -1; }
        switch(opcao) {
            case 1: verMinhaConta(email); break;
            case 2: editarMinhaConta(email); break;
            case 3: excluirMinhaConta(email); break;
        }
    } while(opcao != 0);
}

void CntrApresentacaoPessoal::criarUsuario() {
    string nomeStr, emailStr, ramalStr, senhaStr;
    cout << "Nome: "; getline(cin, nomeStr);
    cout << "Email: "; getline(cin, emailStr);
    cout << "Ramal: "; getline(cin, ramalStr);
    cout << "Senha: "; getline(cin, senhaStr);
    Gerente g{Nome(nomeStr), Email(emailStr), Ramal(ramalStr), Senha(senhaStr)};
    if (servico->criarUsuario(g)) {
        cout << "Usuario criado!\n";
    }

}


void CntrApresentacaoPessoal::lerUsuario() {
    string emailStr;
    cout << "Email: "; getline(cin, emailStr);
    Gerente g; // criar vazio e setar apenas email para evitar validacoes desnecessarias
    g.setEmail(Email(emailStr));
    if (servico->lerUsuario(g)) g.exibirTudo();
    else cout << "Usuario nao encontrado.\n";
}

void CntrApresentacaoPessoal::editarUsuario() {
    string nomeStr, emailStr, ramalStr, senhaStr;
    cout << "Email: "; getline(cin, emailStr);
    cout << "Novo nome: "; getline(cin, nomeStr);
    cout << "Novo ramal: "; getline(cin, ramalStr);
    cout << "Nova senha: "; getline(cin, senhaStr);
    Gerente g{Nome(nomeStr), Email(emailStr), Ramal(ramalStr), Senha(senhaStr)};
    if (servico->editarUsuario(g)) cout << "~[Usuario atualizado!] ~\n";
    else cout << "~ [Falha ao atualizar] ~\n";
}

void CntrApresentacaoPessoal::excluirUsuario() {
    string emailStr;
    cout << "Email: "; getline(cin, emailStr);
    if (servico->excluirUsuario(Email(emailStr))) cout << "~ [Usuurio excluido!] ~\n";
    else cout << "~ [Falha ao excluir] ~\n";
}

void CntrApresentacaoPessoal::verMinhaConta(const Email& email) {
    Gerente g; g.setEmail(email);
    if (servico->lerUsuario(g)) g.exibirTudo();
    else cout << "~ [Conta nao encontrada] ~\n";
}

void CntrApresentacaoPessoal::editarMinhaConta(const Email& email) {
    string nomeStr, ramalStr, senhaStr;
    cout << "Novo nome: "; getline(cin, nomeStr);
    cout << "Novo ramal: "; getline(cin, ramalStr);
    cout << "Nova senha: "; getline(cin, senhaStr);
    Gerente g{Nome(nomeStr), email, Ramal(ramalStr), Senha(senhaStr)};
    if (servico->editarUsuario(g)) cout << "Conta atualizada!\n";
    else cout << "~ [Falha ao atualizar conta] ~\n";
}

void CntrApresentacaoPessoal::excluirMinhaConta(const Email& email) {
    if (servico->excluirUsuario(email)) cout << "~ [Sua conta foi excluida] ~\n";
    else cout << "~ [Falha ao excluir sua conta] ~\n";
}

    void CntrApresentacaoPessoal::criarHospede() {
        string nomeStr, emailStr, endStr, cartaoStr;
        cout << "Nome: "; getline(cin, nomeStr);
        cout << "Email: "; getline(cin, emailStr);
        cout << "Endereco: "; getline(cin, endStr);
        cout << "Cartao: "; getline(cin, cartaoStr);
        Hospede h{Nome(nomeStr), Email(emailStr), Endereco(endStr), Cartao(cartaoStr)};
        if (servico->criarHospede(h)) cout << "~[Hospede criado!]~\n";
        else cout << "~ [Falha ao criar] ~\n";
    }

    void CntrApresentacaoPessoal::lerHospede() {
        string emailStr;
        cout << "Email: "; getline(cin, emailStr);
        Hospede h(Nome(""), Email(emailStr), Endereco(""), Cartao(""));
        if (servico->lerHospede(h)) h.exibirTudo();
        else cout << "~ [Hospede nao encontrado] ~\n";
    }

    void CntrApresentacaoPessoal::editarHospede() {
        string nomeStr, emailStr, endStr, cartaoStr;
        cout << "Email: "; getline(cin, emailStr);
        cout << "Novo nome: "; getline(cin, nomeStr);
        cout << "Novo endereco: "; getline(cin, endStr);
        cout << "Novo cartao: "; getline(cin, cartaoStr);
        Hospede h{Nome(nomeStr), Email(emailStr), Endereco(endStr), Cartao(cartaoStr)};
        if (servico->editarHospede(h)) cout << "~ [Hospede atualizado!] ~\n";
        else cout << "~ [Falha ao atualizar] ~\n";
    }

    void CntrApresentacaoPessoal::excluirHospede() {
        string emailStr;
        cout << "Email: "; getline(cin, emailStr);
        if (servico->excluirHospede(Email(emailStr))) cout << "~ [Hospede excluido] ~\n";
        else cout << "~ [Falha ao excluir] ~\n";
    }

    void CntrApresentacaoPessoal::listarHospedes() {
        auto lista = servico->listarHospedes();
        if (lista.empty()) {
            cout << "Nenhum hospede cadastrado.\n";
            return;
        }
        for (auto& h : lista) h.exibirTudo();
    }

// ==================== Gerenciamento ====================
void CntrApresentacaoGerenciamento::executar(const Email& email) {
    menu(email);
}

void CntrApresentacaoGerenciamento::menu(const Email& email) {
    int opcao;
    do {
        cout << "==========================================\n"
                      << "            Menu Gerenciamento            \n"
                      << "==========================================\n"
                      << "[1] - Cadastrar hotel\n"
                      << "[2] - Listar hoteis\n"
                      << "[3] - Listar quartos\n"
                      << "[4] - Excluir hotel\n"
                      << "[0] - Voltar\n"
                      << "==========================================\n"
                      << "-> Escolha: ";
        string line;
        getline(cin, line);
        try { opcao = stoi(line); } catch(...) { opcao = -1; }
        switch(opcao) {
            case 1: cadastrarHotel(email); break;
            case 2: listarHoteis(); break;
            case 3: listarQuartos(); break;
            case 4: excluirHotel(email); break;
        }
    } while(opcao != 0);
}

void CntrApresentacaoGerenciamento::cadastrarHotel(const Email& gerenteEmail) {
    string nomeStr, endStr, telStr, codStr;
    cout << "Nome: "; getline(cin, nomeStr);
    cout << "Endereco: "; getline(cin, endStr);
    cout << "Telefone: "; getline(cin, telStr);
    cout << "Codigo: "; getline(cin, codStr);
    Hotel h{Codigo(codStr), Nome(nomeStr), Endereco(endStr), Telefone(telStr)};
    // associar o hotel ao gerente logado
    h.setGerenteEmail(gerenteEmail);
    if (servico->criarHotel(h)) cout << "~ [Hotel cadastrado!] ~\n";
    else cout << "~ [Falha ao cadastrar] ~\n";
}

void CntrApresentacaoGerenciamento::listarHoteis() {
    auto lista = servico->listarHoteis();
    for (auto& h : lista) {
        cout << "==========================================\n";
        cout << "              HOTEL:             \n";
        cout << "==========================================\n\n";
        h.exibirTudo();
    }
}

void CntrApresentacaoGerenciamento::cadastrarQuarto() {
    string codStr, numStr, capStr, valorStr, ramalStr;
    cout << "Codigo do hotel: "; getline(cin, codStr);
    cout << "Numero do quarto: "; getline(cin, numStr);
    cout << "Capacidade: "; getline(cin, capStr);
    cout << "Valor por dia: "; getline(cin, valorStr);
    cout << "Ramal: "; getline(cin, ramalStr);
    Quarto q{Numero(numStr), Capacidade(capStr), Dinheiro(valorStr), Ramal(ramalStr)};
    if (servico->criarQuarto(Codigo(codStr), q)) cout << "~ [Quarto cadastrado!] ~\n";
    else cout << "~ [Falha ao cadastrar] ~\n";
}

void CntrApresentacaoGerenciamento::listarQuartos() {
    string codStr;
    cout << "Codigo do hotel: "; getline(cin, codStr);
    auto lista = servico->listarQuartos(Codigo(codStr));
    for (auto& q : lista) q.exibirTudo();
}

void CntrApresentacaoGerenciamento::excluirHotel(const Email& gerenteEmail) {
    string codStr;
    cout << "Codigo do hotel a excluir: "; getline(cin, codStr);
    Hotel h; h.setCodigo(Codigo(codStr));
    if (!servico->lerHotel(h)) {
        cout << "Hotel nao encontrado.\n";
        return;
    }
    // verificar se gerente logado eh o proprietario
    if (h.getGerenteEmail().getValor() != gerenteEmail.getValor()) {
        cout << "Apenas o gerente proprietario pode excluir este hotel.\n";
        return;
    }
    if (servico->excluirHotel(Codigo(codStr))) cout << "~ [Hotel excluido!] ~\n";
    else cout << "~ [Falha ao excluir hotel] ~\n";
}

void CntrApresentacaoGerenciamento::lerQuarto() {
    string codStr, numStr;
    cout << "Codigo do hotel: "; getline(cin, codStr);
    cout << "Numero do quarto: "; getline(cin, numStr);
    Quarto q(Numero(numStr), Capacidade("1"), Dinheiro("0.01"), Ramal("00"));
    if (servico->lerQuarto(Codigo(codStr), q)) q.exibirTudo();
    else cout << "~ [Quarto nao encontrado] ~\n";
}

void CntrApresentacaoGerenciamento::editarQuarto() {
    string codStr, numStr, capStr, valorStr, ramalStr;
    cout << "Codigo do hotel: "; getline(cin, codStr);
    cout << "Numero do quarto (PK): "; getline(cin, numStr);
    cout << "Nova capacidade: "; getline(cin, capStr);
    cout << "Novo valor por dia: "; getline(cin, valorStr);
    cout << "Novo ramal: "; getline(cin, ramalStr);
    Quarto q{Numero(numStr), Capacidade(capStr), Dinheiro(valorStr), Ramal(ramalStr)};
    if (servico->editarQuarto(Codigo(codStr), q)) cout << "~ [Quarto atualizado!] ~\n";
    else cout << "~ [Falha ao atualizar quarto] ~\n";
}

void CntrApresentacaoGerenciamento::excluirQuarto() {
    string codStr, numStr;
    cout << "Codigo do hotel: "; getline(cin, codStr);
    cout << "Numero do quarto: "; getline(cin, numStr);
    if (servico->excluirQuarto(Codigo(codStr), Numero(numStr))) cout << "~ [Quarto excluido!] ~\n";
    else cout << "~ [Falha ao excluir quarto] ~\n";
}

// ==================== Reserva ====================
void CntrApresentacaoReserva::executar(const Email& email) {
    menu(email);
}

void CntrApresentacaoReserva::menu(const Email& email) {
    int opcao;
    do {
        cout << "==========================================\n"
                  << "               Menu Reserva               \n"
                  << "==========================================\n"
                  << "[1] - Criar reserva\n"
                  << "[2] - Cancelar reserva\n"
                  << "[3] - Listar reservas\n"
                  << "[4] - Editar reserva\n"
                  << "[5] - Ler reserva\n"
                  << "[0] - Voltar\n"
                  << "==========================================\n"
                  << "-> Escolha: ";
        string line;
        getline(cin, line);
        try { opcao = stoi(line); } catch(...) { opcao = -1; }
        switch(opcao) {
            case 1: criarReserva(email); break;
            case 2: cancelarReserva(); break;
            case 3: listarReservas(email); break;
            case 4: editarReserva(); break;
            case 5: lerReserva(); break;
        }
    } while(opcao != 0);
}

void CntrApresentacaoReserva::criarReserva(const Email& emailGerente) {
    // Obter dados do gerente logado
    // Criar Gerente vazio e setar apenas o email para buscar os dados persistentes
    Gerente gerente;
    gerente.setEmail(emailGerente);
    if (!servGerenciamento || !servGerenciamento->lerGerente(gerente)) {
        cout << "Erro ao obter dados do gerente. Abortando reserva.\n";
        cout << "Pressione ENTER para continuar...";
        string _tmp; getline(cin, _tmp);
        return;
    }

    // DEBUG: imprimir nome do gerente obtido para diagnosticar validacao de Nome
    try {
        cout << "[DEBUG] Nome do gerente obtido: '" << gerente.getNome().getValor() << "'\n";
    } catch (...) {
        cout << "[DEBUG] Nome do gerente obtido: (excecao ao acessar)\n";
    }

    // Fluxo de reserva: usar nome e email do gerente, pedir apenas endereco e cartao
    string endStr, cartaoStr, chegadaStr, partidaStr, codStr, codHotelStr, numQuartoStr;
    int capInt;

    cout << "Endereco: "; getline(cin, endStr);
    cout << "Cartao: "; getline(cin, cartaoStr);
    cout << "Codigo do hotel (verificacao sera feita): "; getline(cin, codHotelStr);

    // verificar se hotel existe
    Hotel htemp; htemp.setCodigo(Codigo(codHotelStr));
    if (!servGerenciamento || !servGerenciamento->lerHotel(htemp)) {
        cout << "Hotel nao encontrado. Abortando reserva.\n";
        cout << "Pressione ENTER para continuar...";
        string _tmp; getline(cin, _tmp);
        return;
    }

    cout << "Numero do quarto (3 digitos): "; getline(cin, numQuartoStr);
    cout << "Capacidade (1-4): "; cin >> capInt; cin.ignore();

    cout << "Data chegada (DD-MMM-AAAA, ex: 01-FEV-2025): "; getline(cin, chegadaStr);
    cout << "Data partida (DD-MMM-AAAA, ex: 04-FEV-2025): "; getline(cin, partidaStr);
    cout << "Codigo reserva (exatamente 10 caracteres: letras minusculas e digitos, ex: reserv00001): "; getline(cin, codStr);

    // criar hospede local com nome e email do gerente
    Hospede hosp; // evitar "most vexing parse" usando construtor padrao
    try {
        hosp = Hospede{gerente.getNome(), emailGerente, Endereco(endStr), Cartao(cartaoStr)};
    } catch (const std::invalid_argument &e) {
        cout << "Dados de hospede invalidos: " << e.what() << "\n";
        cout << "Abortando reserva. Pressione ENTER para continuar...";
        string _tmp; getline(cin, _tmp);
        return;
    }

    // montar quarto: se nao existir no hotel, criaremos via servGerenciamento
    Quarto q(Numero(numQuartoStr), Capacidade(to_string(capInt)), Dinheiro("0.01"), Ramal("00"));
    // atribuir valor baseado na capacidade (usando pricing.hpp)
    if (capInt < 1 || capInt > 4) capInt = 1;
    double preco = precoPorCapacidade(capInt);
    Dinheiro dval; dval.setValor(preco); q.setValor(dval);
    // definir ramal do quarto igual ao ramal do gerente logado, se disponivel
    try {
        q.setRamal(gerente.getRamal());
    } catch (...) {
        // se houver erro de validacao, mantemos o ramal default
    }

    // tentar ler quarto existente
    Quarto qcheck(Numero(numQuartoStr), Capacidade("1"), Dinheiro("0.01"), Ramal("00"));
    bool quartoExiste = servGerenciamento->lerQuarto(Codigo(codHotelStr), qcheck);
    if (!quartoExiste) {
        // criar quarto dinamicamente
        if (!servGerenciamento->criarQuarto(Codigo(codHotelStr), q)) {
            cout << "Falha ao criar quarto no sistema. Abortando.\n";
            cout << "Pressione ENTER para continuar...";
            string _tmp; getline(cin, _tmp);
            return;
        }
    } else {
        // usar dados existentes (principalmente o valor)
        q = qcheck;
    }

    // DEBUG: imprimir dados antes de criar Reserva
    cout << "[DEBUG] Tentando criar Reserva com:\nCodigo='" << codStr << "'\nChegada='" << chegadaStr << "'\nPartida='" << partidaStr << "'\n";

    Reserva r;
    r.setHospede(&hosp);
    try {
    // setamos hotel/quarto com objetos locais contendo informacoes corretas (cod, numero)
    Hotel hlocal(Codigo(codHotelStr), htemp.getNome(), htemp.getEndereco(), htemp.getTelefone());
        r.setHotel(&hlocal);
        r.setQuarto(&q);
        r.setDatas(Data(chegadaStr), Data(partidaStr));
        r.setCodigo(Codigo(codStr));
    } catch (const std::invalid_argument &e) {
        cout << "Erro ao validar campos da reserva: " << e.what() << "\n";
        cout << "Abortando reserva. Pressione ENTER para continuar...";
        string _tmp; getline(cin, _tmp);
        return;
    }

    if (servico->criarReserva(hosp, r)) cout << "~ [Reserva criada!] ~\n";
    else cout << "~ [Falha ao criar] ~\n";
}

void CntrApresentacaoReserva::cancelarReserva() {
    string codStr;
    cout << "Codigo da reserva: ";
    getline(cin, codStr);

    if (servico->cancelarReserva(Codigo(codStr))) {
        cout << "Reserva cancelada!\n";
    } else {
        cout << "Reserva nao encontrada.\n";
    }
}

void CntrApresentacaoReserva::listarReservas(const Email& email) {
    auto lista = servico->listarReservas(email);
    if (lista.empty()) {
        cout << "Nenhuma reserva encontrada para este email.\n";
        return;
    }
    for (auto& r : lista) {
        try {
            cout << "==========================================\n";
            cout << "                RESERVA:            \n";
            cout << "==========================================\n\n";
            r.exibirTudo();
        } catch (const std::exception &e) {
            cout << "Erro ao exibir reserva '" << r.getCodigo().getValor() << "': " << e.what() << "\n";
        }
    }
}

void CntrApresentacaoReserva::lerReserva() {
    string codStr;
    cout << "Codigo da reserva: "; getline(cin, codStr);
    Reserva r; r.setCodigo(Codigo(codStr));
    if (servico->lerReserva(r)) r.exibirTudo();
    else cout << "~ [Reserva nao encontrada] ~\n";
}

void CntrApresentacaoReserva::editarReserva() {
    string codStr, chegadaStr, partidaStr;
    cout << "Codigo da reserva: "; getline(cin, codStr);
    Reserva r; r.setCodigo(Codigo(codStr));
    if (!servico->lerReserva(r)) { cout << "Reserva nao encontrada.\n"; return; }
    cout << "Nova data chegada (DD/MM/AAAA): "; getline(cin, chegadaStr);
    cout << "Nova data partida (DD/MM/AAAA): "; getline(cin, partidaStr);
    r.setDatas(Data(chegadaStr), Data(partidaStr));
    if (servico->editarReserva(r)) cout << "~ [Reserva atualizada] ~\n";
    else cout << "Falha ao atualizar reserva (conflito ou invalido).\n";
}

void CntrApresentacaoReserva::excluirReserva() {
    string codStr;
    cout << "Codigo da reserva: "; getline(cin, codStr);
    if (servico->excluirReserva(Codigo(codStr))) cout << "~ [Reserva excluida!] ~\n";
    else cout << "~ [Falha ao excluir reserva] ~\n";
}
