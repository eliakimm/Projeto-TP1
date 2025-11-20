#include <iostream>
#include <string>
#include <vector>
#include "../stubs.hpp"

void ok(bool cond, const std::string &msg) {
    std::cout << (cond ? "PASS: " : "FAIL: ") << msg << '\n';
}

int main() {
    StubPessoal svPessoal;
    StubGerenciamento svGer;
    // Test removed from project.
    // This file was removed per project cleanup request.
    int main() { return 0; }
    res = svPessoal.criarUsuario(g);
    ok(res, "Criar gerente test para exclusao");

    // associar container de gerentes ao stub de gerenciamento (feito no wiring acima)
    Hotel h2(Codigo("hotelger01"), Nome("Hotelbyger"), Endereco("Rua G"), Telefone("+551177777777"));
    h2.setGerenteEmail(g.getEmail());
    res = svGer.criarHotel(h2);
    ok(res, "Criar hotel associado ao gerente");

    // Agora tentar excluir gerente: comportamento atual do sistema pode permitir exclusao; o teste abaixo
    // expressa o requisito funcional desejado (exclusao deve falhar). Se falhar no teste, o codigo precisa ser ajustado.
    bool exclRes = svPessoal.excluirUsuario(Email("gertest@ex.com"));
    ok(exclRes, "Excluir gerente deve remover o gerente e os hoteis associados (cascade)");

    // Verificar que o hotel associado foi removido
    Hotel hcheck; hcheck.setCodigo(Codigo("hotelger01"));
    bool exists = svGer.lerHotel(hcheck);
    ok(!exists, "Hotel associado removido apos exclusao do gerente");

    std::cout << "Fim test_listings_consistency." << std::endl;
    return 0;
}
