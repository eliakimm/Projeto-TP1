#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

#include "dominios.hpp"
#include "entidades.hpp"
#include "teste_entidades.hpp"

using namespace std;

int main(){
    // declaracoes:

    //runGerente();

    //runHospede();

    runReserva();

    /*Nome nome;
    Email email;
    Telefone telefone;
    Senha senha;
    Capacidade capacidade;
    Cartao cartao;
    Codigo codigo;
    Data data;
    Dinheiro dinheiro;
    Endereco endereco;
    Numero numero;
    Ramal ramal;

    string valorSTR;
    int valorINT;
    double valorDOU;

    cout << "*** SISTEMA DE CADASTRO ***" << endl;
    cout << "----> DADOS PESSOAIS <----" << endl;
    // NOME:
    // agora atualizado
    cout << "Nome: ";
    getline(cin, valorSTR);
    try{
        nome.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Nome: " << exce.what() << endl;
        return 1;
    }

    // EMAIL
    cout << "Email: ";
    getline(cin, valorSTR);
    try{
        email.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Email: " << exce.what() << endl;
        return 1;
    }

    // PESSOA
    try{
        Pessoa P(nome, email);
        P.exibirTudo();
    } catch(const invalid_argument& exce){
        cerr << "Erro na Pessoa:" << exce.what() << endl;
        return 1;
    }

    // QUARTO
    cout << "----> QUARTO <----" << endl;
    cout << "Numero do quarto (001 - 999): ";
    getline(cin, valorSTR);
    try{
        numero.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Numero: " << exce.what() << endl;
        return 1;
    }

    // capcidade
    cout << "Capacidade (1-4): ";
    cin >> valorINT;
    cin.ignore();  // limpar o buffer
    try{
        capacidade.setValor(valorINT);
    } catch(invalid_argument& exce){
         cerr << "Erro na Capacidade: " << exce.what() << endl;
         return 1;
    }

    // DINHEIRO / DIARIA
    cout << "Diaria: R$ ";
    cin >> valorDOU;
    cin.ignore();
    try{
        dinheiro.setValor(valorDOU);
    } catch(invalid_argument& exce){
        cerr << "Erro no Valor: " << exce.what() << endl;
        return 1;
    }

    // RAMAL
    cout << "Ramal (00-50): ";
    getline(cin, valorSTR);
    try{
        ramal.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Ramal: " << exce.what() << endl;
        return 1;
    }

    // QUARTO
    try{
        Quarto Q(numero, capacidade, dinheiro, ramal);
        Q.exibirTudo();
    } catch(const invalid_argument& exce){
        cerr << "Erro no Quarto: " << exce.what() << endl;
        return 1;
    }

    cout << "\n*** CADASTRO CONCLUIDO! ***" << endl;
    cout << "=================================" << endl;
    cout << "Nome: " << nome.getValor() << endl;
    cout << "Email: " << email.getValor() << endl;
    cout << "Telefone: " << telefone.getValor() << endl;
    cout << "Senha: " << senha.getValor() << endl;

    cout << "\n DADOS ADICIONAIS:" << endl;
    cout << "Capacidade: " << capacidade.getValor() << endl;
    cout << "Cartao: " << cartao.getValor() << endl;
    cout << "Codigo: " << codigo.getValor() << endl;
    cout << "Data: " << data.getValor() << endl;
    cout << "Dinheiro: R$ " << dinheiro.getValor() << endl;
    cout << "Endereço: " << endereco.getValor() << endl;
    cout << "Numero: " << numero.getValor() << endl;
    cout << "Ramal: " << ramal.getValor() << endl;
    cout << "=================================" << endl;*/

    return 0;
}


    /*
    // APAGAR PARTE ABAIXO:
    while(true){
        cout << "Seu nome: ";
        getline(cin, valorSTR);
        try{
            nome.setValor(valorSTR);
            cout << "Nome cadastrado com sucesso!" << endl;
            cout << "Bem-vindo(a), " << nome.getValor() << "!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro de validacao: " << exce.what() << endl;
            cout << "Tente de novo..." << endl;
        }
    }
    // EMAIL:
    while(true){
        cout << "Seu email: ";
        getline(cin, valorSTR);
        try{
            email.setValor(valorSTR);
            break;
        } catch(const exception& exce){
            cerr << "Erro de validacao: " << exce.what() << endl;
        }
    }
    // TELEFONE:
    while(true){
        cout << "Seu telefone: ";
        getline(cin, valorSTR);
        try{
            telefone.setValor(valorSTR);
            break;
        } catch(const exception& exce){
            cerr << "Erro de validacao: " << exce.what() << endl;
        }
    }

    cout << "----> DADOS ADICIONAIS <----" << endl;

    // SENHA:
    while(true){
        cout << "Sua senha: ";
        getline(cin, valorSTR);
        try{
            senha.setValor(valorSTR);
            cout << "Senha cadastrada com sucesso!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Capacidade
    while(true){
        cout << "Capacidade (1-4): ";
        cin >> valorINT;
        cin.ignore(); // Limpa o buffer
        try{
            capacidade.setValor(valorINT);
            cout << "Capacidade cadastrada!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Cartão
    while(true){
        cout << "Numero do cartao (16 digitos): ";
        getline(cin, valorSTR);
        try{
            cartao.setValor(valorSTR);
            cout << "Cartao validado!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Código
    while(true){
        cout << "Codigo (10 caracteres): ";
        getline(cin, valorSTR);
        try{
            codigo.setValor(valorSTR);
            cout << "Codigo cadastrado!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Data
    while(true){
        cout << "Data (DD/MMM/AAAA): ";
        getline(cin, valorSTR);
        try{
            data.setValor(valorSTR);
            cout << "Data cadastrada!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Dinheiro
    while(true){
        cout << "Valor em reais: ";
        cin >> valorDOU;
        cin.ignore(); // Limpa o buffer
        try{
            dinheiro.setValor(valorDOU);
            cout << "Valor cadastrado: R$ " << dinheiro.getValor() << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Endereço
    while(true){
        cout << "Endereço (5-30 caracteres): ";
        getline(cin, valorSTR);
        try{
            endereco.setValor(valorSTR);
            cout << "Endereço cadastrado!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Número
    while(true){
        cout << "Numero (001-999): ";
        getline(cin, valorSTR);
        try{
            numero.setValor(valorSTR);
            cout << "Numero cadastrado!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    // Ramal
    while(true){
        cout << "Ramal (00-50): ";
        getline(cin, valorSTR);
        try{
            ramal.setValor(valorSTR);
            cout << "Ramal cadastrado!" << endl;
            break;
        } catch(const exception& exce){
            cerr << "Erro: " << exce.what() << endl;
        }
    }

    cout << "\n*** CADASTRO CONCLUIDO! ***" << endl;
    cout << "=================================" << endl;
    cout << "Nome: " << nome.getValor() << endl;
    cout << "Email: " << email.getValor() << endl;
    cout << "Telefone: " << telefone.getValor() << endl;
    cout << "Senha: " << senha.getValor() << endl;

    cout << "\n DADOS ADICIONAIS:" << endl;
    cout << "Capacidade: " << capacidade.getValor() << endl;
    cout << "Cartao: " << cartao.getValor() << endl;
    cout << "Codigo: " << codigo.getValor() << endl;
    cout << "Data: " << data.getValor() << endl;
    cout << "Dinheiro: R$ " << dinheiro.getValor() << endl;
    cout << "Endereço: " << endereco.getValor() << endl;
    cout << "Numero: " << numero.getValor() << endl;
    cout << "Ramal: " << ramal.getValor() << endl;
    cout << "=================================" << endl;


    return 0;
}*/
