#include "entidades.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <map>
#include <ctime>

// ==================== Pessoa ====================
Pessoa::Pessoa(const Nome& n, const Email& e) : nome(n), email(e) {}

void Pessoa::setNome(const Nome& nomeNovo) { nome = nomeNovo; }
void Pessoa::setEmail(const Email& emailNovo) { email = emailNovo; }

Nome Pessoa::getNome() const { return nome; }
Email Pessoa::getEmail() const { return email; }

void Pessoa::exibirTudo() const {
    cout << "Nome: " << nome.getValor() << "\n"
              << "Email: " << email.getValor() << "\n";
}

// ==================== Gerente ====================
Gerente::Gerente(const Nome& n, const Email& e, const Ramal& r, const Senha& s)
    : Pessoa(n, e), ramal(r), senha(s) {}

void Gerente::setRamal(Ramal r) { ramal = r; }
void Gerente::setSenha(Senha s) { senha = s; }

Ramal Gerente::getRamal() const { return ramal; }
Senha Gerente::getSenha() const { return senha; }

void Gerente::exibirTudo() const {
    Pessoa::exibirTudo();
    cout << "Ramal: " << ramal.getValor() << "\n"
              << "Senha: " << senha.getValor() << "\n";
}

// ==================== Hospede ====================
Hospede::Hospede(const Nome& n, const Email& e, const Endereco& end, const Cartao& c)
    : Pessoa(n, e), endereco(end), cartao(c) {}

void Hospede::setEndereco(const Endereco& e) { endereco = e; }
void Hospede::setCartao(const Cartao& c)     { cartao   = c; }

Endereco Hospede::getEndereco() const { return endereco; }
Cartao   Hospede::getCartao()   const { return cartao; }

void Hospede::exibirTudo() const {
    Pessoa::exibirTudo();
    cout << "Endereco: " << endereco.getValor() << "\n"
              << "Cartao: " << cartao.getValor() << "\n";
}

// ==================== Hotel ====================
Hotel::Hotel(const Codigo& c, const Nome& n, const Endereco& e, const Telefone& t)
    : codigo(c), nome(n), endereco(e), telefone(t) {}

void Hotel::setGerenteEmail(const Email& em) { gerenteEmail = em; }
Email Hotel::getGerenteEmail() const { return gerenteEmail; }

void Hotel::setCodigo(const Codigo& c) { codigo   = c; }
void Hotel::setNome(const Nome& n)     { nome     = n; }
void Hotel::setEndereco(const Endereco& e) { endereco = e; }
void Hotel::setTelefone(const Telefone& t) { telefone = t; }

Codigo   Hotel::getCodigo()   const { return codigo; }
Nome     Hotel::getNome()     const { return nome; }
Endereco Hotel::getEndereco() const { return endereco; }
Telefone Hotel::getTelefone() const { return telefone; }

void Hotel::exibirTudo() const {
    cout << "Codigo: " << codigo.getValor() << "\n"
              << "Nome: " << nome.getValor() << "\n"
              << "Endereco: " << endereco.getValor() << "\n"
              << "Telefone: " << telefone.getValor() << "\n";
}

// ==================== Quarto ====================
Quarto::Quarto(const Numero& num, const Capacidade& cap, const Dinheiro& v, const Ramal& ram)
    : numero(num), capacidade(cap), valor(v), ramal(ram) {}

void Quarto::setNumero(const Numero& n)      { numero    = n; }
void Quarto::setCapacidade(const Capacidade& c) { capacidade = c; }
void Quarto::setValor(const Dinheiro& v)     { valor     = v; }
void Quarto::setRamal(const Ramal& r)        { ramal     = r; }

Numero    Quarto::getNumero()     const { return numero; }
Capacidade Quarto::getCapacidade() const { return capacidade; }
Dinheiro  Quarto::getValor()      const { return valor; }
Ramal     Quarto::getRamal()      const { return ramal; }

void Quarto::exibirTudo() const {
    cout << "Quarto numero: " << numero.getValor() << "\n"
              << "Capacidade: "  << capacidade.getValor() << "\n"
              << "Valor: "       << valor.getValor() << "\n"
              << "Ramal: "       << ramal.getValor() << "\n";
}

// ==================== Reserva ====================
Reserva::Reserva(const Codigo& c, Hospede* h, Hotel* ho, Quarto* q,
                 const Data& checkin, const Data& checkout)
    : codigo(c), hospede(h), hotel(ho), quarto(q),
      dataCheckin(checkin), dataCheckout(checkout) {}

void Reserva::setCodigo(const Codigo& c) { codigo = c; }
void Reserva::setHospede(Hospede* h)     { hospede = h; }
void Reserva::setHotel(Hotel* ho)        { hotel   = ho; }
void Reserva::setQuarto(Quarto* q)       { quarto  = q; }

// Helper: calcula dias entre duas datas no formato DD-MMM-AAAA
// Meses: JAN, FEV, MAR, ABR, MAI, JUN, JUL, AGO, SET, OUT, NOV, DEZ
static int diasEntre(const string& d1, const string& d2) {
    static const map<string, int> meses = {
        {"JAN", 0}, {"FEV", 1}, {"MAR", 2}, {"ABR", 3}, {"MAI", 4}, {"JUN", 5},
        {"JUL", 6}, {"AGO", 7}, {"SET", 8}, {"OUT", 9}, {"NOV", 10}, {"DEZ", 11}
    };
    auto parse = [&](const string& d) -> tm {
        tm tm = {};
        tm.tm_mday = stoi(d.substr(0,2));
        string mesStr = d.substr(3,3);
        for (char& c : mesStr) c = toupper(c);
        tm.tm_mon = meses.at(mesStr);
        tm.tm_year = stoi(d.substr(7,4)) - 1900;
        // Fixar hora ao meio-dia para evitar problemas com horarios de verao
        tm.tm_hour = 12;
        tm.tm_min = 0;
        tm.tm_sec = 0;
        tm.tm_isdst = -1;
        return tm;
    };
    tm tm1 = parse(d1);
    tm tm2 = parse(d2);
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    double diff = 0.0;
    if (time1 == (time_t)(-1) || time2 == (time_t)(-1)) {
        return 0;
    } else {
        diff = difftime(time2, time1) / (60*60*24);
        return static_cast<int>(diff);
    }
}

void Reserva::setDatas(const Data& checkin, const Data& checkout) {
    int dias = diasEntre(checkin.getValor(), checkout.getValor());
    if (dias <= 0) throw invalid_argument("Data invalida");
    dataCheckin = checkin;
    dataCheckout = checkout;
}

Codigo Reserva::getCodigo() const { return codigo; }
Hospede* Reserva::getHospede() const { return hospede; }
Hotel* Reserva::getHotel() const { return hotel; }
Quarto* Reserva::getQuarto() const { return quarto; }
Data Reserva::getCheckin() const { return dataCheckin; }
Data Reserva::getCheckout() const { return dataCheckout; }

void Reserva::exibir_reserva() {
    cout << dataCheckin.getValor() << " | RESERVA:" << endl;
    if (hospede) cout << "Nome do hospede: " << hospede->getNome().getValor() << endl;
    if (quarto) cout << "Quarto: " << quarto->getNumero().getValor() << endl;
    if (quarto) cout << "Ramal: " << quarto->getRamal().getValor() << endl;
    // calcular valor total: dias * valor do quarto
    if (quarto) {
        int dias = diasEntre(dataCheckin.getValor(), dataCheckout.getValor());
        double valorUnit = stod(quarto->getValor().getValor());
        double total = dias * valorUnit;
        ostringstream oss;
        oss << fixed << setprecision(2) << total;
        cout << ": " << quarto->getValor().getValor() << endl;
        cout << "Dias: " << dias << endl;
        cout << "Valor total: " << oss.str() << endl;
    }
}

void Reserva::exibirTudo() const {
    cout << "Reserva codigo: " << codigo.getValor() << "\n";
    if (hospede) {
        cout << "Hospede: " << hospede->getNome().getValor()
                  << " (" << hospede->getEmail().getValor() << ")\n";
    } else {
        cout << "Hospede: (nenhum)\n";
    }
    if (hotel) {
        cout << "Hotel: " << hotel->getNome().getValor()
                  << " [" << hotel->getCodigo().getValor() << "]\n";
    } else {
        cout << "Hotel: (nenhum)\n";
    }
    if (quarto) {
        cout << "Quarto: " << quarto->getNumero().getValor() << "\n";
        cout << "Ramal: " << quarto->getRamal().getValor() << "\n";
    } else {
        cout << "Quarto: (nenhum)\n";
    }
    cout << "Check-in: "  << dataCheckin.getValor()
              << "\nCheck-out: " << dataCheckout.getValor() << "\n";
    // Valor total
    if (quarto) {
        int dias = diasEntre(dataCheckin.getValor(), dataCheckout.getValor());
        double valorUnit = stod(quarto->getValor().getValor());
        double total = dias * valorUnit;
        ostringstream oss;
        oss << fixed << setprecision(2) << total;
        cout << "Diaria: " << quarto->getValor().getValor() << "\n";
        cout << "Dias: " << dias << "\n";
        cout << "Valor total: " << oss.str() << "\n";
    }
}
