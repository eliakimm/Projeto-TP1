#include <iostream>
#include "interfaces.hpp"
#include "controladoria.hpp"
#include "stubs.hpp"
#include "apresentacao_menu.hpp"

int main() {
    // Instâncias de apresentação
    CntrApresentacaoMenu menu;
    CntrApresentacaoPessoal apPessoal;
    CntrApresentacaoGerenciamento apGerenciamento;
    CntrApresentacaoReserva apReserva;

    // Instâncias de serviço (stubs)
    StubAutenticacao svAuth;
    StubPessoal svPessoal;
    StubGerenciamento svGerenciamento;
    StubReserva svReserva;

    // Sincronizar container de gerentes entre Autenticacao e Pessoal
    svAuth.setContainer(svPessoal.getContainer());
    // Sincronizar container de reservas com pessoal e gerenciamento para integridade referencial
    svPessoal.setReservaContainer(svReserva.getContainer());
    svGerenciamento.setReservaContainer(svReserva.getContainer());
    // Sincronizar container de gerentes com gerenciamento para ler dados do gerente logado
    svGerenciamento.setGerentesContainer(svPessoal.getContainer());
    // Permitir que StubPessoal acesse o container de hoteis para remocoes em cascata
    svPessoal.setHotelContainer(svGerenciamento.getContainer());
    // Permitir que StubReserva acesse os containers de hospedes e hoteis para apontar reservas a instancias persistentes
    svReserva.setHospedeContainer(svPessoal.getHospedeContainer());
    svReserva.setHotelContainer(svGerenciamento.getContainer());

    // Criar hotel teste automaticamente
    svGerenciamento.criarHotel(Hotel(Codigo("hoteltest1"), Nome("Hotel Teste"), Endereco("Rua Teste"), Telefone("+5561991274713")));

    // Injeção de dependências - Menu (Serviços)
    menu.setAutenticacao(&svAuth);
    menu.setPessoalServico(&svPessoal);
    menu.setGerenciamentoServico(&svGerenciamento);
    menu.setReservaServico(&svReserva);

    // Injeção de dependências - Menu (Controladores de Apresentação)
    menu.setPessoal(&apPessoal);
    menu.setGerenciamento(&apGerenciamento);
    menu.setReserva(&apReserva);

    // Injeção de dependências - Controladores de Apresentação
    apPessoal.setPessoal(&svPessoal);
    apGerenciamento.setGerenciamento(&svGerenciamento);
    apReserva.setReserva(&svReserva);
    // Injetar o serviço de gerenciamento também em apReserva para verificacoes de hotel/quarto
    apReserva.setGerenciamento(&svGerenciamento);

    // Executa o menu principal
    menu.executar();

    return 0;
}
