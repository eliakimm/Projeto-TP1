#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <iostream>
#include <chrono>


using namespace std;

class Dominio{
private:
    int valor;
    virtual void validar(int)= 0;
public:
    void setValor(int);
    int getValor() const {return valor;}
};

class DominioStr{
private:
    string valor;
    virtual void validar(string)=0;
public:
    void setValor(string);
    string getValor()  const {return valor;}
};

// MATHEUS ESTEVE AQUI:
// nome
class Nome : public DominioStr {
private:
    void validar(const string nome) override;

    bool temNumero(const string nome);
    bool ultimoEspaco(const string nome);
    bool doisEspacos(const string nome);
    bool maiuscula(const string nome);
};

class Email : public DominioStr{
private:
    void validar(const string email) override;

    bool temArroba(const string email);
    bool emailCerto(const std::string email);
    bool local(const std::string local);
    bool dominioCerto(const std::string dominio);
    bool pontoCom(const std::string extensao);
};

class Telefone : public DominioStr{
private:
    void validar(const string telefone) override;

    bool DDD(const string telefone);
    bool tamanho(const string telefone);
};

class Capacidade : public Dominio{
private:
    void validar(int);
//public:
    //void setValor(int);
    //int getValor() const {return valor;}
};

class Cartao : public DominioStr{
private:
    void validar(string);
};

class Codigo : public DominioStr{
private:
    void validar(string);
};

class Data : public DominioStr{
private:
    void validar(string);
    void mes_dia(string, int);
    bool bissexto(int);
};

class Dinheiro{
private:
    int valor;
    void validar(int);
public:
    void setValor(double);
    double getValor() const {return valor/100.0;}
};

class Endereco : public DominioStr{
private:
    void validar(string);
    bool digito_valido(char);
};

class Numero : public DominioStr{
private:
    void validar(string);
};

class Ramal : public DominioStr{
private:
    void validar(string);
};

class Senha : public DominioStr{
private:
    void validar(string);
    bool isespecial(char);
    bool check_digitos(string);
    static const int TAMANHO= 5;
};

#endif // DOMINIOS_HPP_INCLUDED
