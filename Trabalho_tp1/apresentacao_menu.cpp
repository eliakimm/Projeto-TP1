#include "apresentacao_menu.hpp"
#include <limits>
#include <cstdlib>
using namespace std;

// Implementacao completa e ASCII-only do modulo de apresentacao.

CntrApresentacaoMenu::CntrApresentacaoMenu()
  : srvAutenticacao(nullptr), srvPessoal(nullptr),
    srvGerenciamento(nullptr), srvReserva(nullptr),
    cntrPessoal(nullptr), cntrGerenciamento(nullptr), cntrReserva(nullptr) {}

// Setters de servicos
void CntrApresentacaoMenu::setAutenticacao(IS_Autenticacao* srv) { srvAutenticacao = srv; }
void CntrApresentacaoMenu::setPessoalServico(IS_Pessoal* srv) { srvPessoal = srv; }
void CntrApresentacaoMenu::setGerenciamentoServico(IS_Gerenciamento* srv) { srvGerenciamento = srv; }
void CntrApresentacaoMenu::setReservaServico(IS_Reserva* srv) { srvReserva = srv; }

// Setters de controladores de apresentacao
void CntrApresentacaoMenu::setPessoal(IA_Pessoal* cntr) { cntrPessoal = cntr; }
void CntrApresentacaoMenu::setGerenciamento(IA_Gerenciamento* cntr) { cntrGerenciamento = cntr; }
void CntrApresentacaoMenu::setReserva(IA_Reserva* cntr) { cntrReserva = cntr; }

// Auxiliares
void CntrApresentacaoMenu::limparTela() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void CntrApresentacaoMenu::exibirCabecalho() {

  cout << "==========================================\n";
  cout << "               BEM-VINDO AO               \n";
  cout << "  SISTEMA DE GERENCIAMENTO HOTELEIRO\n";
  cout << "==========================================\n";
}

void CntrApresentacaoMenu::pausar() {
  cout << "\nPressione ENTER para continuar...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Telas
void CntrApresentacaoMenu::telaMenuPrincipal() {
    int opcao;
    bool continuar = true;

  while (continuar) {
    limparTela();
    exibirCabecalho();

    cout << "[1] - Login de Gerente\n";
    cout << "[2] - Cadastro de Gerente\n";
    cout << "[3] - Sair do Sistema\n";
    cout << "==========================================\n";
    cout << "-> Escolha uma opcao: ";

    string line;
    getline(cin, line);
    try { opcao = stoi(line); } catch(...) {
      cout << "\nEntrada invalida. Tente novamente.\n";
      pausar();
      continue;
    }

    switch (opcao) {
      case 1: telaLogin(); break;
      case 2: telaCadastroGerente(); break;
      case 0:
        limparTela();
        cout << "\n==========================================\n";
        cout << "   Obrigado por usar nosso sistema!\n";
        cout << "         Ate logo!\n";
        cout << "==========================================\n\n";
        continuar = false;
        break;
      default:
        cout << "\n[X] Opcao invalida! Tente novamente.\n";
        pausar();
    }
  }
}

void CntrApresentacaoMenu::telaLogin() {
  limparTela();
  //exibirCabecalho();

  cout << "==========================================\n";
  cout << "             LOGIN DE GERENTE             \n";
  cout << "==========================================\n\n";

  string emailStr, senhaStr;
  cout << "Email: ";
  getline(cin, emailStr);
  cout << "Senha: ";
  getline(cin, senhaStr);

  try {
    Email email(emailStr);
    Senha senha(senhaStr);

    if (srvAutenticacao && srvAutenticacao->autenticar(email, senha)) {
      cout << "\n[OK] Autenticacao bem-sucedida!\n";
      pausar();
      telaMenuAutenticado(email);
    } else {
      cout << "\n[X] Email ou senha incorretos.\n";
      pausar();
    }
  } catch (const invalid_argument& e) {
    cout << "\n[X] Erro de validacao: " << e.what() << "\n";
    pausar();
  }
}

void CntrApresentacaoMenu::telaCadastroGerente() {
  limparTela();

  cout << "==========================================\n";
  cout << "         CADASTRO DE NOVO GERENTE         \n";
  cout << "==========================================\n";

  string nomeStr, emailStr, ramalStr, senhaStr;

  cout << "Nome completo: ";
  getline(cin, nomeStr);
  cout << "Email: ";
  getline(cin, emailStr);
  cout << "Ramal (00-50): ";
  getline(cin, ramalStr);
  cout << "Senha (5 caracteres, com maiuscula, minuscula, digito e especial): ";
  getline(cin, senhaStr);

  try {
    Nome nome(nomeStr);
    Email email(emailStr);
    Ramal ramal(ramalStr);
    Senha senha(senhaStr);

    Gerente gerente{nome, email, ramal, senha};

    if (srvPessoal && srvPessoal->criarUsuario(gerente)) {
      cout << "\n[OK] Gerente cadastrado com sucesso!\n";
    } else {
      cout << "\n[X] Erro ao cadastrar gerente. Verifique se o email ja existe.\n";
    }
  } catch (const invalid_argument& e) {
    cout << "\n[X] Erro de validacao: " << e.what() << "\n";
  }

  pausar();
}

void CntrApresentacaoMenu::telaMenuAutenticado(const Email& email) {
  int opcao;
  bool continuar = true;

  while (continuar) {
    limparTela();

    cout << "==========================================\n";
    cout << "              MENU PRICIPAL               \n";
    cout << "==========================================\n";
    cout << "Usuario Autenticado\n";
    cout << "Email: " << email.getValor() << "\n";
    cout << "==========================================\n";
    cout << "[1] - Gerenciar Dados Pessoais\n";
    cout << "[2] - Gerenciar Hoteis\n";
    cout << "[2] - Gerenciar Reservas\n";
    cout << "[0] - Logout\n";
    cout << "==========================================\n";
    cout << "-> Escolha uma opcao: ";

  string line;
  getline(cin, line);
    try { opcao = stoi(line); } catch(...) {
      cout << "\nEntrada invalida. Tente novamente.\n";
      pausar();
      continue;
    }

    switch (opcao) {
      case 1: if (cntrPessoal) cntrPessoal->executar(email); break;
      case 2: if (cntrGerenciamento) cntrGerenciamento->executar(email); break;
      case 3: if (cntrReserva) cntrReserva->executar(email); break;
      case 0:
        cout << "\n[OK] Logout realizado com sucesso!\n";
        pausar();
        continuar = false;
        break;
      default:
        cout << "\n[X] Opcao invalida! Tente novamente.\n";
        pausar();
    }
  }
}

// Metodo principal
void CntrApresentacaoMenu::executar() { telaMenuPrincipal(); }
