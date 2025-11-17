#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED
#include <vector>
#include "dominios.hpp"
#include "entidades.hpp"

/**
 * @defgroup Interfaces Service Interfaces
 * @brief Interfaces que definem os contratos de servico do sistema.
 * @details Separacao clara entre apresentacao (IA_*) e servicos (IS_*).
 * @{
 */

class IS_Autenticacao;
class IS_Pessoal;
class IS_Gerenciamento;
class IS_Reserva;

/**
 * @class IA_Autenticacao
 * @brief Interface de apresentacao para autenticacao.
 */
class IA_Autenticacao{
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
public:
    /**
     * @brief Autentica um gerente interativamente.
     * @return True se autenticacao bem-sucedida, false caso contrario.
     */
    virtual bool autenticarGerente() = 0;
    /**
     * @brief Configura o servico de autenticacao.
     */
    virtual void setAutenticar(IS_Autenticacao*) = 0;
    virtual ~IA_Autenticacao() {}
};

/**
 * @class IS_Autenticacao
 * @brief Interface de servico para autenticacao.
 * @details Fornece operacao de autenticacao baseada em email e senha.
 */
class IS_Autenticacao{
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
public:
    /**
     * @brief Autentica um usuario.
     * @param email Email do gerente.
     * @param senha Senha do gerente.
     * @return True se credenciais forem validas, false caso contrario.
     */
    virtual bool autenticar(const Email&, const Senha&) = 0;
    virtual ~IS_Autenticacao() {}
};

/**
 * @class IA_Pessoal
 * @brief Interface de apresentacao para gerenciamento de dados pessoais.
 */
class IA_Pessoal{
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
public:
    /**
     * @brief Executa o menu de gerenciamento pessoal.
     * @param email Email do gerente autenticado.
     */
    virtual void executar(const Email&) = 0;
    /**
     * @brief Configura o servico de gerenciamento pessoal.
     */
    virtual void setPessoal(IS_Pessoal*) = 0;
    virtual ~IA_Pessoal() {}
};

/**
 * @class IS_Pessoal
 * @brief Interface de servico para gerenciamento de gerentes e hospedes.
 */
class IS_Pessoal{
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
public:
    // --- CRUD Gerente ---
    /**
     * @brief Cria um novo gerente.
     * @param g Gerente a ser criado.
     * @return True se criacao bem-sucedida, false se email ja existe.
     */
    virtual bool criarUsuario(const Gerente&) = 0;
    /**
     * @brief Le dados de um gerente pelo email.
     * @param g Gerente com email definido; sera preenchido com dados do banco.
     * @return True se encontrado, false caso contrario.
     */
    virtual bool lerUsuario(Gerente&) = 0;
    /**
     * @brief Edita dados de um gerente.
     * @param g Gerente com email (PK) e novos valores.
     * @return True se atualizacao bem-sucedida, false se gerente nao existe.
     */
    virtual bool editarUsuario(const Gerente&) = 0;
    /**
     * @brief Exclui um gerente pelo email.
     * @param e Email do gerente a excluir.
     * @return True se exclusao bem-sucedida, false se nao existe.
     */
    virtual bool excluirUsuario(const Email&) = 0;

    // --- CRUD Hospede ---
    /**
     * @brief Cria um novo hospede.
     */
    virtual bool criarHospede(const Hospede&) = 0;
    /**
     * @brief Le dados de um hospede pelo email.
     */
    virtual bool lerHospede(Hospede&) = 0;
    /**
     * @brief Edita dados de um hospede.
     */
    virtual bool editarHospede(const Hospede&) = 0;
    /**
     * @brief Exclui um hospede pelo email.
     */
    virtual bool excluirHospede(const Email&) = 0;
    /**
     * @brief Lista todos os hospedes cadastrados.
     */
    virtual std::vector<Hospede> listarHospedes() = 0;

    virtual ~IS_Pessoal() {}
};

/**
 * @class IA_Gerenciamento
 * @brief Interface de apresentacao para gerenciamento de hoteis e quartos.
 */
class IA_Gerenciamento{
public:
    /**
     * @brief Executa o menu de gerenciamento de hoteis.
     * @param email Email do gerente autenticado.
     */
    virtual void executar(const Email&) = 0;
    /**
     * @brief Configura o servico de gerenciamento.
     */
    virtual void setGerenciamento(IS_Gerenciamento*) = 0;
    virtual ~IA_Gerenciamento() {}
};

/**
 * @class IS_Gerenciamento
 * @brief Interface de servico para gerenciamento de hoteis e quartos.
 */
class IS_Gerenciamento{
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
public:
    // --- CRUD Hotel ---
    /**
     * @brief Cria um novo hotel.
     */
    virtual bool criarHotel(const Hotel&) = 0;
    /**
     * @brief Le dados de um hotel pelo codigo.
     */
    virtual bool lerHotel(Hotel&) = 0;
    /**
     * @brief Edita dados de um hotel.
     */
    virtual bool editarHotel(const Hotel&) = 0;
    /**
     * @brief Exclui um hotel e suas reservas.
     */
    virtual bool excluirHotel(const Codigo&) = 0;

    // --- CRUD Quarto ---
    /**
     * @brief Cria um novo quarto em um hotel.
     * @param codHotel Codigo do hotel.
     * @param q Quarto a ser criado.
     */
    virtual bool criarQuarto(const Codigo&, const Quarto&) = 0;
    /**
     * @brief Le dados de um quarto.
     * @param codHotel Codigo do hotel.
     * @param q Quarto com numero definido; sera preenchido com dados.
     */
    virtual bool lerQuarto(const Codigo&, Quarto&) = 0;
    /**
     * @brief Edita dados de um quarto.
     */
    virtual bool editarQuarto(const Codigo&, const Quarto&) = 0;
    /**
     * @brief Exclui um quarto.
     */
    virtual bool excluirQuarto(const Codigo&, const Numero&) = 0;
    /**
     * @brief Lista todos os hoteis.
     */
    virtual std::vector<Hotel> listarHoteis() = 0;
    /**
     * @brief Lista todos os quartos de um hotel.
     */
    virtual std::vector<Quarto> listarQuartos(Codigo) = 0;

    virtual ~IS_Gerenciamento() {}
};

/**
 * @class IA_Reserva
 * @brief Interface de apresentacao para gerenciamento de reservas.
 */
class IA_Reserva{
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
public:
    /**
     * @brief Executa o menu de gerenciamento de reservas.
     * @param email Email do hospede autenticado.
     */
    virtual void executar(const Email&) = 0;
    /**
     * @brief Configura o servico de reservas.
     */
    virtual void setReserva(IS_Reserva*) = 0;
    virtual ~IA_Reserva() {}
};

/**
 * @class IS_Reserva
 * @brief Interface de servico para gerenciamento de reservas.
 */
class IS_Reserva{
public:
    /**
     * @brief Cria uma nova reserva.
     * @param hospede Hospede que faz a reserva.
     * @param reserva Dados da reserva com codigo, hotel, quarto e datas.
     * @return True se criacao bem-sucedida, false se conflito de datas ou erro.
     */
    virtual bool criarReserva(const Hospede&, const Reserva&) = 0;
    /**
     * @brief Cancela uma reserva.
     * @param cod Codigo da reserva a cancelar.
     */
    virtual bool cancelarReserva(const Codigo&) = 0;
    /**
     * @brief Lista todas as reservas de um hospede.
     * @param e Email do hospede.
     */
    virtual std::vector<Reserva> listarReservas(Email) = 0;
    /**
     * @brief Le dados de uma reserva.
     */
    virtual bool lerReserva(Reserva&) = 0;
    /**
     * @brief Edita dados de uma reserva (ex: mudar datas).
     * @return False se conflito de datas ou erro.
     */
    virtual bool editarReserva(const Reserva&) = 0;
    /**
     * @brief Exclui uma reserva.
     */
    virtual bool excluirReserva(const Codigo&) = 0;
    virtual ~IS_Reserva() {}
};

/**
 * @} // end Interfaces defgroup
 */

#endif // INTERFACES_HPP_INCLUDED
