#ifndef STUBS_HPP_INCLUDED
#define STUBS_HPP_INCLUDED

#include "interfaces.hpp"
#include "containers.hpp"
#include <map>
#include <vector>

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
public:
    ContainerGerentes* getContainer() { return &containerGerentes; }
    void setReservaContainer(ContainerReservas* c) { reservaContainer = c; }
    
    bool criarUsuario(const Gerente&) override;
    bool lerUsuario(Gerente&) override;
    bool editarUsuario(const Gerente&) override;
    bool excluirUsuario(const Email&) override;

    bool criarHospede(const Hospede&) override;
    bool lerHospede(Hospede&) override;
    bool editarHospede(const Hospede&) override;
    bool excluirHospede(const Email&) override;
    std::vector<Hospede> listarHospedes() override;
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
public:
    void setReservaContainer(ContainerReservas* c) { reservaContainer = c; }
    bool criarHotel(const Hotel&) override;
    bool lerHotel(Hotel&) override;
    bool editarHotel(const Hotel&) override;
    bool excluirHotel(const Codigo&) override;

    bool criarQuarto(const Codigo&, const Quarto&) override;
    bool lerQuarto(const Codigo&, Quarto&) override;
    bool editarQuarto(const Codigo&, const Quarto&) override;
    bool excluirQuarto(const Codigo&, const Numero&) override;
    std::vector<Hotel> listarHoteis() override;
    std::vector<Quarto> listarQuartos(Codigo) override;
};

/**
 * @class StubReserva
 * @brief Implementacao de servico para gerenciamento de reservas.
 * @author Eliakim Pereira da Silva - 231021440
 */
class StubReserva : public IS_Reserva {
private:
    ContainerReservas container;
public:
    ContainerReservas* getContainer() { return &container; }
    bool criarReserva(const Hospede&, const Reserva&) override;
    bool cancelarReserva(const Codigo&) override;
    std::vector<Reserva> listarReservas(Email) override;
    bool lerReserva(Reserva&) override;
    bool editarReserva(const Reserva&) override;
    bool excluirReserva(const Codigo&) override;
};

#endif // STUBS_HPP_INCLUDED
