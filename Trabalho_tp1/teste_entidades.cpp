#include "entidades.hpp"
#include <iostream>

using namespace std;

int runGerente(){
    Nome nome;
    Email email;
    Ramal ramal;
    Senha senha;

    string n;
    string e;
    string r;
    string s;

    cout << "Digite seu nome (5-20 letras):" << endl;
    getline(cin, n);

    cout << "Digite seu email:" << endl;
    getline(cin, e);

    cout << "Digite o numero do ramal (00-50):" << endl;
    getline(cin, r);

    cout << "Digite sua senha:" << endl;
    getline(cin, s);

    try{
        nome.setValor(n);
        email.setValor(e);
        ramal.setValor(r);
        senha.setValor(s);

        Gerente gerente(nome, email, ramal, senha);

        system("cls");
        cout << "DADOS DO GERENTE:" << endl;
        cout << "Nome: " << gerente.getNome().getValor() << endl;
        cout << "E-mail: " << gerente.getEmail().getValor() << endl;
        cout << "Nº do Ramal:" << gerente.getRamal().getValor() << endl;

    }catch(invalid_argument &excp){
        cout << "ERRO: " << excp.what() << endl;
    }

    return 0;
}

int runHospede(){
    Nome nome;
    Email email;
    Endereco endereco;
    Cartao cartao;

    string n;
    string e;
    string r;
    string s;

    cout << "Digite seu nome (5-20 letras):" << endl;
    getline(cin, n);

    cout << "Digite seu email:" << endl;
    getline(cin, e);

    cout << "Digite seu endereço:" << endl;
    getline(cin, r);

    cout << "Digite os numeros do seu cartão:" << endl;
    getline(cin, s);

    try{
        nome.setValor(n);
        email.setValor(e);
        endereco.setValor(r);
        cartao.setValor(s);

        Hospede hospede(nome, email, endereco, cartao);

        system("cls");
        cout << "DADOS DO Hóspede:" << endl;
        cout << "Nome: " << hospede.getNome().getValor() << endl;
        cout << "E-mail: " << hospede.getEmail().getValor() << endl;
        cout << "Endereço: " << hospede.getEndereco().getValor() << endl;
        cout << "Nº do Cartão:" << hospede.getCartao().getValor() << endl;

    }catch(invalid_argument &excp){
        cout << "ERRO: " << excp.what() << endl;
    }

    return 0;
}


int runReserva() {
    // Hospede
    Nome nome;
    Email email;
    Endereco endereco;
    Cartao cartao;

    // Quarto
    Numero num;
    Capacidade cap;
    Dinheiro din;
    Ramal ramal;

    // Reserva
    Data chegada;
    Data partida;
    Codigo codigo;

    // Dados simulados
    string n = "Eliakim Silva";
    string e = "eliakim@gmail.com";
    string r = "Samambaia Norte";
    string s = "5502096099523276";

    string nn = "002";
    int ee = 2;
    double rr = 180.0;
    string ss = "02";

    string nnn = "02-OUT-2025";
    string eee = "04-OUT-2025";
    string rrr = "abcde67890";

    try {
        // Setando valores
        nome.setValor(n);
        email.setValor(e);
        endereco.setValor(r);
        cartao.setValor(s);

        num.setValor(nn);
        cap.setValor(ee);
        din.setValor(rr);
        ramal.setValor(ss);

        chegada.setValor(nnn);
        partida.setValor(eee);
        codigo.setValor(rrr);

        // Criando objetos
        Hospede hospede(nome, email, endereco, cartao);
        Quarto quarto(num, cap, din, ramal);
        Reserva reserva;

        // Associando dados à reserva
        reserva.setHospede(&hospede);
        reserva.setQuarto(&quarto);
        reserva.setCodigo(codigo);
        reserva.setDatas(chegada, partida); // já valida e calcula valor

        // Exibindo dados
        system("cls");
        //cout << "DADOS da Reserva:" << endl;
        reserva.exibir_reserva();

    } catch (invalid_argument& excp) {
        system("cls");
        cout << "ERRO: " << excp.what() << endl;
    }

    return 0;
}
