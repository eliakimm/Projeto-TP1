#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED
#include "dominios.hpp"
#include <iostream>

using namespace std;

class Pessoa{  // nome email
private:
    Nome nome;
    Email email;
public:
    // construtor da Pessoa
    Pessoa(const Nome& nome, const Email& email);

    void setNome(const Nome& nomeNovo);
    void setEmail(const Email& emailNovo);

    Nome getNome() const;
    Email getEmail() const;

    void exibirTudo() const;
};

class Quarto{  // numero capacidade dinheiro ramal
private:
    Numero numero;
    Capacidade capacidade;
    Dinheiro dinheiro;
    Ramal ramal;
public:
    Quarto(const Numero& numero, const Capacidade& capacidade, const Dinheiro& dinheiro, const Ramal& ramal);

    void setNumero(const Numero& numNovo);
    void setCapacidade(const Capacidade& capaNova);
    void setDinheiro(const Dinheiro& dinNovo);
    void setRamal(const Ramal& raNovo);

    Numero getNumero() const;
    Capacidade getCapacidade() const;
    Dinheiro getDinheiro() const;
    Ramal getRamal() const;

    void exibirTudo() const;
};

#endif // ENTIDADES_HPP_INCLUDED
