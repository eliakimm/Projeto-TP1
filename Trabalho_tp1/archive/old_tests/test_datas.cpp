#include <iostream>
#include <map>
#include <string>

using namespace std;

static int contarDias(const std::string& d) {
    static const std::map<std::string, int> meses = {
        {"JAN", 1}, {"FEV", 2}, {"MAR", 3}, {"ABR", 4}, {"MAI", 5}, {"JUN", 6},
        {"JUL", 7}, {"AGO", 8}, {"SET", 9}, {"OUT", 10}, {"NOV", 11}, {"DEZ", 12}
    };
    
    if (d.size() != 11) {
        cout << "Tamanho errado: " << d.size() << endl;
        return 0;
    }
    
    int dia = std::stoi(d.substr(0,2));
    std::string mesStr = d.substr(3,3);
    cout << "Mes string: '" << mesStr << "'" << endl;
    // Converter para maiúsculas
    for (char& c : mesStr) c = std::toupper(c);
    cout << "Mes maiusculo: '" << mesStr << "'" << endl;
    int mes = meses.at(mesStr);
    int ano = std::stoi(d.substr(7,4));
    
    // contagem simplificada: dias desde ano 0 aproximado
    return ano * 365 + (ano/4) - (ano/100) + (ano/400) + dia + (mes * 31);
}

int main() {
    try {
        cout << "Teste 1: 01-DEZ-2025" << endl;
        int d1 = contarDias("01-DEZ-2025");
        cout << "Resultado: " << d1 << endl;
        
        cout << "\nTeste 2: 05-DEZ-2025" << endl;
        int d2 = contarDias("05-DEZ-2025");
        cout << "Resultado: " << d2 << endl;
    } catch (const std::exception& e) {
        cout << "Excecao: " << e.what() << endl;
    }
    return 0;
}
