#include <iostream>
#include "interfaces.hpp"
#include "controladoria.hpp"
#include "stubs.hpp"
#include "apresentacao_menu.hpp"

int main() {
    // Instâncias de apresentacao
    CntrApresentacaoMenu menu;
    CntrApresentacaoPessoal apPessoal;
    CntrApresentacaoGerenciamento apGerenciamento;
    CntrApresentacaoReserva apReserva;

    // Instâncias de servico (stubs)
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

    // Injecao de dependências - Menu (Servicos)
    menu.setAutenticacao(&svAuth);
    menu.setPessoalServico(&svPessoal);
    menu.setGerenciamentoServico(&svGerenciamento);
    menu.setReservaServico(&svReserva);

    // Injecao de dependências - Menu (Controladores de Apresentacao)
    menu.setPessoal(&apPessoal);
    menu.setGerenciamento(&apGerenciamento);
    menu.setReserva(&apReserva);

    // Injecao de dependências - Controladores de Apresentacao
    apPessoal.setPessoal(&svPessoal);
    apGerenciamento.setGerenciamento(&svGerenciamento);
    apReserva.setReserva(&svReserva);
    // Injetar o servico de gerenciamento tambem em apReserva para verificacoes de hotel/quarto
    apReserva.setGerenciamento(&svGerenciamento);

    // Executa o menu principal
    menu.executar();

    return 0;
}
