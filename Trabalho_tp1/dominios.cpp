#include "dominios.hpp"
#include <map>

// ==================== Nome ====================
void Nome::validar(const string& nome) {
    // 5-20 chars, letras (incluindo acentuadas) e espacos. Primeiro caractere de cada termo e maiuscula.
    // Resto da palavra em minuscula. Espaco seguido por letra. Sem espaco no inicio/fim.
    if (nome.size() < 5 || nome.size() > 20) throw invalid_argument("Nome: tamanho deve estar entre 5 e 20 caracteres");
    if (nome.front() == ' ' || nome.back() == ' ') throw invalid_argument("Nome: nao pode iniciar ou terminar com espaco");

    bool inicioTermo = true;
    for (size_t i = 0; i < nome.size(); ++i) {
        unsigned char uc = static_cast<unsigned char>(nome[i]);
        if (nome[i] == ' ') {
            if (i + 1 < nome.size() && nome[i+1] == ' ') throw invalid_argument("Nome: espacos consecutivos nao permitidos");
            inicioTermo = true;
        } else if (isalpha(uc) || uc >= 128) {  // ASCII >= 128 permite acentos (UTF-8 single-byte)
            // Aceita letras normais e caracteres acentuados (Latin-1)
            // Validacao simplificada: apenas permite letras e acentos, sem verificar maiuscula/minuscula para acentos
            if (inicioTermo) {
                if (isalpha(uc) && islower(uc)) throw invalid_argument("Nome: primeiro caractere de cada termo deve ser maiuscula");
                inicioTermo = false;
            } else {
                if (isalpha(uc) && isupper(uc)) throw invalid_argument("Nome: resto do termo deve estar em minuscula");
            }
        } else {
            throw invalid_argument("Nome: apenas letras e espacos permitidos");
        }
    }
}

bool Nome::temNumero(const string& nome) {
    for (char c : nome) if (isdigit(static_cast<unsigned char>(c))) return true;
    return false;
}
bool Nome::ultimoEspaco(const string& nome) {
    return !nome.empty() && nome.back() == ' ';
}
bool Nome::doisEspacos(const string& nome) {
    return nome.find("  ") != string::npos;
}
bool Nome::maiuscula(const string& nome) {
    bool inicio = true;
    for (size_t i = 0; i < nome.size(); ++i) {
        char c = nome[i];
        if (inicio) {
            if (!isupper(static_cast<unsigned char>(c))) return false;
            inicio = false;
        } else if (c == ' ') {
            inicio = true;
        } else {
            // aceitar maiusculas ou minusculas no restante da palavra
        }
    }
    return true;
}

// ==================== Email ====================
void Email::validar(const string& email) {
    // Parte-local@dominio. Local: max 64 chars, letras/digitos/ponto/hifen, nao inicia/termina com ponto/hifen.
    // Ponto/hifen seguido por letra/digito. Dominio: max 255 chars, 1+ labels com '.', letras/digitos/hifen.
    if (email.empty() || email.size() > 254) throw invalid_argument("Email: tamanho invalido");
    size_t at = email.find('@');
    if (at == string::npos || at == 0 || at >= email.size() - 1)
        throw invalid_argument("Email: formato invalido (local@dominio)");

    string local = email.substr(0, at);
    string domain = email.substr(at + 1);

    if (local.size() > 64) throw invalid_argument("Email: parte local nao pode exceder 64 caracteres");
    if (domain.size() > 255) throw invalid_argument("Email: dominio nao pode exceder 255 caracteres");

    // Validar parte local
    if (local.front() == '.' || local.front() == '-' || local.back() == '.' || local.back() == '-')
        throw invalid_argument("Email: parte local nao pode iniciar/terminar com ponto ou hifen");
    for (size_t i = 0; i < local.size(); ++i) {
        char c = local[i];
        if (!(isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-'))
            throw invalid_argument("Email: caractere invalido na parte local");
        if ((c == '.' || c == '-') && i + 1 < local.size()) {
            char next = local[i+1];
            if (!(isalnum(static_cast<unsigned char>(next))))
                throw invalid_argument("Email: ponto/hifen deve ser seguido por letra ou digito");
        }
    }

    // Validar dominio: labels separadas por '.'
    size_t start = 0;
    int labelCount = 0;
    while (start < domain.size()) {
        size_t dot = domain.find('.', start);
        if (dot == string::npos) dot = domain.size();
        string label = domain.substr(start, dot - start);

        if (label.empty() || label.size() > 63) throw invalid_argument("Email: label de dominio invalido");
        if (label.front() == '-' || label.back() == '-') throw invalid_argument("Email: label nao pode iniciar/terminar com hifen");

        for (char c : label) {
            if (!(isalnum(static_cast<unsigned char>(c)) || c == '-'))
                throw invalid_argument("Email: caractere invalido em dominio");
        }
        labelCount++;
        start = dot + 1;
    }
    if (labelCount < 2) throw invalid_argument("Email: dominio deve ter pelo menos um ponto");
}

// ==================== Ramal ====================
void Ramal::validar(const string& ramal) {
    // Especificacao: 00 a 50 (assumimos formato com dois digitos de 00 a 50)
    if (ramal.size() != 2) throw invalid_argument("Ramal deve ter exatamente 2 digitos");
    for (char c : ramal) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Ramal deve conter apenas digitos");
    int val = stoi(ramal);
    if (val < 0 || val > 50) throw invalid_argument("Ramal fora do intervalo permitido");
}

// ==================== Senha ====================
void Senha::validar(const string& senha) {
    // Especificacao: exatamente 5 caracteres.
    // Pode conter: letras (maiuscula, minuscula), digitos, caracteres especiais (! " # $ % & ?).
    // Deve conter maiuscula, minuscula, digito. Letras nao consecutivas, digitos nao consecutivos.
    if (senha.size() != 5) throw invalid_argument("Senha deve ter exatamente 5 caracteres");

    const string especiais = "!\"#$%&?";
    bool temMaiuscula = false, temMinuscula = false, temDigito = false;

    for (size_t i = 0; i < senha.size(); ++i) {
        unsigned char uc = static_cast<unsigned char>(senha[i]);
        char c = senha[i];
        bool isLet = isalpha(uc);
        bool isDig = isdigit(uc);
        bool isEsp = (especiais.find(c) != string::npos);

        if (!isLet && !isDig && !isEsp)
            throw invalid_argument("Senha contem caractere invalido");

        if (isLet) {
            if (isupper(uc)) temMaiuscula = true;
            if (islower(uc)) temMinuscula = true;
            // verificar se letra e seguida por letra
            if (i + 1 < senha.size() && isalpha(static_cast<unsigned char>(senha[i+1])))
                throw invalid_argument("Senha nao pode ter duas letras consecutivas");
        }
        if (isDig) {
            temDigito = true;
            // verificar se digito e seguido por digito
            if (i + 1 < senha.size() && isdigit(static_cast<unsigned char>(senha[i+1])))
                throw invalid_argument("Senha nao pode ter dois digitos consecutivos");
        }
    }

    if (!(temMaiuscula && temMinuscula && temDigito))
        throw invalid_argument("Senha deve conter maiuscula, minuscula e digito");
}

// ==================== Codigo ====================
void Codigo::validar(const string& codigo) {
    // 10 caracteres (letras a-z ou digitos 0-9)
    if (codigo.size() != 10) throw invalid_argument("Codigo deve ter 10 caracteres");
    for (char c : codigo) {
        if (!(islower(static_cast<unsigned char>(c)) || isdigit(static_cast<unsigned char>(c))))
            throw invalid_argument("Codigo contem caracteres invalidos (apenas a-z e 0-9)");
    }
}

// ==================== Numero ====================
void Numero::validar(const string& numero) {
    // Numero do quarto: 001 a 999 (formato 3 digitos)
    if (numero.size() != 3) throw invalid_argument("Numero deve ter 3 digitos (formato 001-999)");
    for (char c : numero) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Numero invalido");
    int val = stoi(numero);
    if (val < 1 || val > 999) throw invalid_argument("Numero fora do intervalo 001-999");
}

// ==================== Endereco ====================
void Endereco::validar(const string& endereco) {
    // 5-30 chars: letras (a-z A-Z), digitos (0-9), virgula, ponto, espaco.
    // Virgula/ponto nao seguidos por virgula/ponto. Espaco seguido por letra/digito.
    // Primeiro/ultimo caracter nao pode ser virgula/ponto/espaco.
    if (endereco.size() < 5 || endereco.size() > 30) throw invalid_argument("Endereco: tamanho deve estar entre 5 e 30");
    if (endereco.front() == ' ' || endereco.front() == ',' || endereco.front() == '.')
        throw invalid_argument("Endereco: nao pode iniciar com espaco, virgula ou ponto");
    if (endereco.back() == ' ' || endereco.back() == ',' || endereco.back() == '.')
        throw invalid_argument("Endereco: nao pode terminar com espaco, virgula ou ponto");

    for (size_t i = 0; i < endereco.size(); ++i) {
        unsigned char uc = static_cast<unsigned char>(endereco[i]);
        char c = endereco[i];

        if (!(isalnum(uc) || c == ' ' || c == ',' || c == '.' || c == '-')) {
            throw invalid_argument("Endereco: caractere invalido");
        }

        if ((c == ',' || c == '.') && i + 1 < endereco.size()) {
            char next = endereco[i+1];
            if (next == ',' || next == '.') throw invalid_argument("Endereco: virgula/ponto nao pode ser seguido por virgula/ponto");
        }

        if (c == ' ' && i + 1 < endereco.size()) {
            char next = endereco[i+1];
            if (!(isalnum(static_cast<unsigned char>(next)))) throw invalid_argument("Endereco: espaco deve ser seguido por letra ou digito");
        }
    }
}

// ==================== Data ====================
void Data::validar(const string& data) {
    // Formato: DD-MMM-AAAA (dia 1-31, mes abreviado (case-insensitive), ano 2000-2999).
    // Validacao de bissexto.
    if (data.size() != 11) throw invalid_argument("Data tamanho invalido");
    if (data[2] != '-' || data[6] != '-') throw invalid_argument("Separador de data invalido");

    string sday = data.substr(0, 2);
    string smonth = data.substr(3, 3);
    string syear = data.substr(7, 4);

    for (char c : sday) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Dia invalido");
    for (char c : syear) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Ano invalido");

    int day = stoi(sday);
    int year = stoi(syear);

    if (day < 1 || day > 31) throw invalid_argument("Dia invalido");
    if (year < 2000 || year > 2999) throw invalid_argument("Ano fora do intervalo permitido");

    // Normalizar para title case
    string smonth_normalized = smonth;
    if (!smonth_normalized.empty()) {
        smonth_normalized[0] = toupper(static_cast<unsigned char>(smonth_normalized[0]));
        for (size_t i = 1; i < smonth_normalized.size(); ++i) {
            smonth_normalized[i] = tolower(static_cast<unsigned char>(smonth_normalized[i]));
        }
    }

    // Mapear nome do mes para numero
    static const map<string, int> meses = {
        {"Jan", 1}, {"Fev", 2}, {"Mar", 3}, {"Abr", 4}, {"Mai", 5}, {"Jun", 6},
        {"Jul", 7}, {"Ago", 8}, {"Set", 9}, {"Out", 10}, {"Nov", 11}, {"Dez", 12}
    };

    auto it = meses.find(smonth_normalized);
    if (it == meses.end()) throw invalid_argument("Mes invalido");
    int month = it->second;

    // Validar dia para o mes especificado
    int mdays = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) mdays = 30;
    else if (month == 2) {
        bool bissexto = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
        mdays = bissexto ? 29 : 28;
    }
    if (day > mdays) throw invalid_argument("Dia invalido para o mes/ano especificado");
}

// ==================== Telefone ====================
void Telefone::validar(const string& telefone) {
    // Formato +DDD... (apenas digitos apos '+'). Assumimos entre 8 e 15 digitos (padrao E.164 aproximado)
    if (telefone.size() < 2) throw invalid_argument("Telefone invalido");
    if (telefone[0] != '+') throw invalid_argument("Telefone deve comecar com '+'");
    string digits = telefone.substr(1);
    if (digits.size() < 8 || digits.size() > 15) throw invalid_argument("Telefone deve ter entre 8 e 15 digitos apos '+'");
    for (char c : digits) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Telefone deve conter apenas digitos apos '+'");
}

// ==================== Cartao ====================
void Cartao::validar(const string& cartao) {
    // 16 digitos + algoritmo de Luhn
    if (cartao.size() != 16) throw invalid_argument("Cartao deve ter 16 digitos");
    for (char c : cartao) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Cartao deve conter apenas digitos");
    // Luhn
    int sum = 0;
    bool alt = false;
    for (int i = (int)cartao.size() - 1; i >= 0; --i) {
        int d = cartao[i] - '0';
        if (alt) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        sum += d;
        alt = !alt;
    }
    if (sum % 10 != 0) throw invalid_argument("Cartao invalido pelo algoritmo de Luhn");
}

// ==================== Capacidade ====================
void Capacidade::validar(const string& capacidade) {
    // Apenas valores 1 a 4
    if (capacidade.empty()) throw invalid_argument("Capacidade vazia");
    for (char c : capacidade) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Capacidade deve conter apenas digitos");
    int cap = stoi(capacidade);
    if (cap < 1 || cap > 4) throw invalid_argument("Capacidade deve estar entre 1 e 4");
}

// ==================== Dinheiro ====================
void Dinheiro::validar(const string& dinheiro) {
    // Centavos inteiros, valor entre 1 e 100000000 (0.01 a 1000000.00).
    // Formato: numero com duas casas decimais, ex: 123.45
    if (dinheiro.empty()) throw invalid_argument("Valor vazio");
    size_t pos = dinheiro.find('.');
    if (pos == string::npos) throw invalid_argument("Dinheiro deve conter duas casas decimais separadas por '.'");
    string intpart = dinheiro.substr(0, pos);
    string decpart = dinheiro.substr(pos+1);
    if (decpart.size() != 2) throw invalid_argument("Dinheiro deve ter exatamente duas casas decimais");
    if (intpart.empty()) intpart = "0";
    for (char c : intpart) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Parte inteira contem caracteres invalidos");
    for (char c : decpart) if (!isdigit(static_cast<unsigned char>(c))) throw invalid_argument("Parte decimal contem caracteres invalidos");
    try {
        long long reais = stoll(intpart);
        int cents = stoi(decpart);
        long long totalCents = reais * 100 + cents;
        if (totalCents < 1) throw invalid_argument("Valor minimo e 0.01");
        if (totalCents > 100000000) throw invalid_argument("Valor maximo excedido (1000000.00)");
    } catch (const exception&) {
        throw invalid_argument("Valor invalido");
    }
}
