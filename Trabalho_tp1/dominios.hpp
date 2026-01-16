#ifndef DOMINIOS_HPP
#define DOMINIOS_HPP

#include <string>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

/**
* @file dominios.hpp
* @brief Classes que encapsulam validacoes de dominio do sistema.
* @details Cada classe representa um tipo de dado do dominio, garantindo que apenas valores validos sejam armazenados.
*/

/**
 * @class DominioStr
 * @brief Classe base abstrata para objetos de dominio baseados em strings.
 * @details Define a interface para validacao e armazenamento de valores de dominio.
 *          Cada subclasse implementa sua propria logica de validacao.
 * @author Eliakim Pereira da Silva - 231021440
 */
class DominioStr {
private:
    string valor;
protected:
    virtual void validar(const string&) = 0;
public:
    /**
     * @brief Define e valida um novo valor.
     * @param v O valor a ser validado e armazenado.
     * @throw invalid_argument se o valor nao atender as regras de validacao.
     */
    void setValor(const string& v) { validar(v); valor = v; }

    /**
     * @brief Retorna o valor armazenado.
     * @return O valor em formato string.
     */
    string getValor() const { return valor; }
    virtual ~DominioStr() = default;
};


/**
 * @class Nome
 * @brief Dominio para nomes de pessoas.
 * @details Validacoes: 5-20 caracteres, apenas letras e espacos.
 *          Cada palavra deve comecar com maiuscula seguida de minusculas.
 *          Nao pode comecor ou terminar com espaco; nao pode ter dois espacos consecutivos.
 * @author Matheus Nunes Ferreira - 231021511
 */
class Nome : public DominioStr {
private:
    void validar(const string& nome) override;
    bool temNumero(const string& nome);
    bool ultimoEspaco(const string& nome);
    bool doisEspacos(const string& nome);
    bool maiuscula(const string& nome);
public:
    /**
     * @brief Constroi um Nome vazio.
     */
    Nome() = default;
    /**
     * @brief Constroi um Nome com validacao.
     * @param v Valor do nome a ser validado.
     * @throw invalid_argument se o nome nao atender as validacoes.
     */
    explicit Nome(const string& v) { setValor(v); }
};

/**
 * @class Email
 * @brief Dominio para endereco de email.
 * @details Validacoes: deve conter @, partes local e dominio validas.
 *          Dominio deve conter pelo menos um ponto e ter labels validos (1-63 caracteres).
 *          Caracteres permitidos: letras, digitos, . _ - + (local); letras, digitos, - (dominio).
 * @author Matheus Nunes Ferreira - 231021511
 */
class Email : public DominioStr {
private:
    void validar(const string& email) override;
public:
    /**
     * @brief Constroi um Email vazio.
     */
    Email() = default;
    /**
     * @brief Constroi um Email com validacao.
     * @param v Valor do email a ser validado.
     * @throw invalid_argument se o email nao atender as validacoes.
     */
    explicit Email(const string& v) { setValor(v); }
};

/**
 * @class Ramal
 * @brief Dominio para numero de ramal interno.
 * @details Validacoes: exatamente 2 digitos, intervalo 00-50.
 */
class Ramal : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& ramal) override;
public:
    /**
     * @brief Constroi um Ramal vazio.
     */
    Ramal() = default;
    /**
     * @brief Constroi um Ramal com validacao.
     * @param v Valor do ramal (00-50).
     * @throw invalid_argument se nao for um valor valido (2 digitos, 00-50).
     */
    explicit Ramal(const string& v) { setValor(v); }
};

/**
 * @class Senha
 * @brief Dominio para senha de usuario.
 * @details Validacoes: exatamente 5 caracteres.
 *          Deve conter maiuscula, minuscula, digito e caractere especial (!\"#$%&?).
 *          Restricoes: nao pode ter duas letras consecutivas; nao pode ter dois digitos consecutivos.
 */
class Senha : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& senha) override;
public:
    /**
     * @brief Constroi uma Senha vazia.
     */
    Senha() = default;
    /**
     * @brief Constroi uma Senha com validacao.
     * @param v Valor da senha a ser validado (exatamente 5 caracteres).
     * @throw invalid_argument se nao atender as regras de complexidade.
     */
    explicit Senha(const string& v) { setValor(v); }
};

/**
 * @class Codigo
 * @brief Dominio para codigos de hotel.
 * @details Validacoes: exatamente 10 caracteres em minusculas ou digitos (a-z, 0-9).
 */
class Codigo : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& codigo) override;
public:
    /**
     * @brief Constroi um Codigo vazio.
     */
    Codigo() = default;
    /**
     * @brief Constroi um Codigo com validacao.
     * @param v Valor do codigo (10 caracteres, a-z e 0-9).
     * @throw invalid_argument se nao atender o formato.
     */
    explicit Codigo(const string& v) { setValor(v); }
};

/**
 * @class Numero
 * @brief Dominio para numero de quarto.
 * @details Validacoes: exatamente 3 digitos, intervalo 001-999.
 */
class Numero : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& numero) override;
public:
    /**
     * @brief Constroi um Numero vazio.
     */
    Numero() = default;
    /**
     * @brief Constroi um Numero com validacao.
     * @param v Valor do numero (001-999).
     * @throw invalid_argument se nao for um numero valido (3 digitos, 001-999).
     */
    explicit Numero(const string& v) { setValor(v); }
};

/**
 * @class Endereco
 * @brief Dominio para endereco postal.
 * @details Validacoes: 5-30 caracteres, apenas letras, digitos, espacos e pontuacao basica (. , - #).
 *          Nao pode comecor ou terminar com espaco; nao pode ter espacos consecutivos.
 */
class Endereco : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& endereco) override;
public:
    /**
     * @brief Constroi um Endereco vazio.
     */
    Endereco() = default;
    /**
     * @brief Constroi um Endereco com validacao.
     * @param v Valor do endereco (5-30 caracteres).
     * @throw invalid_argument se nao atender as validacoes.
     */
    explicit Endereco(const string& v) { setValor(v); }
};

/**
 * @class Data
 * @brief Dominio para datas no formato DD/MM/AAAA ou DD-MM-AAAA.
 * @details Validacoes: ano 2000-2999, mes 1-12, dia valido para o mes/ano (include bissexto).
 */
class Data : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& data) override;
public:
    /**
     * @brief Constroi uma Data vazia.
     */
    Data() = default;
    /**
     * @brief Constroi uma Data com validacao.
     * @param v Valor da data no formato DD/MM/AAAA ou DD-MM-AAAA.
     * @throw invalid_argument se a data for invalida.
     */
    explicit Data(const string& v) { setValor(v); }
};

/**
 * @class Telefone
 * @brief Dominio para numero de telefone em formato internacional.
 * @details Validacoes: deve comecor com +, seguido de 8-15 digitos (padrao E.164 aproximado).
 * @author Matheus Nunes Ferreira - 231021511
 */
class Telefone : public DominioStr {
private:
    void validar(const string& telefone) override;
public:
    /**
     * @brief Constroi um Telefone vazio.
     */
    Telefone() = default;
    /**
     * @brief Constroi um Telefone com validacao.
     * @param v Valor do telefone (+DDDD... com 8-15 digitos).
     * @throw invalid_argument se nao atender o formato.
     */
    explicit Telefone(const string& v) { setValor(v); }
};

/**
 * @class Cartao
 * @brief Dominio para numero de cartao de credito.
 * @details Validacoes: exatamente 16 digitos, passa no algoritmo de Luhn.
 */
class Cartao : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& cartao) override;
public:
    /**
     * @brief Constroi um Cartao vazio.
     */
    Cartao() = default;
    /**
     * @brief Constroi um Cartao com validacao.
     * @param v Valor do cartao (16 digitos, validado com Luhn).
     * @throw invalid_argument se nao passar na validacao de Luhn ou formato.
     */
    explicit Cartao(const string& v) { setValor(v); }
};

/**
 * @class Capacidade
 * @brief Dominio para capacidade de hospedes em um quarto.
 * @details Validacoes: valor inteiro entre 1 e 4.
 */
class Capacidade : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& capacidade) override;
public:
    /**
     * @brief Constroi uma Capacidade vazia.
     */
    Capacidade() = default;
    /**
     * @brief Constroi uma Capacidade com validacao.
     * @param v Valor da capacidade (1-4).
     * @throw invalid_argument se nao for um valor valido (1-4).
     */
    explicit Capacidade(const string& v) { setValor(v); }
    using DominioStr::setValor;
    /**
     * @brief Sobrecarga para aceitar valores inteiros diretamente.
     */
    void setValor(int v) { DominioStr::setValor(to_string(v)); }
};

/**
 * @class Dinheiro
 * @brief Dominio para valores monetarios em reais.
 * @details Validacoes: formato com duas casas decimais (ex: 123.45).
 *          Valor minimo 0.01, maximo 1000000.00.
 */
class Dinheiro : public DominioStr {
/**
 * @author Eliakim Pereira da Silva - 231021440
 */
private:
    void validar(const string& dinheiro) override;
public:
    /**
     * @brief Constroi um Dinheiro vazio.
     */
    Dinheiro() = default;
    /**
     * @brief Constroi um Dinheiro com validacao.
     * @param v Valor monetario em formato XXX.YY (com ponto como separador decimal).
     * @throw invalid_argument se nao atender o formato ou intervalo valido.
     */
    explicit Dinheiro(const string& v) { setValor(v); }
    using DominioStr::setValor;
    /**
     * @brief Sobrecarga para aceitar valores em ponto flutuante.
     */
    void setValor(double v) {
        ostringstream oss;
        oss << fixed << setprecision(2) << v;
        DominioStr::setValor(oss.str());
    }
};

/**
 * @} // end Dominio defgroup
 */

#endif
