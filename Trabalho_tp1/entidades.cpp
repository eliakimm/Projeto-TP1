#include "entidades.hpp"
#include <iostream>

using namespace std;

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
    cout << "=== DADOS PESSOAIS - TESTE ===" << endl;
    cout << "Nome: " << nome.getValor() << endl;
    cout << "Email: " << email.getValor() << endl;
    cout << "======================" << endl;
}

// ========
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
