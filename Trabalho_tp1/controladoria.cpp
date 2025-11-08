#include "controladoria.hpp"
#include <iostream>
using namespace std;

CntrApresentacaoAutenticacao::CntrApresentacaoAutenticacao() : cntrServicoAutenticacao(nullptr){}

CntrApresentacaoPessoal::CntrApresentacaoPessoal() : cntrServicoPessoal(nullptr){}

CntrApresentacaoGerenciamento::CntrApresentacaoGerenciamento() : cntrServicoGerenciamento(nullptr){}

CntrApresentacaoReserva::CntrApresentacaoReserva() : cntrServicoReserva(nullptr){}


void CntrApresentacaoAuteticacao::setAutenticar(IS_Autenticacao* servico){
    cntrServicoAutenticacao = servico;
}

void CntrApresentacaoPessoal::setPessoal(IS_Pessoal* servico){
    cntrServicoPessoal = servico;
}

void CntrApresentacaoGerenciamento::setGerenciamento(IS_Gerenciamento* servico){
    cntrServicoGerenciamento = servico;
}

// implementacao autenticador
bool CntrApresentacaoAuteticacao::autenticarGerente(){
    /**
    * 1 bloco de verificacao de seguranca
    * Verifica se o ponteiro para o servico foi configurado
    * 'se cntrServicoAutenticacao for nullptr'
    * e uma precondicao essencial antes de usar o servico
    * retorna false imediatamente se nao estiver configurado
    */
    if(!cntrServicoAutenticacao){
        cout << "Erro: Autenticacao nao configurada!\n" << endl;
        return false;
    }

    /**
    * 2 bloco declaracao das variaveis
    * emailTempo/senhaTempo: strings temporárias para leitura do usuário
    * email/senha: objetos de domínio que farão as validações
    * Separamos a leitura (strings) da validação (objetos de domínio)
    */
    string emailTempo, senhaTempo;
    Email email;
    Senha senha;

    /**
    * 3 bloco interface com o usuario
    * Mostra cabeçalho para orientar o usuário
    * Solicita email e senha via terminal
    * Os dados ficam temporariamente em strings
    */
    cout << "*** TELA DE AUTENTICACAO ***" << endl;
    cout << "Email: ";
    cin >> emailTempo;
    cout << "Senha: ";
    cin >> senhaTempo;

    /**
    * 4 bloco tratamento de excecoes
    * Aqui suas validações de dominios.cpp são executadas!
    * Se emailtempo for inválido, setValor() lança exceção
    * Se senhatempo for inválida, setValor() lança exceção
    * As exceções são capturadas pelo catch abaixo
    */
    try{
        email.setValor(emailTempo);
        senha.setValor(senhaTempo);

        /**
        * feedback do usuario
        * informa o resultado da operacao pro usuario
        */
        bool autenticado = cntrServicoAutenticacao->autenticar(email, senha);
        if(autenticado){
            cout << "Sucesso na autenticacao." << endl;
        } else{
        cout << "email ou senha invalidos." << endl;
        }
        return autenticado;
    /**
    * 5 bloco pega os erros
    * vei pega os erros, ora pombas!
    */
    } catch(const exception& exce){
        cout << "Erro de validacao: " << exce.what() << endl;
        return false;
    }
}

// PESSOAL
bool CntrServicoPessoal::criarUsuario(Gerente gerente){
    static vector<Gerente> usuarios;

    for(size_t i = 0; i < usuarios.size(); i++){
        string emailVelho = usuarios[i].getEmail().getValor();
        string emailNovo = gerente.getEmail().getValor();

        if(emailVelho == emailNovo){
            return false;
        }
    }

    usuarios.push_back(gerente);
    return true;
}

bool CntrServicoPessoal::lerUsuario(Gerente gerente){
    static vector<Gerente> usuarios;

    for(size_t i = 0; i < usuarios.size(); i++){
        string emailNaLista = usuarios[i].getEmail().getValor();
        string emailProcurado = gerente.getEmail().getValor();

        if(emailNaLista == emailProcurado){
            gerente = usuarios[i];
            return true;
        }
    }
    return false;
}

bool CntrServicoPessoal::editarUsuario(Gerente gerente){
    for(size_t i = 0; i < usuarios.size(); i++){
        if(usuarios[i].getEmail().getValor() == gerente.getEmail().getValor()){
            usuarios[i] = gerente;
            return true;
        }
    }
    return false;
}

bool CntrServicoPessoal::excluirUsuario(Email email){
    for(size_t i = 0; i < usuarios.size(); i++){
        if(usuarios[i].getEmail().getValor() == email.getValor()){
            usuarios.erase(usuario.begin() + 1); // remove o elementp
            return true;
        }
    }
    return false;
}

// depois dos metodos feitos aqui vai ser a execução
void CntrApresentacaoPessoal::executar(const Email& email){
    if(!cntrServicoPessoal){
        cout << "erro: servico pessoal nao configurado.\n" << endl;
        return;
    }

    int escola;
    do{
        cout << "*** GERENCIAR PERFIL ***" << endl;
        cout << "[1] - Ver dados pessoais." << endl;
        cout << "[2] - Editar perfil." << endl;
        cout << "[3] - Excluir conta." << endl;
        cout << "[4] - Voltar." << endl;
        cout << "Sua escolha: " << endl;
        cin >> escolha;

        switch(escolha){
            case 1:
            {
                Gerente gerente;
                gerente.setEmail(email);

                if(cntrServicoPessoal->lerUsuario(gerente)){
                    cout << "Nome: " << gerente.getNome() << endl;
                    cout << "Email: " << gerente.getEmail().getValor() << endl;
                } else {
                    cout << "Usuario não encontrado!" << endl;
                }
                break;
            }
            case 2:
            {
                Gerente gerente;
                gerente.setEmail(email);

                // Primeiro busca os dados atuais
                if(cntrServicoPessoal->lerUsuario(gerente)){
                    string novoNome;
                    cout << "Nome atual: " << gerente.getNome() << endl;
                    cout << "Novo nome: ";
                    cin >> novoNome;

                    gerente.setNome(novoNome);

                    if(cntrServicoPessoal->editarUsuario(gerente)){
                        cout << "Dados atualizados com sucesso!" << endl;
                    } else {
                        cout << "Erro ao atualizar dados!" << endl;
                    }
                } else {
                    cout << "Usuario nao encontrado!" << endl;
                }
                break;
            }
            case 3:
            {
                char confirmacao;
                cout << "Tem certeza que deseja excluir sua conta? (S/N): ";
                cin >> confirmacao;

                if(confirmacao == 's' || confirmacao == 'S') {
                    if(cntrServicoPessoal->excluirUsuario(email)) {
                        cout << "Conta excluida com sucesso!" << endl;
                        return;
                    } else {
                        cout << "Erro ao excluir conta!" << endl;
                    }
                }
                break;
            }
            }
            case 0:
                cout << "Voltando ao menu principal..." << endl;
                break;


            default: cout << "Opcao invalida!" << endl;
    }
}



// implementacao pessoal
