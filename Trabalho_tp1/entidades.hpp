#ifndef ENTIDADES_HPP
#define ENTIDADES_HPP

#include "dominios.hpp"

/**
 * @defgroup Entidades Domain Entities
 * @brief Classes que representam entidades principais do sistema.
 * @details Usam domínios para validar seus atributos e mantém as regras de negócio.
 * @{
 */

/**
 * @class Pessoa
 * @brief Classe base abstrata para pessoas (Gerente, Hospede).
 * @details Encapsula atributos comuns: nome e email.
 * @author Matheus Nunes Ferreira - 231021511
 */
class Pessoa {
private:
    Nome  nome;
    Email email;

public:
    /**
     * @brief Constroi uma Pessoa com nome e email.
     * @param n Nome da pessoa.
     * @param e Email da pessoa.
     */
    Pessoa(const Nome& n, const Email& e);
    /**
     * @brief Constroi uma Pessoa vazia.
     */
    Pessoa() : nome(), email() {}

    /**
     * @brief Define o nome da pessoa.
     */
    void setNome(const Nome& nomeNovo);
    /**
     * @brief Define o email da pessoa.
     */
    void setEmail(const Email& emailNovo);
    /**
     * @brief Retorna o nome da pessoa.
     */
    Nome  getNome()  const;
    /**
     * @brief Retorna o email da pessoa.
     */
    Email getEmail() const;

    /**
     * @brief Exibe todos os atributos da pessoa.
     */
    void exibirTudo() const;
};

/**
 * @class Gerente
 * @brief Entidade que representa um gerente do sistema.
 * @details Herda de Pessoa e adiciona ramal e senha para autenticacao.
 */
class Gerente : public Pessoa {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    Ramal ramal;
    Senha senha;

public:
    /**
     * @brief Constroi um Gerente com todos os atributos.
     * @param n Nome do gerente.
     * @param e Email do gerente (chave primaria).
     * @param r Ramal do gerente (00-50).
     * @param s Senha do gerente.
     */
    Gerente(const Nome& n, const Email& e, const Ramal& r, const Senha& s);
    /**
     * @brief Constroi um Gerente vazio.
     */
    Gerente() : Pessoa(Nome(), Email()), ramal(), senha() {}

    /**
     * @brief Define o ramal do gerente.
     */
    void setRamal(Ramal);
    /**
     * @brief Define a senha do gerente.
     */
    void setSenha(Senha);

    /**
     * @brief Retorna o ramal do gerente.
     */
    Ramal getRamal() const;
    /**
     * @brief Retorna a senha do gerente.
     */
    Senha getSenha() const;

    /**
     * @brief Exibe todos os atributos do gerente.
     */
    void exibirTudo() const;
};

/**
 * @class Hospede
 * @brief Entidade que representa um hospede (cliente) do hotel.
 * @details Herda de Pessoa e adiciona endereco e cartao de credito.
 */
class Hospede : public Pessoa {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    Endereco endereco;
    Cartao   cartao;

public:
    /**
     * @brief Constroi um Hospede com todos os atributos.
     * @param n Nome do hospede.
     * @param e Email do hospede (chave primaria).
     * @param end Endereco do hospede.
     * @param c Numero de cartao de credito do hospede.
     */
    Hospede(const Nome& n, const Email& e, const Endereco& end, const Cartao& c);
    /**
     * @brief Constroi um Hospede vazio.
     */
    Hospede() : Pessoa(Nome(), Email()), endereco(), cartao() {}
    /**
     * @author Matheus Nunes Ferreira - 231021511
     */

    /**
     * @brief Define o endereco do hospede.
     */
    void setEndereco(const Endereco&);
    /**
     * @brief Define o cartao do hospede.
     */
    void setCartao(const Cartao&);
    /**
     * @author Matheus Nunes Ferreira - 231021511
     */

    /**
     * @brief Retorna o endereco do hospede.
     */
    Endereco getEndereco() const;
    /**
     * @brief Retorna o cartao do hospede.
     */
    Cartao   getCartao() const;
    /**
     * @author Eliakim Pereira da Silva - 231021440
     */

    /**
     * @brief Exibe todos os atributos do hospede.
     */
    void exibirTudo() const;
};

/**
 * @class Hotel
 * @brief Entidade que representa um hotel no sistema.
 * @details Encapsula informacoes do hotel: codigo (PK), nome, endereco e telefone.
 */
class Hotel {
private:
    Codigo   codigo;
    Nome     nome;
    Endereco endereco;
    Telefone telefone;
    // Email do gerente/proprietario do hotel (opcional)
    Email    gerenteEmail;

public:
    /**
     * @brief Constroi um Hotel com todos os atributos.
     * @param c Codigo do hotel (chave primaria).
     * @param n Nome do hotel.
     * @param e Endereco do hotel.
     * @param t Telefone do hotel.
     */
    Hotel(const Codigo& c, const Nome& n, const Endereco& e, const Telefone& t);
    /**
     * @brief Constroi um Hotel vazio.
     */
    Hotel() : codigo(), nome(), endereco(), telefone() {}

    /**
     * @brief Define o codigo do hotel (PK imutavel).
     */
    void setCodigo(const Codigo&);
    /**
     * @brief Define o nome do hotel.
     */
    void setNome(const Nome&);
    /**
     * @brief Define o endereco do hotel.
     */
    void setEndereco(const Endereco&);
    /**
     * @brief Define o telefone do hotel.
     */
    void setTelefone(const Telefone&);
    /**
     * @brief Define o email do gerente/proprietario do hotel (opcional).
     */
    void setGerenteEmail(const Email&);

    /**
     * @brief Retorna o codigo do hotel.
     */
    Codigo   getCodigo() const;
    /**
     * @brief Retorna o nome do hotel.
     */
    Nome     getNome() const;
    /**
     * @brief Retorna o endereco do hotel.
     */
    Endereco getEndereco() const;
    /**
     * @brief Retorna o telefone do hotel.
     */
    Telefone getTelefone() const;
    /**
     * @brief Retorna o email do gerente/proprietario do hotel.
     */
    Email getGerenteEmail() const;

    /**
     * @brief Exibe todos os atributos do hotel.
     */
    void exibirTudo() const;
};

/**
 * @class Quarto
 * @brief Entidade que representa um quarto de hotel.
 * @details Encapsula numero (PK), capacidade, valor da diaria e ramal interno.
 */
class Quarto {
private:
    Numero    numero;
    Nome      descricao;
    Capacidade capacidade;
    Dinheiro  valor;
    Ramal     ramal;

public:
    /**
     * @brief Constroi um Quarto com todos os atributos.
     * @param num Numero do quarto (PK, 001-999).
     * @param cap Capacidade do quarto (1-4).
     * @param v Valor da diaria.
     * @param ram Ramal interno do quarto.
     */
    Quarto(const Numero& num, const Capacidade& cap, const Dinheiro& v, const Ramal& ram);
    /**
     * @brief Constroi um Quarto vazio.
     */
    Quarto() : numero(), descricao(), capacidade(), valor(), ramal() {}

    /**
     * @brief Define o numero do quarto (PK imutavel).
     */
    void setNumero(const Numero& n);
    /**
     * @brief Define a descricao do quarto.
     */
    void setDescricao(const Nome& d);
    /**
     * @brief Define a capacidade do quarto.
     */
    void setCapacidade(const Capacidade& c);
    /**
     * @brief Define o valor da diaria.
     */
    void setValor(const Dinheiro& v);
    /**
     * @brief Define o ramal interno do quarto.
     */
    void setRamal(const Ramal& r);

    /**
     * @brief Retorna o numero do quarto.
     */
    Numero    getNumero() const;
    /**
     * @brief Retorna a descricao do quarto.
     */
    Nome      getDescricao() const;
    /**
     * @brief Retorna a capacidade do quarto.
     */
    Capacidade getCapacidade() const;
    /**
     * @brief Retorna o valor da diaria.
     */
    Dinheiro  getValor() const;
    /**
     * @brief Retorna o ramal do quarto.
     */
    Ramal     getRamal() const;

    /**
     * @brief Exibe todos os atributos do quarto.
     */
    void exibirTudo() const;
};

/**
 * @class Reserva
 * @brief Entidade que representa uma reserva de quarto.
 * @details Encapsula codigo (PK), referencias para hospede/hotel/quarto e datas de checkin/checkout.
 *          As referencias sao nao-donas (ponteiros) e podem ser nullptr.
 */
class Reserva {
private:
    Codigo codigo;
    /**
     * Ponteiro não-dono para o hospede que fez a reserva.
     * Pode ser nullptr; o container gerencia a validade.
     */
    Hospede* hospede;
    /**
     * Ponteiro não-dono para o hotel da reserva.
     */
    Hotel*   hotel;
    /**
     * Ponteiro não-dono para o quarto reservado.
     */
    Quarto*  quarto;
    /**
     * Data de checkin da reserva.
     */
    Data dataCheckin;
    /**
     * Data de checkout da reserva.
     */
    Data dataCheckout;

public:
    /**
     * @brief Constroi uma Reserva com todos os atributos.
     * @param c Codigo da reserva (PK).
     * @param h Ponteiro para o hospede (nao-dono).
     * @param ho Ponteiro para o hotel (nao-dono).
     * @param q Ponteiro para o quarto (nao-dono).
     * @param checkin Data de checkin (opcional, padrao vazio).
     * @param checkout Data de checkout (opcional, padrao vazio).
     */
    Reserva(const Codigo& c, Hospede* h, Hotel* ho, Quarto* q,
            const Data& checkin = Data(), const Data& checkout = Data());
    /**
     * @brief Constroi uma Reserva vazia.
     */
    Reserva() : codigo(), hospede(nullptr), hotel(nullptr), quarto(nullptr),
                dataCheckin(), dataCheckout() {}

    /**
     * @brief Define o codigo da reserva.
     */
    void setCodigo(const Codigo& c);
    /**
     * @brief Define o ponteiro para o hospede.
     */
    void setHospede(Hospede* h);
    /**
     * @brief Define o ponteiro para o hotel.
     */
    void setHotel(Hotel* ho);
    /**
     * @brief Define o ponteiro para o quarto.
     */
    void setQuarto(Quarto* q);
    /**
     * @brief Define as datas de checkin e checkout.
     */
    void setDatas(const Data& checkin, const Data& checkout);

    /**
     * @brief Retorna o codigo da reserva.
     */
    Codigo   getCodigo() const;
    /**
     * @brief Retorna o ponteiro para o hospede (pode ser nullptr).
     */
    Hospede* getHospede() const;
    /**
     * @brief Retorna o ponteiro para o hotel (pode ser nullptr).
     */
    Hotel*   getHotel() const;
    /**
     * @brief Retorna o ponteiro para o quarto (pode ser nullptr).
     */
    Quarto*  getQuarto() const;
    /**
     * @brief Retorna a data de checkin.
     */
    Data     getCheckin() const;
    /**
     * @brief Retorna a data de checkout.
     */
    Data     getCheckout() const;

    /**
     * @brief Exibe todos os atributos da reserva.
     */
    void exibirTudo() const;
    /**
     * @brief Exibe um resumo simples da reserva (formato usado em testes).
     */
    void exibir_reserva();
};

/**
 * @} // end Entidades defgroup
 */

#endif
