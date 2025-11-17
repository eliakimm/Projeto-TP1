#include "controladoria.hpp"
#include <iostream>
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

// ==================== Pessoal ====================
void CntrApresentacaoPessoal::executar(const Email& email) {
    menu(email);
}

// Menu que recebe email do usuario autenticado e permite self-service
void CntrApresentacaoPessoal::menu(const Email& email) {
    int opcao;
    do {
        cout << "==========================================\n"
                  << "               Menu Pessoal               \n"
                  << "==========================================\n"
                  << "[1] - Criar usuario (Gerente)\n"
                  << "[2] - Ler usuario (Gerente)\n"
                  << "[3] - Editar usuario (Gerente)\n"
                  << "[4] - Excluir usuario (Gerente)\n"
                  << "[5] - Criar hospede\n"
                  << "[6] - Ler hospede\n"
                  << "[7] - Editar hospede\n"
                  << "[8] - Excluir hospede\n"
                  << "[9] - Listar hospedes\n"
                  << "[10] - Ver minha conta\n"
                  << "[11] - Editar minha conta\n"
                  << "[12] - Excluir minha conta\n"
                  << "[0] - Voltar\n"
                  << "==========================================\n"
                  << "-> Escolha: ";
        string line;
        getline(cin, line);
        try { opcao = stoi(line); } catch(...) { opcao = -1; }
        switch(opcao) {
            case 1: criarUsuario(); break;
            case 2: lerUsuario(); break;
            case 3: editarUsuario(); break;
            case 4: excluirUsuario(); break;
            case 5: criarHospede(); break;
            case 6: lerHospede(); break;
            case 7: editarHospede(); break;
            case 8: excluirHospede(); break;
            case 9: listarHospedes(); break;
            case 10: verMinhaConta(email); break;
            case 11: editarMinhaConta(email); break;
            case 12: excluirMinhaConta(email); break;
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
        cout << "Usuário criado!\n";
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
    if (servico->editarUsuario(g)) cout << "~[Usuário atualizado!] ~\n";
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

void CntrApresentacaoGerenciamento::menu(const Email&) {
    int opcao;
    do {
        cout << "==========================================\n"
                  << "            Menu Gerenciamento            \n"
                  << "==========================================\n"
                  << "[1] - Cadastrar hotel\n"
                  << "[2] - Listar hoteis\n"
                  << "[3] - Cadastrar quarto\n"
                  << "[4] - Listar quartos\n"
                  << "[0] - Voltar\n"
                  << "==========================================\n"
                  << "-> Escolha: ";
        string line;
        getline(cin, line);
        try { opcao = stoi(line); } catch(...) { opcao = -1; }
        switch(opcao) {
            case 1: cadastrarHotel(); break;
            case 2: listarHoteis(); break;
            case 3: cadastrarQuarto(); break;
            case 4: listarQuartos(); break;
        }
    } while(opcao != 0);
}

void CntrApresentacaoGerenciamento::cadastrarHotel() {
    string nomeStr, endStr, telStr, codStr;
    cout << "Nome: "; getline(cin, nomeStr);
    cout << "Endereco: "; getline(cin, endStr);
    cout << "Telefone: "; getline(cin, telStr);
    cout << "Codigo: "; getline(cin, codStr);
    Hotel h{Codigo(codStr), Nome(nomeStr), Endereco(endStr), Telefone(telStr)};
    if (servico->criarHotel(h)) cout << "~ [Hotel cadastrado!] ~\n";
    else cout << "~ [Falha ao cadastrar] ~\n";
}

void CntrApresentacaoGerenciamento::listarHoteis() {
    auto lista = servico->listarHoteis();
    for (auto& h : lista) h.exibirTudo();
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
                  << "[4] - Ler reserva\n"
                  << "[5] - Editar reserva\n"
                  << "[6] - Excluir reserva\n"
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
            case 4: lerReserva(); break;
            case 5: editarReserva(); break;
            case 6: excluirReserva(); break;
        }
    } while(opcao != 0);
}

void CntrApresentacaoReserva::criarReserva(const Email& email) {
    string nomeStr, endStr, cartaoStr, chegadaStr, partidaStr, codStr;
    cout << "Nome: "; getline(cin, nomeStr);
    cout << "Endereco: "; getline(cin, endStr);
    cout << "Cartao: "; getline(cin, cartaoStr);
    cout << "Data chegada (DD/MM/AAAA): "; getline(cin, chegadaStr);
    cout << "Data partida (DD/MM/AAAA): "; getline(cin, partidaStr);
    cout << "Codigo reserva: "; getline(cin, codStr);

    Hospede h(Nome(nomeStr), email, Endereco(endStr), Cartao(cartaoStr));
    Reserva r;
    r.setHospede(&h);
    r.setDatas(Data(chegadaStr), Data(partidaStr));
    r.setCodigo(Codigo(codStr));

    if (servico->criarReserva(h, r)) cout << "~ [Reserva criada!] ~\n";
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
        r.exibirTudo();
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
