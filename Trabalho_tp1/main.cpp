#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

#include "dominios.hpp"
#include "entidades.hpp"

using namespace std;

int main(){
    // declaracoes:
    Nome nome;
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

    cout << "*** [SISTEMA DE CADASTRO DO HOTEL] ***" << endl;
    cout << "\n----> DADOS DO HOTEL <----" << endl;

    // Nome do hotel
    Nome nomeHotel;
    cout << "Nome do Hotel: ";
    getline(cin, valorSTR);
    try{
        nomeHotel.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Nome do Hotel: " << exce.what() << endl;
        return 1;
    }

    // endereco do hotel
    Endereco enderecoHotel;
    cout << "Endereco do Hotel: ";
    getline(cin, valorSTR);
    try{
        enderecoHotel.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Endereco do Hotel: " << exce.what() << endl;
        return 1;
    }

    // Telefone do Hotel
    Telefone telefoneHotel;
    cout << "Telefone do Hotel: ";
    getline(cin, valorSTR);
    try{
        telefoneHotel.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Telefone do Hotel: " << exce.what() << endl;
        return 1;
    }

    // Código do Hotel
    Codigo codigoHotel;
    cout << "Codigo do Hotel: ";
    getline(cin, valorSTR);
    try{
        codigoHotel.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Codigo do Hotel: " << exce.what() << endl;
        return 1;
    }

    // HOTEL
    try{
        Hotel H(nomeHotel, enderecoHotel, telefoneHotel, codigoHotel);
        cout << "\n--- Dados do Hotel ---" << endl;
        H.exibirTudo();
    } catch(const invalid_argument& exce){
        cerr << "Erro no Hotel: " << exce.what() << endl;
        return 1;
    }

    // PESSOA (Dados pessoais básicos)
    // NOME:
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
        cerr << "Erro na Pessoa: " << exce.what() << endl;
        return 1;
    }

    // GERENTE
    // Telefone do Gerente
    Telefone telefoneGerente;
    cout << "Telefone do Gerente: ";
    getline(cin, valorSTR);
    try{
        telefoneGerente.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Telefone: " << exce.what() << endl;
        return 1;
    }

    // Senha do Gerente
    Senha senhaGerente;
    cout << "Senha do Gerente: ";
    getline(cin, valorSTR);
    try{
        senhaGerente.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro na Senha: " << exce.what() << endl;
        return 1;
    }

    // Ramal do Gerente
    Ramal ramalGerente;
    cout << "Ramal do Gerente (00-50): ";
    getline(cin, valorSTR);
    try{
        ramalGerente.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Ramal: " << exce.what() << endl;
        return 1;
    }

    // GERENTE
    try{
        Gerente G(nome, email, ramalGerente, senhaGerente);
        G.exibirTudo();
    } catch(const invalid_argument& exce){
        cerr << "Erro no Gerente: " << exce.what() << endl;
        return 1;
    }

    // HÓSPEDE
    // ENDERECO DO HOSPEDE
    Endereco enderecoHospede;
    cout << "Endereco do Hospede: ";
    getline(cin, valorSTR);
    try{
        enderecoHospede.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Endereco: " << exce.what() << endl;
        return 1;
    }

    // CARTAO DO HOSPEDE
    Cartao cartaoHospede;
    cout << "Cartao do Hospede (16 digitos): ";
    getline(cin, valorSTR);
    try{
        cartaoHospede.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Cartao: " << exce.what() << endl;
        return 1;
    }

    // HSPEDE
    try{
        Hospede H(nome, email, enderecoHospede, cartaoHospede);
        H.exibirTudo();
    } catch(const invalid_argument& exce){
        cerr << "Erro no Hospede: " << exce.what() << endl;
        return 1;
    }

    // QUARTO
    // Número do Quarto
    Numero numeroQuarto;
    cout << "Numero do quarto (001 - 999): ";
    getline(cin, valorSTR);
    try{
        numeroQuarto.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Numero: " << exce.what() << endl;
        return 1;
    }

    // Capacidade do Quarto
    Capacidade capacidadeQuarto;
    cout << "Capacidade (1-4): ";
    cin >> valorINT;
    cin.ignore();  // limpar o buffer
    try{
        capacidadeQuarto.setValor(valorINT);
    } catch(invalid_argument& exce){
         cerr << "Erro na Capacidade: " << exce.what() << endl;
         return 1;
    }

    // Diária do Quarto
    Dinheiro diariaQuarto;
    cout << "Diaria: R$ ";
    cin >> valorDOU;
    cin.ignore();
    try{
        diariaQuarto.setValor(valorDOU);
    } catch(invalid_argument& exce){
        cerr << "Erro no Valor: " << exce.what() << endl;
        return 1;
    }

    // Ramal do Quarto
    Ramal ramalQuarto;
    cout << "Ramal do Quarto (00-50): ";
    getline(cin, valorSTR);
    try{
        ramalQuarto.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Ramal: " << exce.what() << endl;
        return 1;
    }

    // QUARTO
    try{
        Quarto Q(numeroQuarto, capacidadeQuarto, diariaQuarto, ramalQuarto);
        cout << "\n--- Dados do Quarto ---" << endl;
        Q.exibirTudo();
    } catch(const invalid_argument& exce){
        cerr << "Erro no Quarto: " << exce.what() << endl;
        return 1;
    }

    // RESERVA
    Data dataChegada, dataPartida;
    Codigo codigoReserva;

    cout << "Data de Chegada (DD/MMM/AAAA): ";
    getline(cin, valorSTR);
    try{
        dataChegada.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro na Data de Chegada: " << exce.what() << endl;
        return 1;
    }

    cout << "Data de Partida (DD/MMM/AAAA): ";
    getline(cin, valorSTR);
    try{
        dataPartida.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro na Data de Partida: " << exce.what() << endl;
        return 1;
    }

    cout << "Codigo da Reserva: ";
    getline(cin, valorSTR);
    try{
        codigoReserva.setValor(valorSTR);
    } catch(invalid_argument& exce){
        cerr << "Erro no Codigo da Reserva: " << exce.what() << endl;
        return 1;
    }

    cout << "\n*** CADASTRO CONCLUIDO! ***" << endl;
    cout << "=================================" << endl;
    cout << "RESUMO DO CADASTRO:" << endl;
    cout << "HOTEL: " << nomeHotel.getValor() << endl;
    cout << "CODIGO DO HOTEL: " << codigoHotel.getValor() << endl;
    cout << "ENDERECO DO HOTEL: " << enderecoHotel.getValor() << endl;
    cout << "TELEFONE DO HOTEL: " << telefoneHotel.getValor() << endl;

    cout << "\nGERENTE: " << nome.getValor() << endl;
    cout << "EMAIL: " << email.getValor() << endl;
    cout << "RAMAL: " << ramalGerente.getValor() << endl;

    cout << "\nQUARTO: " << numeroQuarto.getValor() << endl;
    cout << "CAPACIDADE: " << capacidadeQuarto.getValor() << endl;
    cout << "DIARIA: R$ " << diariaQuarto.getValor() << endl;
    cout << "RAMAL DO QUARTO: " << ramalQuarto.getValor() << endl;

    cout << "\nRESERVA:" << endl;
    cout << "CODIGO: " << codigoReserva.getValor() << endl;
    cout << "CHEGADA: " << dataChegada.getValor() << endl;
    cout << "PARTIDA: " << dataPartida.getValor() << endl;
    cout << "=================================" << endl;

    return 0;
}
