#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED
#include "dominios.hpp"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

class Gerente:public Pessoa{
private:
    Ramal ramal;
    Senha senha;
public:
    void setRamal(Ramal);
    void setSenha(Senha);

    Ramal getRamal(){return ramal;}
    Senha getSenha(){return senha;}

    //Construtores:
    Gerente(Nome, Email, Ramal, Senha);
};

class Hospede:public Pessoa{
private:
    Endereco endereco;
    Cartao cartao;
public:
    void setEndereco(Endereco);
    void setCartao(Cartao);

    Endereco getEndereco(){return endereco;}
    Cartao getCartao(){return cartao;}

    //Construtores:
    Hospede(Nome, Email, Endereco, Cartao);
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

class Reserva{
private:
    Data chegada;
    Data partida;
    Dinheiro valor;
    Codigo codigo;
    int ContarDias(string, string);
    void verificaData(Data,Data);
    double CalculoValor();

    Hospede* hospede;
    Quarto* quarto;

public:

    void setDatas(Data, Data);

    void setCodigo(Codigo);

    void setHospede(Hospede* h);
    void setQuarto(Quarto* q);

    Data getChegada(){return chegada;}
    Data getPartida(){return partida;}
    Codigo getCodigo(){return codigo;}

    Hospede* getHospede(){return hospede;}
    Quarto* getQuarto(){return quarto;}

    void exibir_reserva();

};


#endif // ENTIDADES_HPP_INCLUDED
