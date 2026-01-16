#ifndef STUBS_HPP_INCLUDED
#define STUBS_HPP_INCLUDED

#include "interfaces.hpp"
#include "containers.hpp"
#include <map>
#include <vector>

/**
* @file stubs.hpp
* @brief Implementacões stub dos servicos do sistema para desenvolvimento e teste
* @details Este arquivo contem as implementacões em memoria (stubs) das interfaces
* de servico do sistema, permitindo o desenvolvimento e teste sem dependência
* de sistemas externos ou persistência real. As implementacões utilizam
* containers em memoria para simular o comportamento dos servicos.
* @author Eliakim Pereira da Silva - 231021440
*/

/**
 * @class StubAutenticacao
 * @brief Implementacao de servico para autenticacao (stubs/in-memory)
 * @author Eliakim Pereira da Silva - 231021440
 */
class StubAutenticacao : public IS_Autenticacao {
private:
    ContainerGerentes* containerGerentes;
public:
    StubAutenticacao();
    void setContainer(ContainerGerentes* c) { containerGerentes = c; }
    bool autenticar(const Email&, const Senha&) override;
};

/**
 * @class StubPessoal
 * @brief Implementacao de servico para CRUD de gerentes e hospedes.
 * @author Eliakim Pereira da Silva - 231021440
 */
class StubPessoal : public IS_Pessoal {
private:
    ContainerGerentes containerGerentes;
    ContainerHospedes containerHospedes;
    ContainerReservas* reservaContainer = nullptr;
    ContainerHoteis* hotelContainer = nullptr;
public:
    ContainerGerentes* getContainer() { return &containerGerentes; }
    ContainerHospedes* getHospedeContainer() { return &containerHospedes; }
    void setReservaContainer(ContainerReservas* c) { reservaContainer = c; }
    void setHotelContainer(ContainerHoteis* c) { hotelContainer = c; }
    /**
     * @brief Construtor que semeia usuarios de teste para facilitar execucao de testes manuais/automaticos.
     */
    StubPessoal();

    bool criarUsuario(const Gerente&) override;
    bool lerUsuario(Gerente&) override;
    bool editarUsuario(const Gerente&) override;
    bool excluirUsuario(const Email&) override;

    bool criarHospede(const Hospede&) override;
    bool lerHospede(Hospede&) override;
    bool editarHospede(const Hospede&) override;
    bool excluirHospede(const Email&) override;
    vector<Hospede> listarHospedes() override;
};

/**
 * @class StubGerenciamento
 * @brief Implementacao de servico para gerenciamento de hoteis e quartos.
 * @author Eliakim Pereira da Silva - 231021440
 */
class StubGerenciamento : public IS_Gerenciamento {
private:
    ContainerHoteis container;
    ContainerReservas* reservaContainer = nullptr;
    ContainerGerentes* gerentesContainer = nullptr;
public:
    ContainerHoteis* getContainer() { return &container; }
    void setReservaContainer(ContainerReservas* c) { reservaContainer = c; }
    void setGerentesContainer(ContainerGerentes* c) { gerentesContainer = c; }
    bool criarHotel(const Hotel&) override;
    bool lerHotel(Hotel&) override;
    bool editarHotel(const Hotel&) override;
    bool excluirHotel(const Codigo&) override;

    bool criarQuarto(const Codigo&, const Quarto&) override;
    bool lerQuarto(const Codigo&, Quarto&) override;
    bool editarQuarto(const Codigo&, const Quarto&) override;
    bool excluirQuarto(const Codigo&, const Numero&) override;
    vector<Hotel> listarHoteis() override;
    vector<Quarto> listarQuartos(Codigo) override;
    bool lerGerente(Gerente&) override;
};

/**
 * @class StubReserva
 * @brief Implementacao de servico para gerenciamento de reservas.
 * @author Eliakim Pereira da Silva - 231021440
 */
class StubReserva : public IS_Reserva {
private:
    ContainerReservas container;
    ContainerHospedes* hospedesContainer = nullptr;
    ContainerHoteis*   hoteisContainer = nullptr;
public:
    ContainerReservas* getContainer() { return &container; }
    void setHospedeContainer(ContainerHospedes* c) { hospedesContainer = c; }
    void setHotelContainer(ContainerHoteis* c) { hoteisContainer = c; }
    bool criarReserva(const Hospede&, const Reserva&) override;
    bool cancelarReserva(const Codigo&) override;
    vector<Reserva> listarReservas(Email) override;
    bool lerReserva(Reserva&) override;
    bool editarReserva(const Reserva&) override;
    bool excluirReserva(const Codigo&) override;
};

#endif // STUBS_HPP_INCLUDED
