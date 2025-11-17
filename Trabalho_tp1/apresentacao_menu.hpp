#ifndef APRESENTACAO_MENU_HPP_INCLUDED
#define APRESENTACAO_MENU_HPP_INCLUDED

#include "interfaces.hpp"
#include <iostream>
#include <string>

// ==================== Controlador de Apresentação do Menu ====================
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
class CntrApresentacaoMenu {
private:
    IS_Autenticacao* srvAutenticacao;
    IS_Pessoal* srvPessoal;
    IS_Gerenciamento* srvGerenciamento;
    IS_Reserva* srvReserva;

    IA_Pessoal* cntrPessoal;
    IA_Gerenciamento* cntrGerenciamento;
    IA_Reserva* cntrReserva;

    // Métodos privados para cada tela
    void telaMenuPrincipal();
    void telaLogin();
    void telaCadastroGerente();
    void telaMenuAutenticado(const Email& email);
    void limparTela();
    void exibirCabecalho();
    void pausar();

public:
    CntrApresentacaoMenu();
    
    // Setters para injeção de dependência - Serviços
    void setAutenticacao(IS_Autenticacao* srv);
    void setPessoalServico(IS_Pessoal* srv);
    void setGerenciamentoServico(IS_Gerenciamento* srv);
    void setReservaServico(IS_Reserva* srv);

    // Setters para injeção de dependência - Controladores de Apresentação
    void setPessoal(IA_Pessoal* cntr);
    void setGerenciamento(IA_Gerenciamento* cntr);
    void setReserva(IA_Reserva* cntr);
    
    // Método principal que inicia o fluxo
    void executar();
    
    virtual ~CntrApresentacaoMenu() {}
};

#endif // APRESENTACAO_MENU_HPP_INCLUDED
