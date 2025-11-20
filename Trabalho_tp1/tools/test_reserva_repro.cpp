#include <iostream>
#include "stubs.hpp"

int main() {
    try {
    std::cout << "Stage: init stubs\n";
    StubPessoal svPessoal;
    StubGerenciamento svGer;
    StubReserva svReserva;
    std::cout << "Stage: created stubs\n";

    // wire
    svPessoal.setReservaContainer(svReserva.getContainer());
    svGer.setReservaContainer(svReserva.getContainer());
    svGer.setGerentesContainer(svPessoal.getContainer());
    svPessoal.setHotelContainer(svGer.getContainer());
    svReserva.setHospedeContainer(svPessoal.getHospedeContainer());
    svReserva.setHotelContainer(svGer.getContainer());

    // criar hotel (codigo deve ter 10 chars)
    std::cout << "Stage: creating hotel\n";
    svGer.criarHotel(Hotel(Codigo("hoteltest1"), Nome("Hotel Teste"), Endereco("Rua Teste"), Telefone("+551199999999")));
    std::cout << "Stage: hotel created\n";

    // criar quarto 101
    std::cout << "Stage: creating quarto\n";
    Quarto q(Numero("101"), Capacidade("2"), Dinheiro("150.00"), Ramal("05"));
    if (!svGer.criarQuarto(Codigo("hoteltest1"), q)) std::cout << "createQuarto returned false\n";
    std::cout << "Stage: quarto created\n";

    // criar gerente/hospede usado para reservas
    std::cout << "Stage: creating gerente\n";
    Gerente g(Nome("Teste Gerente"), Email("gerente@test.com"), Ramal("01"), Senha("A1b!2"));
    if (!svPessoal.criarUsuario(g)) std::cout << "criarUsuario gerente returned false\n";
    std::cout << "Stage: gerente created\n";

    // Primeiro reserva
    Hospede hosp1(g.getNome(), g.getEmail(), Endereco("Rua 1"), Cartao("4532015112830366"));
    Reserva r1; r1.setCodigo(Codigo("reserve001")); r1.setHospede(&hosp1);
        Hotel htemp; htemp.setCodigo(Codigo("hoteltest1"));
    svGer.lerHotel(htemp);
    Hotel hlocal(Codigo("hoteltest1"), htemp.getNome(), htemp.getEndereco(), htemp.getTelefone());
    r1.setHotel(&hlocal);
    r1.setQuarto(&q);
    r1.setDatas(Data("01-JAN-2026"), Data("03-JAN-2026"));

    bool ok1 = false;
    try { ok1 = svReserva.criarReserva(hosp1, r1); } catch (const std::exception &ex) { std::cout<<"Exception during criarReserva1: "<<ex.what()<<"\n"; }
    std::cout << "criarReserva1 returned: " << ok1 << "\n";

    // Segundo reserva
    Hospede hosp2(g.getNome(), g.getEmail(), Endereco("Rua 1"), Cartao("4532015112830366"));
    Reserva r2; r2.setCodigo(Codigo("reserve002")); r2.setHospede(&hosp2);
    r2.setHotel(&hlocal);
    r2.setQuarto(&q);
    r2.setDatas(Data("04-JAN-2026"), Data("06-JAN-2026"));
    bool ok2 = false;
    try { ok2 = svReserva.criarReserva(hosp2, r2); } catch (const std::exception &ex) { std::cout<<"Exception during criarReserva2: "<<ex.what()<<"\n"; }
    std::cout << "criarReserva2 returned: " << ok2 << "\n";

    // listar
    auto lista = svReserva.listarReservas(g.getEmail());
    std::cout << "Lista size: " << lista.size() << "\n";
    for (auto &res : lista) {
        res.exibirTudo();
    }
    } catch (const std::exception &ex) {
        std::cout << "Uncaught exception in main: " << ex.what() << "\n";
    }
    return 0;
}
