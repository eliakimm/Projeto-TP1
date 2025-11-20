#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    Senha s;
    
    cout << "=== Testando Validador de Senha ===" << endl;
    
    // Teste 1: Esperado passado na conversa anterior
    try {
        s.setValor("A1b2C");
        cout << "✓ A1b2C aceito" << endl;
    } catch (const exception& e) {
        cout << "✗ A1b2C rejeitado: " << e.what() << endl;
    }
    
    // Teste 2: Letras consecutivas (deveria ser rejeitado)
    try {
        s.setValor("AB1c2");
        cout << "✗ AB1c2 aceito (erro - letras consecutivas)" << endl;
    } catch (const exception& e) {
        cout << "✓ AB1c2 rejeitado: " << e.what() << endl;
    }
    
    // Teste 3: Dígitos consecutivos (deveria ser rejeitado)
    try {
        s.setValor("A12bC");
        cout << "✗ A12bC aceito (erro - dígitos consecutivos)" << endl;
    } catch (const exception& e) {
        cout << "✓ A12bC rejeitado: " << e.what() << endl;
    }
    
    // Teste 4: Sem maiúscula (deveria ser rejeitado)
    try {
        s.setValor("a1b2c");
        cout << "✗ a1b2c aceito (erro - sem maiúscula)" << endl;
    } catch (const exception& e) {
        cout << "✓ a1b2c rejeitado: " << e.what() << endl;
    }
    
    // Teste 5: Sem minúscula (deveria ser rejeitado)
    try {
        s.setValor("A1B2C");
        cout << "✗ A1B2C aceito (erro - sem minúscula)" << endl;
    } catch (const exception& e) {
        cout << "✓ A1B2C rejeitado: " << e.what() << endl;
    }
    
    // Teste 6: Sem dígito (deveria ser rejeitado)
    try {
        s.setValor("AbCdE");
        cout << "✗ AbCdE aceito (erro - sem dígito)" << endl;
    } catch (const exception& e) {
        cout << "✓ AbCdE rejeitado: " << e.what() << endl;
    }
    
    // Teste 7: Tamanho errado
    try {
        s.setValor("A1b2");
        cout << "✗ A1b2 aceito (erro - tamanho < 5)" << endl;
    } catch (const exception& e) {
        cout << "✓ A1b2 rejeitado: " << e.what() << endl;
    }
    
    // Teste 8: Padrão alternado perfeito
    try {
        s.setValor("a1B2c");
        cout << "✓ a1B2c aceito (alternado: minúscula, dígito, maiúscula, dígito, minúscula)" << endl;
    } catch (const exception& e) {
        cout << "✗ a1B2c rejeitado: " << e.what() << endl;
    }
    
    return 0;
}
