# Trabalho TP1 - Sistema de Gerenciamento de Hotéis

## 📋 Descrição

Sistema em C++17 para gerenciamento de hotéis com funcionalidades de:
- **Autenticação** de gerentes
- **CRUD** de gerentes, hotéis, quartos e hóspedes
- **Gerenciamento de reservas** com detecção de conflitos
- **Validação de domínios** (nome, email, ramal, senha, etc.)
- **Testes automatizados** com coverage completo

---

## 🔧 Compilação

### Pré-requisitos
- Compilador: `g++` (versão 7+)
- Sistema: Windows/Linux/macOS com bash
- Flags: C++17 com exceções habilitadas

### Compilar Aplicação Principal

```bash
cd c:\Users\Acer\Documents\Estudos\Meus_repositorios\Projeto-TP1\Trabalho_tp1
g++ -Wall -fexceptions -std=c++17 *.cpp -o Trabalho_tp1.exe
```

### Compilar Suite de Testes

```bash
# Testes de integração (18 testes)
g++ -Wall -fexceptions -std=c++17 *.cpp tests/test_all.cpp -o tests/test_all.exe

# Testes CRUD dedicados (Gerente, Hotel, Hóspede)
g++ -Wall -fexceptions -std=c++17 *.cpp tests/test_crud.cpp -o tests/test_crud.exe
```

---

## 🚀 Execução

### Aplicação Interativa

```bash
# Executar menu principal
./Trabalho_tp1.exe
```

**Fluxo do Menu:**
1. **Menu Principal** — Opções: 1 (Login), 2 (Sair)
2. **Autenticação** — Digite email e senha de um gerente registrado
3. **Menu Autenticado** — Opções:
   - 1: Menu Pessoal (CRUD de gerentes e hóspedes)
   - 2: Menu Gerenciamento (CRUD de hotéis e quartos)
   - 3: Menu Reserva (criar/listar/deletar reservas)
   - 4: Logout

**Dados Padrão (de `tests/test_all.cpp`):**
- **Gerente**: email=`gerente@hotel.com`, senha=`A1a$2`
- **Hóspede**: email=`hospede@email.com`, telefone=`11999999999`, cartão=`1111111111111111`

### Testes Automatizados

```bash
# Executar testes de integração (18 testes)
./tests/test_all.exe

# Executar testes CRUD (Gerente, Hotel, Hóspede)
./tests/test_crud.exe

# Ambos devem exibir "[PASS]" para cada caso
```

**Resultado Esperado:**
```
[PASS] Gerente: criar
[PASS] Gerente: autenticar
[PASS] Gerente: editar
...
[PASS] Hotel: deletar quartos
Fim dos testes.
```

---

## 📐 Regras de Validação de Domínios

| Domínio | Regra | Exemplo |
|---------|-------|---------|
| **Nome** | 5-20 caracteres, capitalizado | "João Silva" |
| **Email** | Formato RFC (user@domain.ext) | "joao@hotel.com" |
| **Ramal** | Exatamente 2 dígitos, 00-50 | "05", "25", "50" |
| **Senha** | 5 caracteres, sem consecutivos de mesmo tipo, requer: maiúscula, minúscula, dígito, especial (!\"#$%&?) | "A1a$2", "B2b%3" |
| **Código** | 10 caracteres alfanuméricos (a-z, 0-9) | "hotel12345" |
| **Número** | 1-4 dígitos | "101", "1" |
| **Endereço** | 5-40 caracteres | "Av. Paulista 1000" |
| **Data** | Formato DDMMYYYY | "15011990" |
| **Telefone** | 10-11 dígitos | "11999999999" |
| **Cartão** | 16 dígitos | "1111111111111111" |
| **Capacidade** | 1-10 pessoas | "4" |
| **Dinheiro** | 0.00 a 99999.99 | "1500.00" |

---

## 🏗️ Arquitetura

### Estrutura de Arquivos

```
├── dominios.{hpp,cpp}          # Value objects com validação
├── entidades.{hpp,cpp}         # Entities (Pessoa, Gerente, Hospede, Hotel, Quarto, Reserva)
├── interfaces.hpp              # Service contracts (IA_*/IS_*)
├── controladoria.cpp           # Presentation controllers
├── apresentacao_menu.cpp       # Menu driver
├── containers.hpp              # In-memory storage
├── stubs.{hpp,cpp}             # Service implementations
├── main.cpp                    # Entry point & wiring
└── tests/
    ├── test_all.cpp            # Integration tests (18 casos)
    └── test_crud.cpp           # Dedicated CRUD tests
```

### Padrões de Design

- **Domain-Driven Design**: Validação em value objects (dominios)
- **Repository Pattern**: Containers para persistência em memória
- **Service Locator**: Stub services gerenciados em main.cpp
- **Presentation Model**: Controllers separam UI da lógica
- **Cascade Delete**: Remoção de hóspede/hotel remove entidades relacionadas (reservas, quartos)

---

## ✅ Testes

### Test All (`test_all.exe`) — 18 Testes

1. **Autenticação**: Criar gerente, autenticar com sucesso
2. **CRUD Gerente**: Criar, editar, deletar
3. **CRUD Hotel**: Criar, editar, deletar
4. **CRUD Quarto**: Criar em hotel, editar, deletar
5. **CRUD Reserva**: Criar com validação de conflito
6. **Cascade Delete**: Remover hóspede/hotel e verificar limpeza de referências

### Test CRUD (`test_crud.exe`) — Testes Dedicados

Cada entidade (Gerente, Hotel, Hóspede) é testada com:
- **Create**: Inserir novo registro
- **Read**: Recuperar por chave primária
- **Edit**: Atualizar campo sem alterar PK
- **Delete**: Remover e verificar não-existência

---

## 🐛 Troubleshooting

### Problema: "Prompt não aparece / opção ignorada"
**Causa**: Buffering de entrada (mistura de `std::cin >>` e `getline`).
**Solução**: Usar `getline` para todos os inputs (já implementado).

### Problema: "Senha/Ramal inválido"
**Causa**: Formato de entrada errado.
**Verificar**:
- Ramal: exatamente 2 dígitos (00-50)
- Senha: 5 caracteres com: maiúscula, minúscula, dígito, especial

### Problema: "Compilação falha com símbolos não encontrados"
**Solução**: Incluir todos os `.cpp` na compilação:
```bash
g++ -Wall -fexceptions -std=c++17 *.cpp tests/test_all.cpp -o tests/test_all.exe
```

---

## 📚 Documentação

### Documentação Doxygen (HTML)
Todos os cabeçalhos (.hpp) contêm **anotações Doxygen** para geração automática de documentação.

**📁 Acessar documentação gerada:**
- Windows: `start html\index.html`
- macOS: `open html/index.html`
- Linux: `xdg-open html/index.html`

**📊 Arquivos principais:**
- `html/index.html` — Página inicial
- `html/classes.html` — Lista de classes
- `html/annotated.html` — Classes com detalhes
- `html/modules.html` — Módulos (defgroups)

**📖 Anotações Doxygen usadas:**
- `@class` — Definição de classe
- `@brief` — Descrição breve
- `@details` — Detalhes expandidos
- `@param` — Parâmetros de função
- `@return` — Valor retornado
- `@throw` — Exceções lançadas
- `@defgroup` — Agrupamento de módulos

**🔧 Gerar documentação novamente:**
```bash
doxygen Doxyfile
```

**📝 Documentação em Markdown:**
- `README.md` — Instruções de execução
- `CRITERIOS_AVALIACAO.md` — Verificação de critérios de avaliação
- `DOCUMENTACAO.md` — Índice de acesso rápido à documentação HTML

---

## 📝 Nota Sobre Reservas

- Reservas armazenam **referências não-proprietárias** (apontadores raw) para Hotel/Quarto/Hóspede
- Ao deletar um hóspede, todas as suas reservas são removidas automaticamente (cascade delete)
- Ao deletar um hotel, todas as suas reservas são removidas automaticamente

---

## 🎯 Status Atual

- ✅ Input handling robusto (getline para todos os inputs)
- ✅ Validação de domínios completa e testada
- ✅ CRUD funcional para todas entidades
- ✅ Testes automatizados (18 + dedicated CRUD)
- ✅ Documentação Doxygen em todos os headers
- ✅ Cascade delete operacional
- ⏳ PK protection (opcional) — impedir edição de chaves primárias

---

## 👤 Autor

Desenvolvido como parte do Trabalho Prático 1 (TP1).

---

**Última atualização**: Atual  
**Status**: ✅ Funcional | ✅ Testado | ✅ Documentado
