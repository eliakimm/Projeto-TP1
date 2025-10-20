#include "entidades.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Pessoa
Pessoa::Pessoa(const Nome& nome, const Email& email){
    this->nome = nome;
    this->email = email;
}

void Pessoa::setNome(const Nome& nomeNovo){
    nome = nomeNovo;
}
Nome Pessoa::getNome() const{
    return nome;
}

void Pessoa::setEmail(const Email& emailNovo){
    email = emailNovo;
}
Email Pessoa::getEmail() const{
    return email;
}

void Pessoa::exibirTudo() const{
    cout << "\n=== DADOS PESSOAIS ===" << endl;
    cout << "Nome: " << nome.getValor() << endl;
    cout << "Email: " << email.getValor() << endl;
    cout << "======================\n" << endl;
}
// ===========================================
// gerente
void Gerente::setRamal(Ramal ramal){
    this->ramal= ramal;
}

void Gerente::setSenha(Senha senha){
    this->senha= senha;
}

Gerente::Gerente(Nome nome, Email email, Ramal ramal, Senha senha)
    :Pessoa(nome, email){
    setRamal(ramal);
    setSenha(senha);
}

void Gerente::exibirTudo() const{
    cout << "\n=== DADOS GERENTE ===" << endl;
    cout << "Ramal: " << ramal.getValor() << endl;
    cout << "Senha: " << senha.getValor() << endl;
    cout << "Ramal: " << ramal.getValor() << endl;
    cout << "======================\n" << endl;
}

// hospede
void Hospede::setEndereco(Endereco endereco){
    this->endereco= endereco;
}

void Hospede::setCartao(Cartao cartao){
    this->cartao= cartao;
}

Hospede::Hospede(Nome nome, Email email, Endereco endereco, Cartao cartao)
    :Pessoa(nome,email){
    setEndereco(endereco);
    setCartao(cartao);
}

void Hospede::exibirTudo() const{
    cout << "Endereco: " << endereco.getValor() << endl;
    cout << "Cartao: " << cartao.getValor() << endl;
}

Quarto::Quarto(const Numero& numero, const Capacidade& capacidade, const Dinheiro& dinheiro, const Ramal& ramal){
    this->numero = numero;
    this->capacidade = capacidade;
    this->dinheiro = dinheiro;
    this->ramal = ramal;
}

void Quarto::setNumero(const Numero& numNovo){
    numero = numNovo;
}
Numero Quarto::getNumero() const{
    return numero;
}

void Quarto::setCapacidade(const Capacidade& capaNova){
    capacidade = capaNova;
}
Capacidade Quarto::getCapacidade() const{
    return capacidade;
}

void Quarto::setDinheiro(const Dinheiro& dinNovo){
    dinheiro = dinNovo;
}
Dinheiro Quarto::getDinheiro() const{
    return dinheiro;
}

void Quarto::setRamal(const Ramal& raNovo){
    ramal = raNovo;
}
Ramal Quarto::getRamal() const{
    return ramal;
}

void Quarto::exibirTudo() const{
    cout << "=== DADOS DO QUARTO ===" << endl;
    cout << "Numero: " << numero.getValor() << endl;
    cout << "Capacidade: " << capacidade.getValor() << endl;
    cout << "Valor: R$" << dinheiro.getValor() << endl;
    cout << "Ramal: " << ramal.getValor() << endl;
    cout << "=======================" << endl;
}
// ===========================================
// reservA
int Reserva::ContarDias(string data1, string data2) {
    map<string,int> meses = {
        {"JAN",1}, {"FEV",2}, {"MAR",3}, {"ABR",4},
        {"MAI",5}, {"JUN",6}, {"JUL",7}, {"AGO",8},
        {"SET",9}, {"OUT",10}, {"NOV",11}, {"DEZ",12}
    };

    auto converter = [&](string data) {
        int dia = stoi(data.substr(0,2));
        int mes = meses[data.substr(3,3)];
        int ano = stoi(data.substr(7,4));

        int total = dia;
        for (int m = 1; m < mes; m++) {
            if (m == 2 && ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)))
                total += 29;
            else {
                int diasPorMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
                total += diasPorMes[m - 1];
            }
        }
        for (int a = 1; a < ano; a++) {
            total += ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 366 : 365;
        }
        return total;
    };

    return converter(data2) - converter(data1);
}

//setters:

void Reserva::verificaData(Data data1, Data data2){
    if(ContarDias(data1.getValor(), data2.getValor()) <= 0){
        throw invalid_argument("Data invalida");
    }
}

void Reserva::setDatas(Data data1, Data data2){
    verificaData(data1, data2);
    this->chegada= data1;
    this->partida= data2;
    CalculoValor();
}

void Reserva::setCodigo(Codigo codigo){
    this->codigo= codigo;
}

void Reserva::setHospede(Hospede* h){
    this->hospede= h;
}

void Reserva::setQuarto(Quarto* q){
    this->quarto= q;
}

double Reserva::CalculoValor(){
    double dias_contados= (ContarDias(chegada.getValor(),partida.getValor())) * quarto->getDinheiro().getValor();
    Dinheiro temp;
    temp.setValor(dias_contados);
    this->valor= temp;
}

void Reserva::exibir_reserva(){
    cout << chegada.getValor() << " | RESERVA:" << endl;
    cout << "Nome do hospede: " << hospede->getNome().getValor() << endl;
    cout << "Quarto: " << quarto->getNumero().getValor() << endl;
    cout << "Ramal: " << quarto->getRamal().getValor() << endl;
    cout << "Valor total: " << valor.getValor() << endl;
}

// ===========================================
Hotel::Hotel(const Nome& nome, const Endereco& endereco, const Telefone& telefone, const Codigo& codigo){
    this->nome = nome;
    this->endereco = endereco;
    this->telefone = telefone;
    this->codigo = codigo;
}

void Hotel::setNome(const Nome& nomeNovo){
    nome = nomeNovo;
}
Nome Hotel::getNome() const{
    return nome;
}

void Hotel::setEndereco(const Endereco& endeNovo){
    endereco = endeNovo;
}
Endereco Hotel::getEndereco() const{
    return endereco;
}

void Hotel::setTelefone(const Telefone& teleNovo){
    telefone = teleNovo;
}
Telefone Hotel::getTelefone() const{
    return telefone;
}

void Hotel::setCodigo(const Codigo& codeNovo){
    codigo = codeNovo;
}
Codigo Hotel::getCodigo() const{
    return codigo;
}

void Hotel::exibirTudo() const{
    cout << "=== DADOS DO HOTEL  ===" << endl;
    cout << "Nome: " << nome.getValor() << endl;
    cout << "Endereco: " << endereco.getValor() << endl;
    cout << "Telefone" << telefone.getValor() << endl;
    cout << "Codigo: " << codigo.getValor() << endl;
    cout << "=======================" << endl;
}
