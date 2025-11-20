#ifndef PRICING_HPP
#define PRICING_HPP

// Tabela simples de precificacao por capacidade
inline double precoPorCapacidade(int cap) {
    switch (cap) {
        case 1: return 150.0;
        case 2: return 220.0;
        case 3: return 290.0;
        case 4: return 360.0;
        default: return 150.0;
    }
}

#endif // PRICING_HPP
