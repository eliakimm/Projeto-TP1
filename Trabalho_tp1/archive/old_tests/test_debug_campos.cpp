#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    cout << "=== Testando EXATAMENTE os valores fornecidos ===" << endl;
    
    // Nome: Eliakim Silva (13 caracteres)
    try {
        Nome n;
        n.setValor("Eliakim Silva");
        cout << "✓ Nome: 'Eliakim Silva' (" << string("Eliakim Silva").size() << " chars)" << endl;
    } catch (const exception& e) {
        cout << "✗ Nome erro: " << e.what() << endl;
    }
    
    // Email: não informado - testando com um válido
    try {
        Email em;
        em.setValor("test@example.com");
        cout << "✓ Email: test@example.com" << endl;
    } catch (const exception& e) {
        cout << "✗ Email erro: " << e.what() << endl;
    }
    
    // Endereco: Samambaia Norte (16 caracteres)
    try {
        Endereco e;
        e.setValor("Samambaia Norte");
        cout << "✓ Endereco: 'Samambaia Norte' (" << string("Samambaia Norte").size() << " chars)" << endl;
    } catch (const exception& ex) {
        cout << "✗ Endereco erro: " << ex.what() << endl;
    }
    
    // Cartao: 5502096099523276
    try {
        Cartao c;
        c.setValor("5502096099523276");
        cout << "✓ Cartao: 5502096099523276" << endl;
    } catch (const exception& ex) {
        cout << "✗ Cartao erro: " << ex.what() << endl;
    }
    
    // Codigo hotel: hoteltest1 (10 caracteres)
    try {
        Codigo cod;
        cod.setValor("hoteltest1");
        cout << "✓ Codigo hotel: 'hoteltest1' (" << string("hoteltest1").size() << " chars)" << endl;
    } catch (const exception& ex) {
        cout << "✗ Codigo hotel erro: " << ex.what() << endl;
    }
    
    // Numero quarto: 125
    try {
        Numero num;
        num.setValor("125");
        cout << "✓ Numero quarto: 125" << endl;
    } catch (const exception& ex) {
        cout << "✗ Numero quarto erro: " << ex.what() << endl;
    }
    
    // Capacidade: 2
    try {
        Capacidade cap;
        cap.setValor(2);
        cout << "✓ Capacidade: 2" << endl;
    } catch (const exception& ex) {
        cout << "✗ Capacidade erro: " << ex.what() << endl;
    }
    
    // Data chegada: 01-Fev-2025
    try {
        Data d;
        d.setValor("01-Fev-2025");
        cout << "✓ Data chegada: 01-Fev-2025" << endl;
    } catch (const exception& ex) {
        cout << "✗ Data chegada erro: " << ex.what() << endl;
    }
    
    // Data partida: 04-Fev-2025
    try {
        Data d;
        d.setValor("04-Fev-2025");
        cout << "✓ Data partida: 04-Fev-2025" << endl;
    } catch (const exception& ex) {
        cout << "✗ Data partida erro: " << ex.what() << endl;
    }
    
    // Codigo reserva: reserva123 (10 caracteres)
    try {
        Codigo cod;
        cod.setValor("reserva123");
        cout << "✓ Codigo reserva: 'reserva123' (" << string("reserva123").size() << " chars)" << endl;
    } catch (const exception& ex) {
        cout << "✗ Codigo reserva erro: " << ex.what() << endl;
    }
    
    // Ramal (padrão)
    try {
        Ramal r;
        r.setValor("01");
        cout << "✓ Ramal: 01" << endl;
    } catch (const exception& ex) {
        cout << "✗ Ramal erro: " << ex.what() << endl;
    }
    
    // Dinheiro (preço por capacidade 2)
    try {
        Dinheiro d;
        d.setValor(220.00);
        cout << "✓ Dinheiro: 220.00" << endl;
    } catch (const exception& ex) {
        cout << "✗ Dinheiro erro: " << ex.what() << endl;
    }
    
    return 0;
}
