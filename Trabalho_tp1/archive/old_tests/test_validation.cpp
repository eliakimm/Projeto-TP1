#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    cout << "=== Testando cada campo ===" << endl;
    
    // Nome: Eliakim Silva
    try {
        Nome n;
        n.setValor("Eliakim Silva");
        cout << "✓ Nome: Eliakim Silva" << endl;
    } catch (const exception& e) {
        cout << "✗ Nome erro: " << e.what() << endl;
    }
    
    // Endereco: Samambaia Norte
    try {
        Endereco e;
        e.setValor("Samambaia Norte");
        cout << "✓ Endereco: Samambaia Norte" << endl;
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
    
    // Codigo hotel: hoteltest1
    try {
        Codigo cod;
        cod.setValor("hoteltest1");
        cout << "✓ Codigo hotel: hoteltest1" << endl;
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
    
    // Data chegada: 01/FEV/2025
    try {
        Data d;
        d.setValor("01-Fev-2025");
        cout << "✓ Data chegada: 01-Fev-2025" << endl;
    } catch (const exception& ex) {
        cout << "✗ Data chegada erro: " << ex.what() << endl;
    }
    
    // Data chegada com formato original: 01/FEV/2025
    try {
        Data d;
        d.setValor("01/FEV/2025");
        cout << "✓ Data chegada (formato alternativo): 01/FEV/2025" << endl;
    } catch (const exception& ex) {
        cout << "✗ Data chegada (alternativo) erro: " << ex.what() << endl;
    }
    
    // Data partida: 04/FEV/2025
    try {
        Data d;
        d.setValor("04-Fev-2025");
        cout << "✓ Data partida: 04-Fev-2025" << endl;
    } catch (const exception& ex) {
        cout << "✗ Data partida erro: " << ex.what() << endl;
    }
    
    // Codigo reserva: reserva123
    try {
        Codigo cod;
        cod.setValor("reserva123");
        cout << "✓ Codigo reserva: reserva123" << endl;
    } catch (const exception& ex) {
        cout << "✗ Codigo reserva erro: " << ex.what() << endl;
    }
    
    // Dinheiro: Testando valor por capacidade
    try {
        Dinheiro d;
        d.setValor(220.00);  // Preço padrão para capacidade 2
        cout << "✓ Dinheiro: 220.00" << endl;
    } catch (const exception& ex) {
        cout << "✗ Dinheiro erro: " << ex.what() << endl;
    }
    
    return 0;
}
