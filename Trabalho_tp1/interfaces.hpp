#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED
#include "dominios.hpp"
#include "entidades.hpp"

//Declaração adiantada (forward declaration)

class IS_Autenticacao;
class IS_Pessoal;
class IS_Gerenciamento;
class IS_Reserva;

//Interface responsavel pela autenticacao (camada de apresentação):

class IA_Autenticacao{
public:
    virtual bool autenticarGerente()= 0;
    virtual void setAutenticar(IS_Autenticacao*)= 0;
    virtual ~IA_Autenticacao(){}
};

//Interface responsavel pela autenticacao (camada de serviço):

class IS_Autenticacao{
public:
    virtual bool autenticar(const Email&, const Senha&)= 0;
    virtual ~IS_Autenticacao(){}
};

//Inetrface responsavel pela apresentação dos serviços pessoais

class IA_Pessoal{
public:
    virtual void executar(const Email&)= 0;
    virtual void setPessoal(IS_Pessoal*)= 0;
    virtual ~IA_Pessoal(){}
};

//Interface responsavel pelo serviço pessoal: criar usuario, ler, editar e excluir usuario

class IS_Pessoal{
public:
    virtual bool criarUsuario(Gerente)= 0;
    virtual bool lerUsuario(Gerente&)= 0;
    virtual bool editarUsuario(Gerente)= 0;
    virtual bool excluirUsuario(Email)= 0;

    virtual ~IS_Pessoal(){}
};

//Iterface de apresentação de gerenciamento de hoteis:

class IA_Gerenciamento{
public:
    virtual void executar(const Email&)= 0;
    virtual void setGerenciamento(IS_Gerenciamento*)= 0;

    virtual ~IA_Gerenciamento(){}
};

//Interface resposavel por prover o serviço de gerenciamento de hoteis:

class IS_Gerenciamento{
public:
    virtual bool criarHotel(Hotel)= 0;
    virtual bool lerHotel(Hotel&)= 0;
    virtual bool editarHotel(Hotel)= 0;
    virtual bool excluirHotel(Codigo)= 0;

    virtual bool criarQuarto(Codigo, Quarto)= 0;
    virtual vector<Hotel> listarHoteis()= 0;
    virtual vector<Quarto> listarQuartos(Codigo)= 0;

    virtual ~IS_Gerenciamento(){}
};

//Interface de apresentação de reserva:

class IA_Reserva{
public:
    virtual void executar(const Email&)= 0;
    virtual void setReserva(IS_Reserva*)= 0;

    virtual ~IA_Reserva(){}
};

//Interface responsavel por prover os serviços de reserva:

class IS_Reserva{
public:
    virtual bool criarReserva(const Hospede&, const Reserva&)= 0;
    virtual bool cancelarReserva(const Codigo&)= 0;
    virtual vector<Reserva> listarReservas(Email)= 0;

    virtual ~IS_Reserva(){}
};

#endif // INTERFACES_HPP_INCLUDED
