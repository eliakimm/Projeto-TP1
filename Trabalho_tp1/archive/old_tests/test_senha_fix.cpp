#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    Senha s;
    
    cout << "=== Testando Validador de Senha ===" << endl;
    
    // Teste principal: A1b!2
    try {
        s.setValor("A1b!2");
        cout << "✓ A1b!2 aceito" << endl;
    } catch (const exception& e) {
        cout << "✗ A1b!2 rejeitado: " << e.what() << endl;
    }
    
    // Teste: Letras consecutivas (deveria ser rejeitado)
    try {
        s.setValor("Ab1!2");
        cout << "✗ Ab1!2 aceito (erro - letras consecutivas)" << endl;
    } catch (const exception& e) {
        cout << "✓ Ab1!2 rejeitado corretamente: " << e.what() << endl;
    }
    
    // Teste: Dígitos consecutivos (deveria ser rejeitado)
    try {
        s.setValor("A12!b");
        cout << "✗ A12!b aceito (erro - dígitos consecutivos)" << endl;
    } catch (const exception& e) {
        cout << "✓ A12!b rejeitado corretamente: " << e.what() << endl;
    }
    
    // Teste: Sem maiúscula (deveria ser rejeitado)
    try {
        s.setValor("a1b!2");
        cout << "✗ a1b!2 aceito (erro - sem maiúscula)" << endl;
    } catch (const exception& e) {
        cout << "✓ a1b!2 rejeitado corretamente: " << e.what() << endl;
    }
    
    // Teste: Sem minúscula (deveria ser rejeitado)
    try {
        s.setValor("A1B!2");
        cout << "✗ A1B!2 aceito (erro - sem minúscula)" << endl;
    } catch (const exception& e) {
        cout << "✓ A1B!2 rejeitado corretamente: " << e.what() << endl;
    }
    
    // Teste: Sem dígito (deveria ser rejeitado)
    try {
        s.setValor("Abc!$");
        cout << "✗ Abc!$ aceito (erro - sem dígito)" << endl;
    } catch (const exception& e) {
        cout << "✓ Abc!$ rejeitado corretamente: " << e.what() << endl;
    }
    
    return 0;
}
