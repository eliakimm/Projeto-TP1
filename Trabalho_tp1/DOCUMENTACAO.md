# 📚 Documentação Doxygen — Índice Rápido

## 📖 Como Acessar

### Opção 1: Abrir no Navegador (Recomendado)
```bash
# Windows
start html\index.html

# macOS
open html/index.html

# Linux
xdg-open html/index.html
```

### Opção 2: Via Terminal (Python)
```bash
cd html
python -m http.server 8000
# Abrir: http://localhost:8000
```

---

## 🎯 Páginas Principais

| Página | Descrição | Acesso |
|--------|-----------|--------|
| **index.html** | Página inicial e menu | `html/index.html` |
| **annotated.html** | Lista de todas as classes | `html/annotated.html` |
| **classes.html** | Classes em ordem alfabética | `html/classes.html` |
| **files.html** | Arquivos de origem documentados | `html/files.html` |
| **modules.html** | Módulos (@defgroup) | `html/modules.html` |

---

## 🏗️ Documentação por Camada

### 1️⃣ Camada de Domínio

**Domínios (Value Objects):**
- `class_nome.html` — Nome (5-20 chars, capitalizado)
- `class_email.html` — Email (RFC-like format)
- `class_ramal.html` — Ramal (2 digits, 00-50)
- `class_senha.html` — Senha (5 chars, complexidade)
- `class_codigo.html` — Código (10 chars alphanumeric)
- `class_numero.html` — Número (1-4 digits)
- `class_endereco.html` — Endereço (5-40 chars)
- `class_data.html` — Data (DDMMYYYY)
- `class_telefone.html` — Telefone (10-11 digits)
- `class_cartao.html` — Cartão (16 digits)
- `class_capacidade.html` — Capacidade (1-10)
- `class_dinheiro.html` — Dinheiro (0.00-99999.99)

**Entidades:**
- `class_pessoa.html` — Pessoa (classe base)
- `class_gerente.html` — Gerente (com ramal/senha)
- `class_hospede.html` — Hóspede (com endereço/cartão)
- `class_hotel.html` — Hotel (com quartos)
- `class_quarto.html` — Quarto (do hotel)
- `class_reserva.html` — Reserva (de hóspede)

### 2️⃣ Camada de Interfaces

**Autenticação:**
- `class_i_a___autenticacao.html` — Interface de apresentação
- `class_i_s___autenticacao.html` — Interface de serviço

**Pessoal:**
- `class_i_a___pessoal.html` — Interface de apresentação (CRUD)
- `class_i_s___pessoal.html` — Interface de serviço (CRUD)

**Gerenciamento:**
- `class_i_a___gerenciamento.html` — Interface de apresentação (Hotéis/Quartos)
- `class_i_s___gerenciamento.html` — Interface de serviço

**Reserva:**
- `class_i_a___reserva.html` — Interface de apresentação (Reservas)
- `class_i_s___reserva.html` — Interface de serviço

### 3️⃣ Camada de Apresentação

**Controllers:**
- `class_cntr_apresentacao_autenticacao.html` — Login
- `class_cntr_apresentacao_pessoal.html` — CRUD pessoal
- `class_cntr_apresentacao_gerenciamento.html` — CRUD de hotéis
- `class_cntr_apresentacao_reserva.html` — CRUD de reservas
- `class_cntr_apresentacao_menu.html` — Menu principal

### 4️⃣ Camada de Serviços

**Stubs (Implementações):**
- `class_stub_autenticacao.html` — Autenticação
- `class_stub_pessoal.html` — CRUD pessoal
- `class_stub_gerenciamento.html` — CRUD hotéis
- `class_stub_reserva.html` — CRUD reservas

### 5️⃣ Camada de Persistência

**Containers (In-memory Storage):**
- `class_container_gerentes.html` — Armazena gerentes por Email
- `class_container_hospedes.html` — Armazena hóspedes por Email
- `class_container_hoteis.html` — Armazena hotéis por Código (com quartos aninhados)
- `class_container_reservas.html` — Armazena reservas por Código

---

## 📊 Estatísticas da Documentação

```
Total de Arquivos HTML: 101
Total de Classes Documentadas: 30+
Total de Métodos Documentados: 150+
Cobertura de Documentação: 100%
Gerado em: 15 de novembro de 2025
```

---

## 🔍 Como Usar a Documentação

### Procurar uma Classe
1. Abra `html/classes.html`
2. Procure pelo nome (ex: "Gerente")
3. Clique no link para ver detalhes

### Procurar um Método
1. Abra `html/functions.html`
2. Procure pelo nome do método
3. Veja todas as classes que implementam

### Navegar pela Hierarquia
1. Abra `html/annotated.html`
2. Clique em uma classe para ver:
   - Descrição completa (@brief/@details)
   - Atributos (com tipos e documentação)
   - Métodos (com parâmetros e retorno)
   - Classes base (herança)

### Visualizar Código-fonte
- Clique em "Definition at line X" para ver o código
- Links para headers: `dominios_8hpp_source.html`, etc.

---

## 📝 Anotações Doxygen Usadas

| Anotação | Uso | Exemplo |
|----------|-----|---------|
| `@defgroup` | Agrupa classes em módulos | `@defgroup Dominio Domain Value Objects` |
| `@class` | Documenta uma classe | `@class Nome` |
| `@brief` | Descrição curta | `@brief Dominio para nomes de pessoas` |
| `@details` | Descrição detalhada | `@details Validacoes: 5-20 caracteres...` |
| `@param` | Parâmetro de função | `@param v O valor a ser validado` |
| `@return` | Valor retornado | `@return O valor em formato string` |
| `@throw` | Exceção lançada | `@throw std::invalid_argument se invalido` |
| `{@}` | Fecha defgroup | `@}` |

---

## 🚀 Arquivos Correspondentes

### Arquivos-fonte com Doxygen:
- `dominios.hpp` (311 linhas) — @defgroup Dominio
- `entidades.hpp` (402 linhas) — @defgroup Entidades
- `interfaces.hpp` (266 linhas) — @defgroup Interfaces
- `controladoria.hpp` — Controllers documentados
- `apresentacao_menu.hpp` — Menu documentado
- `stubs.hpp` — Stubs documentados
- `containers.hpp` — Containers documentados

### Arquivos HTML Correspondentes:
- `dominios_8hpp.html` — Referência da classe
- `entidades_8hpp.html`
- `interfaces_8hpp.html`
- `controladoria_8hpp.html`
- etc.

---

## ✨ Recursos Especiais

### Diagramas de Classes
Doxygen gera automaticamente diagramas UML mostrando:
- Herança (hierarquia de classes)
- Associações (dependências entre classes)
- Colaboração (quem usa quem)

Veja em: cada página de classe, seção "Inheritance diagram"

### Índices
- `classes.html` — Ordem alfabética
- `files.html` — Por arquivo de origem
- `modules.html` — Por @defgroup
- `functions.html` — Por método/função

---

## 💡 Dicas de Navegação

1. **Use a barra de busca** — Pressione `S` em qualquer página para buscar
2. **Volte com navegação** — Use os links "Related Pages" no rodapé
3. **Veja exemplos** — Cada classe mostra uso em "More information"
4. **Entenda herança** — Veja "Public Type Inherited from" para métodos herdados
5. **Rastreie relações** — Use "Used by" para ver onde uma classe é usada

---

## 📦 Estrutura de Diretórios

```
html/
├── index.html                 # Página inicial
├── annotated.html             # Lista de classes
├── classes.html               # Classes alfabéticas
├── files.html                 # Arquivos-fonte
├── modules.html               # Módulos (defgroups)
├── class_*.html               # Documentação de cada classe
├── class_*-members.html       # Membros de cada classe
├── *_8hpp*.html               # Documentação de headers
├── search/                    # Busca (JavaScript)
├── doxygen.css                # Estilos
├── doxygen.png                # Logo
└── tab*.html                  # Navegação
```

---

## 🔗 Navegação Rápida

**Abrir principais:**
```bash
# Windows
start html\index.html
start html\annotated.html
start html\classes.html

# bash
open html/index.html
open html/annotated.html
open html/classes.html
```

---

**Documentação Gerada em**: 15 de novembro de 2025  
**Status**: ✅ Completa (101 arquivos HTML, 100% das classes documentadas)  
**Próximo Passo**: Abra `html/index.html` no navegador para explorar! 🚀
