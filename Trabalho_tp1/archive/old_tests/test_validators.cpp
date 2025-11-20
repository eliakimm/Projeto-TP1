#include <iostream>
#include <cassert>
#include "dominios.hpp"

using namespace std;

int main() {
    cout << "Testando validadores de dominios..." << endl;
    
    // Teste Data com nomes de meses
    try {
        Data d;
        d.setValor("02-Out-2025");
        cout << "✓ Data formato DD-MMM-AAAA aceito: 02-Out-2025" << endl;
    } catch (...) {
        cout << "✗ Erro: Data 02-Out-2025 deveria ser valida" << endl;
        return 1;
    }
    
    // Teste Data invalida (formato antigo)
    try {
        Data d;
        d.setValor("02-10-2025");
        cout << "✗ Data 02-10-2025 (formato antigo) nao deveria ser aceita" << endl;
        return 1;
    } catch (...) {
        cout << "✓ Data formato numerico rejeitada corretamente" << endl;
    }
    
    // Teste Endereco com virgula/ponto
    try {
        Endereco e;
        e.setValor("Rua 10, Apt. 5");
        cout << "✓ Endereco com virgula e ponto aceito: Rua 10, Apt. 5" << endl;
    } catch (...) {
        cout << "✗ Erro: Endereco 'Rua 10, Apt. 5' deveria ser valido" << endl;
        return 1;
    }
    
    // Teste Senha com restricoes de adjacencia
    try {
        Senha s;
        s.setValor("A1b2C");  // Alternando letra/digito
        cout << "✓ Senha alternada aceita: A1b2C" << endl;
    } catch (const exception& ex) {
        cout << "✗ Erro: Senha 'A1b2C' deveria ser valida: " << ex.what() << endl;
        return 1;
    }
    
    // Teste Senha com letras consecutivas (invalida)
    try {
        Senha s;
        s.setValor("AB1c2");  // Duas letras consecutivas
        cout << "✗ Senha 'AB1c2' (letras consecutivas) nao deveria ser aceita" << endl;
        return 1;
    } catch (...) {
        cout << "✓ Senha com letras consecutivas rejeitada corretamente" << endl;
    }
    
    // Teste Dinheiro
    try {
        Dinheiro d;
        d.setValor(180.00);
        cout << "✓ Dinheiro 180.00 aceito" << endl;
    } catch (...) {
        cout << "✗ Erro: Dinheiro 180.00 deveria ser valido" << endl;
        return 1;
    }
    
    // Teste Capacidade
    try {
        Capacidade c;
        c.setValor(2);
        cout << "✓ Capacidade 2 aceita" << endl;
    } catch (...) {
        cout << "✗ Erro: Capacidade 2 deveria ser valida" << endl;
        return 1;
    }
    
    // Teste Cartao com Luhn (valido)
    try {
        Cartao cart;
        cart.setValor("4111111111111111");  // Numero valido com Luhn
        cout << "✓ Cartao 4111111111111111 (valido com Luhn) aceito" << endl;
    } catch (...) {
        cout << "✗ Erro: Cartao valido deveria ser aceito" << endl;
        return 1;
    }
    
    cout << "\n✓ Todos os testes passaram!" << endl;
    return 0;
}
