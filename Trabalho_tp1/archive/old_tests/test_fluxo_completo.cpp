#include <iostream>
#include "dominios.hpp"
using namespace std;

int main() {
    cout << "=== Testando Fluxo Completo ===" << endl << endl;
    
    // ===== GERENTE =====
    cout << "1. Testando Login do Gerente:" << endl;
    try {
        Email emailGer;
        emailGer.setValor("teste@hotel.com");
        Senha senhaGer;
        senhaGer.setValor("A1b!2");
        cout << "✓ Email gerente: teste@hotel.com" << endl;
        cout << "✓ Senha gerente: A1b!2" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro gerente: " << e.what() << endl;
        return 1;
    }
    
    cout << endl << "2. Testando Criação do Hotel:" << endl;
    try {
        Nome nomeHotel;
        nomeHotel.setValor("Hotel Teste");
        
        Endereco enderecoHotel;
        enderecoHotel.setValor("Rua Teste");
        
        Telefone teleHotel;
        teleHotel.setValor("+5561991274713");
        
        Codigo codigoHotel;
        codigoHotel.setValor("hoteltest1");
        
        cout << "✓ Nome hotel: Hotel Teste" << endl;
        cout << "✓ Endereço hotel: Rua Teste" << endl;
        cout << "✓ Telefone hotel: +5561991274713" << endl;
        cout << "✓ Código hotel: hoteltest1" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro hotel: " << e.what() << endl;
        return 1;
    }
    
    cout << endl << "3. Testando Criação da Reserva (Hóspede):" << endl;
    try {
        Nome nomeHospede;
        nomeHospede.setValor("Eliakim Silva");
        
        Email emailHospede;
        emailHospede.setValor("eliakim@email.com");
        
        Endereco enderecoHospede;
        enderecoHospede.setValor("Samambaia Norte");
        
        Cartao cartaoHospede;
        cartaoHospede.setValor("5502096099523276");
        
        cout << "✓ Nome hóspede: Eliakim Silva" << endl;
        cout << "✓ Email hóspede: eliakim@email.com" << endl;
        cout << "✓ Endereço hóspede: Samambaia Norte" << endl;
        cout << "✓ Cartão hóspede: 5502096099523276" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro hóspede: " << e.what() << endl;
        return 1;
    }
    
    cout << endl << "4. Testando Criação do Quarto (Dinâmico):" << endl;
    try {
        Numero numeroQuarto;
        numeroQuarto.setValor("125");
        
        Capacidade capacidadeQuarto;
        capacidadeQuarto.setValor(2);
        
        Dinheiro dinheiroQuarto;
        dinheiroQuarto.setValor(220.00);
        
        Ramal ramalQuarto;
        ramalQuarto.setValor("01");
        
        cout << "✓ Número quarto: 125" << endl;
        cout << "✓ Capacidade: 2" << endl;
        cout << "✓ Dinheiro (preço): 220.00" << endl;
        cout << "✓ Ramal: 01" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro quarto: " << e.what() << endl;
        return 1;
    }
    
    cout << endl << "5. Testando Datas da Reserva:" << endl;
    try {
        Data dataChegada;
        dataChegada.setValor("01-Fev-2025");
        
        Data dataPartida;
        dataPartida.setValor("04-Fev-2025");
        
        cout << "✓ Data chegada: 01-Fev-2025" << endl;
        cout << "✓ Data partida: 04-Fev-2025" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro datas: " << e.what() << endl;
        return 1;
    }
    
    cout << endl << "6. Testando Código da Reserva:" << endl;
    try {
        Codigo codigoReserva;
        codigoReserva.setValor("reserva123");
        
        cout << "✓ Código reserva: reserva123" << endl;
    } catch (const exception& e) {
        cout << "✗ Erro código reserva: " << e.what() << endl;
        return 1;
    }
    
    cout << endl << "✅ TODOS OS CAMPOS ESTÃO VÁLIDOS!" << endl;
    return 0;
}
