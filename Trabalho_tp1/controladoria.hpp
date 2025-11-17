#ifndef CONTROLADORIA_HPP_INCLUDED
#define CONTROLADORIA_HPP_INCLUDED
#include "interfaces.hpp"
#include "entidades.hpp"

/**
 * @file controladoria.hpp
 * @brief Controladores de apresentacao (interfaces de UI) para o sistema.
 * @details Implementa classes que mediam a interacao entre a apresentacao e os servicos.
 *
 * @author Matheus Nunes Ferreira - 231021511
 */

class CntrApresentacaoAutenticacao : public IA_Autenticacao {
private:
    IS_Autenticacao* servico;
public:
    CntrApresentacaoAutenticacao() : servico(nullptr) {}
    void setAutenticar(IS_Autenticacao* s) override { servico = s; }
    bool autenticarGerente() override;
};

class CntrApresentacaoPessoal : public IA_Pessoal {
private:
    IS_Pessoal* servico;
    void menu(const Email&);
    void criarUsuario();
    void lerUsuario();
    void editarUsuario();
    void excluirUsuario();
     void criarHospede();
     void lerHospede();
     void editarHospede();
     void excluirHospede();
     void listarHospedes();
    // Self-service para usuario autenticado
    void verMinhaConta(const Email&);
    void editarMinhaConta(const Email&);
    void excluirMinhaConta(const Email&);
public:
    CntrApresentacaoPessoal() : servico(nullptr) {}
    void setPessoal(IS_Pessoal* s) override { servico = s; }
    void executar(const Email&) override;
};

class CntrApresentacaoGerenciamento : public IA_Gerenciamento {
private:
    IS_Gerenciamento* servico;
    void menu(const Email&);
    void cadastrarHotel();
    void listarHoteis();
    void cadastrarQuarto();
    void listarQuartos();
    void lerQuarto();
    void editarQuarto();
    void excluirQuarto();
public:
    CntrApresentacaoGerenciamento() : servico(nullptr) {}
    void setGerenciamento(IS_Gerenciamento* s) override { servico = s; }
    void executar(const Email&) override;
};

class CntrApresentacaoReserva : public IA_Reserva {
private:
    IS_Reserva* servico;
    void menu(const Email&);
    void criarReserva(const Email&);
    void cancelarReserva();
    void listarReservas(const Email&);
    void lerReserva();
    void editarReserva();
    void excluirReserva();
public:
    CntrApresentacaoReserva() : servico(nullptr) {}
    void setReserva(IS_Reserva* s) override { servico = s; }
    void executar(const Email&) override;
};

#endif // CONTROLADORIA_HPP_INCLUDED
