#ifndef CONTROLADORIA_HPP_INCLUDED
#define CONTROLADORIA_HPP_INCLUDED
#include "interfaces.hpp"

// cpntrole da Autenticacao
class CntrApresentacaoAutenticacao : public IA_Autenticacao{
private:
    IS_Autenticacao* cntrServicoAutenticacao;
public:
    CntrApresentacaoAutenticacao();
    void setAutenticar(IS_Autenticacao*) override;
    bool autenticarGerente() override;
};

// servico da autenticacao
class CntrSevicoAutenticacao : IS_Autenticacao{
public:
    bool autenticar(const Email&, const Senha&) override;
};

// controle do Pessoal
class CntrApresentacaoPessoal : public IA_Pessoal{
private:
    IS_Pessoal* cntrServicoPessoal;
public:
    CntrApresentacaoPessoal();
    void setPessoal(IS_Pessoal*) override;
    bool executar(const Email&) override;
};

// servico do pessoal
class CntrServicoPessoal : public IS_Pessoal{
public:
    bool criarUsuario(Gerente) override;
    bool lerUsuario(Gerente&) override;
    bool editarUsuario(Gerente) override;
    bool excluirUsuario(Email) override;
};

// controle do gerenciamento
class CntrApresentacaoGerenciamento : public IA_Gerenciamento{
private:
    IS_Gerenciamento* cntrServicoGerenciamento;
public:
    CntrServicoGerenciamento();
    void setGerenciamento(IS_Gerenciamento*) override;
    void executar(const Email&) override;
};

// servico do gerenciamento
class CntrServicoGerenciamento : public IS_Gerenciamento{
public:
    bool criarHotel(Hotel) override;
    bool lerHotel(Hotel&) override;
    bool editarHotel(Hotel) override;
    bool excluirHotel(Codigo) override;

    bool criarQuarto(Codigo, Quarto) override;

    vector<Hotel> listarHoteis() override;
    vector<Quarto> listarQuartos(Codigo) override;
};

// controle da reserva
class CntrApresentacaoReserva : public IA_Reserva{
private:
    IS_Reserva* cntrServicoReserva;
public:
    CntrServicoReserva();
    void setReserva(IS_Reserva*) override;
    void executar(const Email&) override;
};

// servico da reserva
class CntrServicoReserva : public IS_Reserva{
public:
    bool criarReserva(const Hospede&, const Reserva&) override;
    bool cancelarReserva(const Codigo&) override;
};

#endif // CONTROLADORIA_HPP_INCLUDED
