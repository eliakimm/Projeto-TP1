#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    Telefone t;
    
    // Teste 1: Válido com 14 dígitos
    try {
        t.setValor("+5511999998888");
        cout << "✓ +5511999998888 aceito" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro: " << e.what() << endl;
    }
    
    // Teste 2: Válido com 8 dígitos (mínimo)
    try {
        t.setValor("+12345678");
        cout << "✓ +12345678 aceito (8 dígitos)" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro: " << e.what() << endl;
    }
    
    // Teste 3: Inválido - menos de 8 dígitos
    try {
        t.setValor("+1234567");
        cout << "✗ +1234567 não deveria ser aceito" << endl;
    } catch (...) {
        cout << "✓ +1234567 rejeitado corretamente (< 8 dígitos)" << endl;
    }
    
    // Teste 4: Inválido - mais de 15 dígitos
    try {
        t.setValor("+1234567890123456");
        cout << "✗ +1234567890123456 não deveria ser aceito" << endl;
    } catch (...) {
        cout << "✓ +1234567890123456 rejeitado corretamente (> 15 dígitos)" << endl;
    }
    
    // Teste 5: Inválido - sem +
    try {
        t.setValor("5511999998888");
        cout << "✗ 5511999998888 não deveria ser aceito (sem +)" << endl;
    } catch (...) {
        cout << "✓ Número sem + rejeitado corretamente" << endl;
    }
    
    // Teste 6: Inválido - contém caracteres não-dígito
    try {
        t.setValor("+551199999888a");
        cout << "✗ +551199999888a não deveria ser aceito" << endl;
    } catch (...) {
        cout << "✓ Número com caractere não-dígito rejeitado" << endl;
    }
    
    return 0;
}
