#include <iostream>
#include <string>
using namespace std;

int main() {
    string nome = "Eliakim Silva";
    cout << "Nome: '" << nome << "'" << endl;
    cout << "Tamanho: " << nome.size() << endl;
    cout << "Válido? " << (nome.size() >= 5 && nome.size() <= 20 ? "SIM" : "NÃO") << endl;
    
    // Testando caractere por caractere
    cout << "\nAnálise caractere por caractere:" << endl;
    for (size_t i = 0; i < nome.size(); ++i) {
        cout << "Pos " << i << ": '" << nome[i] << "' (ASCII " << (int)nome[i] << ")" << endl;
    }
    
    return 0;
}
