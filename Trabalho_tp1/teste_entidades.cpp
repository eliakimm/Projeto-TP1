#include <iostream>
#include <string>
#include <vector>
#include "entidades.hpp"

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

        // Associando dados à reserva
        Reserva reserva(codigo, chegada, partida, &hospede, &quarto);

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


int runReserva2() {
    struct CasoTeste {
        string nome, email, endereco, cartao;
        string numeroQuarto, ramal;
        int capacidade;
        double diaria;
        string chegada, partida, codigo;
        string descricao;
    };

    vector<CasoTeste> testes = {
        {
            "Eliakim Silva", "eliakim@gmail.com", "Samambaia Norte", "5502096099523276",
            "002", "02", 2, 180.0,
            "02-OUT-2025", "04-OUT-2025", "abcde67890",
            "Caso válido"
        },
        {
            "Joao", "joaogmail.com", "Taguatinga@", "1234567890123456",
            "003", "03", 3, -200.0,
            "05-OUT-2025", "03-OUT-2025", "",
            "Varios campos invalidos"
        }
    };

    for (const auto& teste : testes) {
        vector<string> erros;
        system("cls");
        cout << "Testando: " << teste.descricao << endl;

        try {
            // Validação acumulada com valores exibidos
            Nome nome; try { nome.setValor(teste.nome); } catch (invalid_argument& e) { erros.push_back("Nome invalido : \"" + teste.nome + "\" | " + e.what()); }
            Email email; try { email.setValor(teste.email); } catch (invalid_argument& e) { erros.push_back("Email invalido : \"" + teste.email + "\" | " + e.what()); }
            Endereco endereco; try { endereco.setValor(teste.endereco); } catch (invalid_argument& e) { erros.push_back("Endereco invalido : \"" + teste.endereco + "\" | " + e.what()); }
            Cartao cartao; try { cartao.setValor(teste.cartao); } catch (invalid_argument& e) { erros.push_back("Cartao invalido : \"" + teste.cartao + "\" | " + e.what()); }

            Numero numero; try { numero.setValor(teste.numeroQuarto); } catch (invalid_argument& e) { erros.push_back("Numero do quarto invalido : \"" + teste.numeroQuarto + "\" | " + e.what()); }
            Capacidade capacidade; try { capacidade.setValor(teste.capacidade); } catch (invalid_argument& e) { erros.push_back("Capacidade invalida : \"" + to_string(teste.capacidade) + "\" | " + e.what()); }
            Dinheiro dinheiro; try { dinheiro.setValor(teste.diaria); } catch (invalid_argument& e) { erros.push_back("Diaria invalida : \"" + to_string(teste.diaria) + "\" | " + e.what()); }
            Ramal ramal; try { ramal.setValor(teste.ramal); } catch (invalid_argument& e) { erros.push_back("Ramal invalido : \"" + teste.ramal + "\" | " + e.what()); }

            Data chegada; try { chegada.setValor(teste.chegada); } catch (invalid_argument& e) { erros.push_back("Data de chegada invalida : \"" + teste.chegada + "\" | " + e.what()); }
            Data partida; try { partida.setValor(teste.partida); } catch (invalid_argument& e) { erros.push_back("Data de partida invalida : \"" + teste.partida + "\" | " + e.what()); }
            Codigo codigo; try { codigo.setValor(teste.codigo); } catch (invalid_argument& e) { erros.push_back("Codigo invalido : \"" + teste.codigo + "\" | " + e.what()); }

            if (!erros.empty()) {
                cout << "\n Erros encontrados:\n";
                for (const auto& erro : erros) {
                    cout << " - " << erro << endl;
                }
            } else {
                Hospede hospede(nome, email, endereco, cartao);
                Quarto quarto(numero, capacidade, dinheiro, ramal);
                Reserva reserva(codigo, chegada, partida, &hospede, &quarto);
                cout << "\n Reserva criada com sucesso:\n";
                reserva.exibir_reserva();
            }

        } catch (...) {
            cout << "\n Erro inesperado durante o teste.\n";
        }

        cout << "\n-----------------------------\n";
    }

    return 0;
}
