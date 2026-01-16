#ifndef CONTROLADORIA_HPP_INCLUDED
#define CONTROLADORIA_HPP_INCLUDED
#include "interfaces.hpp"
#include "entidades.hpp"

/**
* @file controladoria.hpp
* @brief Controladores de apresentacao do sistema de gestao de hoteis
* @details Este arquivo contem as declaracoes das classes controladoras que implementam
* as interfaces de apresentacao, mediando a interacao entre a camada de interface
* com o usuario e a camada de servicos do sistema.
*/

 /**
 * @class CntrApresentacaoAutenticacao
 * @brief Controlador responsavel pela autenticacao de usuarios.
 * @details Implementa a interface de apresentacao de autenticacao (IA_Autenticacao),
 * permitindo configurar o servico de autenticacao e realizar login de gerentes.
 * @author Matheus Nunes Ferreira - 231021511
 */
class CntrApresentacaoAutenticacao : public IA_Autenticacao {
private:
    IS_Autenticacao* servico;
public:
    /**
    * @brief Construtor padrao inicia como nulo.
    */
    CntrApresentacaoAutenticacao() : servico(nullptr) {}

    /**
    * @brief Configura o servico de autenticacao.
    * @param s Ponteiro para o servico de autenticacao.
    */
    void setAutenticar(IS_Autenticacao* s) override { servico = s; }

    /**
    * @brief Autentica um gerente interativamente.
    * @return true se a autenticacao for bem-sucedida, false caso contrario.
    */
    bool autenticarGerente() override;
};

/**
* @class CntrApresentacaoPessoal
* @brief Controlador responsavel pela gestao de usuarios e hospedes.
* @details Implementa a interface IA_Pessoal, permitindo operacões de CRUD
* sobre usuarios e hospedes, alem de funcionalidades de autoatendimento
* para usuarios autenticados.
* @author Matheus Nunes Ferreira - 231021511
*/
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
    /**
    * @brief Construtor padrao inicia como como nulo.
    */
    CntrApresentacaoPessoal() : servico(nullptr) {}

    /**
    * @brief Configura o servico de pessoal.
    * @param s Ponteiro para o servico de pessoal.
    */
    void setPessoal(IS_Pessoal* s) override { servico = s; }

    /**
    * @brief Executa o fluxo principal de operacões de pessoal.
    * @param email Email do usuario autenticado.
    */
    void executar(const Email&) override;
};

/**
* @class CntrApresentacaoGerenciamento
* @brief Controlador responsavel pela gestao de hoteis e quartos.
* @details Implementa a interface IA_Gerenciamento, permitindo operacões de cadastro,
* leitura, edicao e exclusao de hoteis e quartos.
* @author Matheus Nunes Ferreira - 231021511
*/
class CntrApresentacaoGerenciamento : public IA_Gerenciamento {
private:
    IS_Gerenciamento* servico;
    void menu(const Email&);
    void cadastrarHotel(const Email&);
    void listarHoteis();
    void excluirHotel(const Email&);
    void cadastrarQuarto();
    void listarQuartos();
    void lerQuarto();
    void editarQuarto();
    void excluirQuarto();
public:
    /**
    * @brief Construtor padrao inicia como nulo.
    */
    CntrApresentacaoGerenciamento() : servico(nullptr) {}

    /**
    * @brief Configura o servico de gerenciamento.
    * @param s Ponteiro para o servico de gerenciamento.
    */
    void setGerenciamento(IS_Gerenciamento* s) override { servico = s; }

    /**
    * @brief Executa o fluxo principal de operacões de gerenciamento.
    * @param email Email do gerente autenticado.
    */
    void executar(const Email&) override;
};

/**
* @class CntrApresentacaoReserva
* @brief Controlador responsavel pela gestao de reservas.
* @details Implementa a interface IA_Reserva, permitindo operacões de criacao,
* leitura, edicao, cancelamento e exclusao de reservas.
* @author Matheus Nunes Ferreira - 231021511
*/
class CntrApresentacaoReserva : public IA_Reserva {
private:
    IS_Reserva* servico;
    IS_Gerenciamento* servGerenciamento;
    void menu(const Email&);
    void criarReserva(const Email&);
    void cancelarReserva();
    void listarReservas(const Email&);
    void lerReserva();
    void editarReserva();
    void excluirReserva();
public:
    /**
    * @brief Construtor padrao. Inicializa o servico como nulo.
    */
    CntrApresentacaoReserva() : servico(nullptr) {}

    /**
    * @brief Configura o servico de gerenciamento auxiliar.
    * @param s Ponteiro para o servico de gerenciamento.
    */
    void setGerenciamento(IS_Gerenciamento* s) { servGerenciamento = s; }

    /**
    * @brief Configura o servico de reservas.
    * @param s Ponteiro para o servico de reservas.
    */
    void setReserva(IS_Reserva* s) override { servico = s; }

    /**
    * @brief Executa o fluxo principal de operacões de reservas.
    * @param email Email do usuario autenticado.
    */
    void executar(const Email&) override;
};

#endif // CONTROLADORIA_HPP_INCLUDED
