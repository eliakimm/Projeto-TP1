Usuário(s) de teste semeados automaticamente

Visão geral
- Um gerente e um hóspede de teste são semeados automaticamente pelo construtor de `StubPessoal`.

Credenciais
- Gerente:
  - Email: teste@hotel.com
  - Senha: A1b!2
- Hóspede:
  - Email: hospede@teste.com
  - Endereço: Rua Teste, 123
  - Cartão (teste): 4532015112830366

Como usar
- Ao criar uma instância de `StubPessoal` (ou quando o serviço/fixture criar uma), os usuários acima serão adicionados aos containers em memória.
- Para autenticar via `StubAutenticacao`, a aplicação precisa ter um `ContainerGerentes` apontado em `StubAutenticacao::setContainer(...)` ou usar o `getContainer()` do `StubPessoal`.

Exemplo rápido (pseudo):
- StubPessoal stub;
- StubAutenticacao auth;
- auth.setContainer(stub.getContainer());
- Email e("teste@hotel.com"); Senha s("A1b!2");
- bool ok = auth.autenticar(e, s); // deve retornar true

Observações
- As senhas e dados são apenas para testes locais. Nao usar em produção.
- Se os domínios validarem e lançarem exceção durante a semente, o construtor silencia o erro (try/catch) para não quebrar execuções automáticas.

Se quiser, eu posso:
- Adicionar uma rotina `tools/seed_test_users.cpp` para semear explicitamente via binário.
- Fazer o `StubPessoal` aceitar uma flag para ativar/desativar a seed (útil para testes isolados).
