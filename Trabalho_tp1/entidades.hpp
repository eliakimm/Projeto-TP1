#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED
#include "dominios.hpp"
#include <iostream>

using namespace std;

/**
* @class Pessoa
* @brief Entidade que representa uma pessoa
*
* @details A classe Pessoa tem dominios que pertencem
* a pessoa que vai ser cadastrada
*
* @author Matheus Nunes Ferreira - 231021511
*/
class Pessoa{  // nome email
private:
    Nome nome;        ///< Nome completeo
    Email email;      ///< Endereco email valido
public:

    /**
    * @brief Construtor da entidade Pessoa
    * @param Nome nome completo e valido
    * @param Email email valido
    */
    Pessoa(const Nome& nome, const Email& email);

    /**
    * @brief Atualiza o nome da Pessoa
    * @param nomeNovo a ser validado e atribuido
    * @param emailNovo a ser validado e atribuido
    */
    void setNome(const Nome& nomeNovo);
    void setEmail(const Email& emailNovo);

    /**
    * @brief Recupera o nome da Pessoa
    * @return  Nome objeto contendo o nome ja validado
    */
    Nome getNome() const;

    /**
    * @brief Recupera o email da Pessoa
    * @return  Email objeto contendo o email ja validado
    */
    Email getEmail() const;

    /**
    * @brief Vai exibir os dados em uma lista
    */
    void exibirTudo() const;
};
// ===================================================
// gerente
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

    void exibirTudo() const;
};

// hospete
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

    void exibirTudo() const;
};

// ===================================================

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
// =====================================
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
// =====================================

class Hotel{
private:
    Nome nome;
    Endereco endereco;
    Telefone telefone;
    Codigo codigo;
public:
    Hotel(const Nome& nome, const Endereco& endereco, const Telefone& telefone, const Codigo& codigo);

    void setNome(const Nome& nomeNovo);
    void setEndereco(const Endereco& endeNovo);
    void setTelefone(const Telefone& teleNovo);
    void setCodigo(const Codigo& codeNovo);

    Nome getNome() const;
    Endereco getEndereco() const;
    Telefone getTelefone() const;
    Codigo getCodigo() const;

    void exibirTudo() const;

};
#endif // ENTIDADES_HPP_INCLUDED
