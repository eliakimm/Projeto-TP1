#include "dominios.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

//DOMINIO:
//set para classes derivadas que utilizam valores do tipo inteiro;
void Dominio::setValor(int valor){
    validar(valor);
    this->valor= valor;
}

//DOMINIOSTR:
//set para classes derivadas que utilizam valores do tipo string;
void DominioStr::setValor(string valor){
    validar(valor);
    this->valor= valor;
}

// _______NOME_________
void Nome::validar(const string nome){
    // nomes autoexplicaticos
    if(nome.empty()) throw invalid_argument("Escreva algo!");  // Funciona
    if(nome.length() < 5 || nome.length() > 20) throw invalid_argument("Nome entre 5 a 20 letras."); // Funciona
    if(temNumero(nome)) throw invalid_argument("Sem numeros, robo!");  // Funciona
    if(ultimoEspaco(nome)) throw invalid_argument("Sem espaco no fim.");  // Funciona
    if(doisEspacos(nome)) throw invalid_argument("Dois espacos consecutivos.");  // Funciona
    if(!maiuscula(nome)) throw invalid_argument("Deve comecar com letra maiuscula.");  // Funciona
}

bool Nome::temNumero(const string nome){
    return any_of(nome.begin(), nome.end(), ::isdigit);
}

bool Nome::ultimoEspaco(const string nome){
    return !nome.empty() && isspace(nome.back());
}

bool Nome::doisEspacos(const string nome){
    for(size_t i = 0; i < nome.length() -1; i++){
        if(nome[i] == ' ' && nome[i+1] == ' '){
            return true;
        }
    }
    return false;
}

bool Nome::maiuscula(const string nome){
    if(!isupper(nome[0])) return false;
    for(size_t i = 1; i < nome.length(); i++){
        if(nome[i-1] == ' ' && !isupper(nome[i])) return false;
    }
    return true;
}

// _______EMAIL________
void Email::validar(const string email){
    if(email.empty()) throw invalid_argument("Cade o email?!");  // FuncionaM
    if(email.length() > 254) throw invalid_argument("Mucho email.");  // Funciona KKKK
    if(!temArroba(email)) throw invalid_argument("Apenas um '@'.");  // Funciona
    if(!emailCerto(email)) throw invalid_argument("Formato de email invalido."); // Funciona

    // fragmentando: 1- achaArroba, 2- extrai o que ta antes do @, 3- extrai depois do @
    size_t achaArroba = email.find('@');
    string parteLocal = email.substr(0, achaArroba);
    string dominio = email.substr(achaArroba + 1);

    if(!local(parteLocal)) throw invalid_argument("Local do email invalido.");
    if(!dominioCerto(dominio)) throw invalid_argument("Dominio do email invalido.");  // Funciona
}

bool Email::temArroba(const string email){
    int count = 0;
    for(char c : email){
        if(c == '@') count ++;  // so um arrombado
    }
    return count == 1;
}

bool Email::emailCerto(const string email){
    size_t achaArroba = email.find('@');
    if(achaArroba == string::npos || achaArroba == 0 || achaArroba == email.length() -1){  // nao comeca ou terminar com @
        return false; // npos é pra indicar algo que nao foi encontrado
    }

    // fragmentado
    string local = email.substr(0, achaArroba);
    string dominio = email.substr(achaArroba + 1);

    // locsl
    // teste do ponto ou hifen no comeco
    if(local[0] == '.' || local[0] == '-' || local.back() == '.' || local.back() == '-'){
        return false;
    }
    // dois pontos ou hifens ou ponte e hifen etc
    for(size_t i = 0; i < local.length(); i++){
        char c = local[i];
        if(!isalnum(c) && c != '.' && c != '-'){
            return false;
        }

        if((c == '.' || c == '-') && (i + 1 >= local.length() || !isalnum(local[i + 1]))){
            return false;
        }
        if(i > 0 && (local[i - 1] == '.' || local[i - 1] == '==') && (c == '.' || c == '-')){
            return false;
        }
    }
    return true;
}

bool Email::local(const string local){
    if(local.empty() || local.length() > 64){
        return false;
    }
    for(char c : local){
        if(!isalnum(c) && c != '.' && c != '-'){
            return false;
        }
    }
    return true;
}

bool Email::dominioCerto(const string dominio){
    if(dominio.empty() || dominio.length() > 255){
        return false;
    }
    //fragmentar com vector para "analisar" cada parte do email
    vector<string> partes;
    size_t comeco = 0;
    size_t fim = dominio.find('.');  // acha o primeiro ponto

    while(fim != string::npos){  // npos é pra indicar algo que nao foi encontrada
        // separa o comeco do fim
        string parte = dominio.substr(comeco, fim - comeco);
        // valida cada parte
        if(parte.empty() || parte[0] == '-' || parte.back() == '-'){
            return false;
        }

        for(char c : parte){
            if(!isalnum(c) && c != '-'){
                return false;
            }
        }

        partes.push_back(parte);
        comeco = fim + 1;
        fim = dominio.find('.', comeco);
    }
    // extensao
    string extensao = dominio.substr(comeco);
    if(extensao.empty() || extensao.front() == '-' || extensao.back() == '-'){
        return false;
    }


    for(char l : extensao){
        if(!isalnum(l) && l != '-'){
            return false;
        }
    }

    partes.push_back(extensao);
    return partes.size() >= 2;  // aqui vai checar se o emal tem duas 'partes'
}

// ______TELEFONE______
void Telefone::validar(const string telefone){
    if (telefone.empty()) {
        throw invalid_argument("Passa teu celular!");
    }
    if(!tamanho(telefone)){
        throw invalid_argument("Precisa de 11 digitos!");
    }
    if(!all_of(telefone.begin(), telefone.end(), ::isdigit)){
        throw invalid_argument("Apenas numeros.");
    }
    if(!DDD(telefone)) {
        throw invalid_argument("Insira o DDD.");
    }
}

bool Telefone::tamanho(const string telefone){
    return telefone.length() == 11;
}

bool Telefone::DDD(const string telefone){
    // pelo menos dois digitos pro ddd7
    if(telefone.length() < 2){
        return false;
    }
    string ddd = telefone.substr(0, 2);
    int dddValor = stoi(ddd);  // stoi String to inteiro
    return (dddValor >= 11 && dddValor <= 99);
}

//CAPACIDADE:
//Verifica se o valor passado como parametro esta dentro do intervalo da capacidade de 1-4;
void Capacidade::validar(int valor){
    if(valor > 4 || valor < 1){
        throw invalid_argument("Valor inválido: [1 a 4]");
    }
}

//CARTAO:
//Verifica se o cartão é valido de acordo com o algoritimo de luhn;
void Cartao::validar(string valor){
    if(valor.length() != 16){
        throw invalid_argument("cartao invalido");
    }

    int cont= 0;

    for(int j= 15; j >= 0; j--){
        int digito= valor[j] - '0';
        int pos= 15 - j;
        if(pos%2 == 1){
            digito*=2;
            if(digito > 9){
                digito-=9;
            }
        }
        cont+= digito;
    }

    if(cont%10 != 0){
        throw invalid_argument("cartao invalido");
    }
}

//CODIGO:
//Verifica se valor passado como parametro esta dentro das normas:
//Sequencia de 10 caracteres;
//Caracteres de a-z ou Digitos de 0-9;
void Codigo::validar(string valor){
    if(valor.length() != 10){
        throw invalid_argument("Codigo invalido!");
    }
    for(int i= 0; i < 10; i++){
        if(!isdigit(valor[i]) && !isalpha(valor[i])){
            throw invalid_argument("Codigo invalido!");
        }
    }
}

//DATA:
//Verifica se o mês está de acordo com o formato imposto;
void Data::mes_dia(string mes, int dia){

    vector<string> meses = {
        "JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
        "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"
    };

    vector<string> meses_30_dias= {"FEV", "ABR", "JUN", "SET", "NOV"};

    if(dia > 31 || dia <= 0){//Verifica se o dia é valido;
        throw invalid_argument("Dia invalido\n(1-31)");
    }

    if(find(meses.begin(), meses.end(), mes) == meses.end()){//Verifica se o mes existe;
        throw invalid_argument("Mês inválido\n(Mês é JAN, FEV, MAR, ABR, MAI, JUN, JUL, AGO, SET, OUT, NOV ou DEZ)");
    }

    //Verifica se o mês tem os dias correspondentes;
    if((find(meses_30_dias.begin(), meses_30_dias.end(), mes) != meses_30_dias.end() && dia == 31) || (mes == "FEV" && dia > 29)){
        throw invalid_argument("Mês inválido\n(O mês digitado não tem 30/31 dias)");
    }

}

//Verifica se ano em questão é um ano bissexto retornando um valor booleano;
bool Data::bissexto(int ano){
    return (ano%4 == 0 && ano%10 != 0) || (ano%400 == 0);
}

void Data::validar(string data){

    for(int i= 0; i < data.length(); i++){//Troca as letras do mês para maiúculo;
        if(isalpha(data[i])){
            data[i]= toupper(data[i]);
        }
    }

    //Divide a data em substring's para verificação;
    //stoi() converte o tipo de string para inteiro;
    int dia= stoi(data.substr(0,2));
    string mes= data.substr(3,3);
    int ano= stoi(data.substr(7,9));


    mes_dia(mes, dia);//Verficação de dia e mes;


    if(ano < 2000 || ano > 2999){//Validade de ano;
        throw invalid_argument("Ano inválido\n(2000-2999)");
    }

    if(mes == "FEV" && dia == 29 && !bissexto(ano)){//Verifica se o ano é bissexto;
        throw invalid_argument("O ano digitado não é bissexto!");
    }
}

//DINHEIRO:
//Verifica o valor convetido em inteiro está dentro dos limites estabelecidos para armazena-lo;
void Dinheiro::validar(int valor){
    if(valor < 1 || valor > 100000000){
        throw invalid_argument("Valor invalido\n(0.01 a 1000000.00)");
    }
}

//Recebe o valor em float e converte para inteiro de forma a garantir que não haja erros de arredondamento;
void Dinheiro::setValor(double valor){
    int valor_centavos= static_cast<int>(round(valor * 100));
    validar(valor_centavos);
    this->valor= valor_centavos;
}

//ENDEREÇO:
//
//Verifica se o digito em questão é valido retornando um valor true ou false;
bool Endereco::digito_valido(char valor){
    return isdigit(valor) || isalpha(valor) || valor == '.' || valor == ',' || valor == ' ';
}

void Endereco::validar(string ender){
    int tam= ender.length();
    if(tam < 5 || tam > 30){//Verifica se o tamanho do endereço é valido;
        throw invalid_argument("Endereço inválido\n(5-30 caracteres)");
    }
    for(int i= 0; i < tam; i++){
        if(!digito_valido(ender[i])){//Verifica se o digito é valido;
            throw invalid_argument("Endereço inválido\n(A-Z, 0-9, [, .])");
        }
        if(ender[0] == ' ' || ender[0] == ',' || ender[0] == '.'){//Verifica se o 1° digito é valido;
            throw invalid_argument("Endereço inválido\n(A-Z, 0-9, [, .])");
        }
        if(ender[tam - 1] == ' ' || ender[tam - 1] == ',' || ender[tam - 1] == '.'){//Verifica se o ultimo digito é valido;
            throw invalid_argument("Endereço inválido\n(A-Z, 0-9, [, .])");
        }
        if(ender[i] == ',' && (ender[i+1] == ',' || ender[i+1] == '.')){//Virgula não é seguida por virgula ou ponto;
            throw invalid_argument("Endereço inválido\n(A-Z, 0-9, [, .])");
        }
        if(ender[i] == '.' && (ender[i+1] == ',' || ender[i+1] == '.')){//Ponto não é seguido por virgula ou ponto;
            throw invalid_argument("Endereço inválido\n(A-Z, 0-9, [, .])");
        }
        if(ender[i] == ' ' && (!isdigit(ender[i+1]) && !isalpha(ender[i+1]))){//Espaço em branco não é seguido por virgula ou ponto;
            throw invalid_argument("Endereço inválido\n(A-Z, 0-9, [, .])");
        }

    }
}

//NÚMERO:
//Valida o numero no seguintes critérios:
void Numero::validar(string valor){
    //Verifica o tamanho da string do número (tem que ser == 3);
    //Também verifica se há digitos não numéricos;
    for(int i= 0; i < 3; i++){
        if(!isdigit(valor[i])){
            throw invalid_argument("Número inválido\n(Sequência de 3 digitos numéricos: 001 a 999)");
        }
    }

    //Verifica se: [1 < valor > 999];
    if(stoi(valor) < 1 || stoi(valor) > 999){
        throw invalid_argument("Número inválido\n(Sequência de 3 digitos numéricos: 001 a 999)");
    }
}

//RAMAL:
//Valida o numero no seguintes critérios:
void Ramal::validar(string valor){
    //Verifica o tamanho da string do número (tem que ser == 2);
    //Também verifica se há digitos não numéricos;
    for(int i= 0; i < 2; i++){
        if(!isdigit(valor[i])){
            throw invalid_argument("Número inválido\n(Sequência de 2 digitos numéricos: 00 a 50)");
        }
    }

    //Verifica se: [0 <= valor > 50];
    if(stoi(valor) <= 0 || stoi(valor) > 50){
        throw invalid_argument("Número inválido\n(Sequência de 2 digitos numéricos: 00 a 50)");
    }
}

//SENHA:
//Verifica a presença de caracteres especiais permitidos e retorna um valor booleano;
bool Senha::isespecial(char valor){

    vector<char> caracteres= {'!', '"',  '#', '$',  '%', '&', '?'};

    if(find(caracteres.begin(), caracteres.end(), valor) == caracteres.end()) return false;

    return true;
}

//Verifica se há a presença de pelo menos um de cada tipo: letra maiúscula e minúscula, número e caracteres especiais;
bool Senha::check_digitos(string valor){

    int contN= 0, cont_maiscula= 0, cont_minuscula= 0, cont_especial= 0;

    for(int i= 0; i < TAMANHO; i++){
        if(isdigit(valor[i])) contN++;
        if(isalpha(valor[i]) && isupper(valor[i])) cont_maiscula++;
        if(isalpha(valor[i]) && islower(valor[i])) cont_minuscula++;
        if(isespecial(valor[i])) cont_especial++;
    }

    return contN > 0 && cont_maiscula > 0 && cont_minuscula > 0 && cont_especial > 0;

}

void Senha::validar(string valor){
    if(valor.length() != TAMANHO) throw invalid_argument("Senha inválida\n(5 caracteres)");

    for(int i= 0; i < TAMANHO; i++){
        if(!isespecial(valor[i]) && !isdigit(valor[i]) && !isalpha(valor[i])){
            throw invalid_argument("Senha inválida\n(5 caracteres: pelo menos uma letra minúscula (a-z), uma letra maiúscula (A-Z), um dígito (0-9) e um caracter especial.)");
        }
        if(isdigit(valor[i]) && isdigit(valor[i+1])){
            throw invalid_argument("Senha inválida\n(Número não pode ser seguido por número)");
        }
        if(isalpha(valor[i]) && isalpha(valor[i+1])){
            throw invalid_argument("Senha inválida\n(Letra não pode ser seguida por letra)");
        }
        if(isespecial(valor[i]) && isespecial(valor[i+1])){
            throw invalid_argument("Senha inválida\n(Caracteres especiais não podem ser seguidos por caracteres especiais)");
        }
    }

    if(!check_digitos(valor)){
        throw invalid_argument("Senha inválida\n(5 caracteres: pelo menos uma letra minúscula (a-z), uma letra maiúscula (A-Z), um dígito (0-9) e um caracter especial.)");
    }

}

