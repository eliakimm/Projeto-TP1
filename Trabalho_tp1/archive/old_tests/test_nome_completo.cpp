#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    cout << "=== Testando Validador de Nome ===" << endl;
    
    try {
        Nome n;
        n.setValor("Eliakim Silva");
        cout << "✓ Nome 'Eliakim Silva' aceito" << endl;
    } catch (const exception& e) {
        cout << "✗ Nome 'Eliakim Silva' rejeitado: " << e.what() << endl;
    }
    
    try {
        Nome n;
        n.setValor("João");
        cout << "✓ Nome 'João' aceito (5 chars)" << endl;
    } catch (const exception& e) {
        cout << "✗ Nome 'João' rejeitado: " << e.what() << endl;
    }
    
    try {
        Nome n;
        n.setValor("Ana");
        cout << "✗ Nome 'Ana' aceito (mas deveria ser rejeitado - 3 chars < 5)" << endl;
    } catch (const exception& e) {
        cout << "✓ Nome 'Ana' rejeitado corretamente: " << e.what() << endl;
    }
    
    return 0;
}
