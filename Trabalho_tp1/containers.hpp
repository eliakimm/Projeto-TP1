// Cleaned containers header — single canonical implementation
#ifndef CONTAINERS_HPP_INCLUDED
#define CONTAINERS_HPP_INCLUDED

#include "entidades.hpp"
#include <vector>
#include <map>
#include <string>

/**
 * @file containers.hpp
 * @brief Implementacoes em memoria para gerentes, hospedes, hoteis/quartos e reservas.
 *
 * Esta versao foi consolidada para remover blocos duplicados e fornecer
 * uma API consistente usada pelos stubs e serviços do projeto.
 */

class ContainerGerentes {
private:
    std::map<std::string, Gerente> gerentes;

public:
    bool adicionar(const Gerente& g) {
        std::string email = g.getEmail().getValor();
        if (gerentes.count(email)) return false;
        gerentes.insert_or_assign(email, g);
        return true;
    }

    bool remover(const Email& e) {
        return gerentes.erase(e.getValor()) > 0;
    }

    Gerente* buscar(const Email& e) {
        auto it = gerentes.find(e.getValor());
        if (it != gerentes.end()) return &it->second;
        return nullptr;
    }

    bool atualizar(const Gerente& g) {
        std::string email = g.getEmail().getValor();
        if (!gerentes.count(email)) return false;
        gerentes.insert_or_assign(email, g);
        return true;
    }

    std::vector<Gerente> listarTodos() const {
        std::vector<Gerente> lista;
        for (const auto& [email, g] : gerentes) lista.push_back(g);
        return lista;
    }
};

class ContainerHoteis {
private:
    std::map<std::string, Hotel> hoteis;
    std::map<std::string, std::vector<Quarto>> quartosPorHotel;

public:
    bool adicionarHotel(const Hotel& h) {
        std::string cod = h.getCodigo().getValor();
        if (hoteis.count(cod)) return false;
        hoteis.insert_or_assign(cod, h);
        return true;
    }

    bool atualizarHotel(const Hotel& h) {
        std::string cod = h.getCodigo().getValor();
        if (!hoteis.count(cod)) return false;
        hoteis.insert_or_assign(cod, h);
        return true;
    }

    bool removerHotel(const Codigo& cod) {
        std::string c = cod.getValor();
        bool ok1 = (hoteis.erase(c) > 0);
        quartosPorHotel.erase(c);
        return ok1;
    }

    Hotel* buscarHotel(const Codigo& cod) {
        auto it = hoteis.find(cod.getValor());
        if (it != hoteis.end()) return &it->second;
        return nullptr;
    }

    bool adicionarQuarto(const Codigo& codHotel, const Quarto& q) {
        quartosPorHotel[codHotel.getValor()].push_back(q);
        return true;
    }

    bool editarQuarto(const Codigo& codHotel, const Quarto& q) {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return false;
        for (auto& item : it->second) {
            if (item.getNumero().getValor() == q.getNumero().getValor()) {
                item = q;
                return true;
            }
        }
        return false;
    }

    bool removerQuarto(const Codigo& codHotel, const Numero& num) {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return false;
        auto& vec = it->second;
        for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
            if (iter->getNumero().getValor() == num.getValor()) {
                vec.erase(iter);
                return true;
            }
        }
        return false;
    }

    std::vector<Hotel> listarHoteis() const {
        std::vector<Hotel> lista;
        for (const auto& [c, h] : hoteis) lista.push_back(h);
        return lista;
    }

    std::vector<Quarto> listarQuartos(const Codigo& codHotel) const {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it != quartosPorHotel.end()) return it->second;
        return {};
    }
};

class ContainerHospedes {
private:
    std::map<std::string, Hospede> hospedes;

public:
    bool adicionar(const Hospede& h) {
        std::string email = h.getEmail().getValor();
        if (hospedes.count(email)) return false;
        hospedes.insert_or_assign(email, h);
        return true;
    }

    bool remover(const Email& e) {
        return hospedes.erase(e.getValor()) > 0;
    }

    Hospede* buscar(const Email& e) {
        auto it = hospedes.find(e.getValor());
        if (it != hospedes.end()) return &it->second;
        return nullptr;
    }

    bool atualizar(const Hospede& h) {
        std::string email = h.getEmail().getValor();
        if (!hospedes.count(email)) return false;
        hospedes.insert_or_assign(email, h);
        return true;
    }

    std::vector<Hospede> listarTodos() const {
        std::vector<Hospede> lista;
        for (const auto& [email, h] : hospedes) lista.push_back(h);
        return lista;
    }
};

class ContainerReservas {
private:
    std::map<std::string, Reserva> reservas; // chave: codigo da reserva

public:
    // Converte Data "DD/MM/AAAA" ou "DD-MM-AAAA" em inteiro AAAAMMDD para comparacao
    static int dataParaInt(const Data& d) {
        std::string s = d.getValor();
        std::string dd = s.substr(0,2);
        std::string mm = s.substr(3,2);
        std::string yyyy = s.substr(6,4);
        return std::stoi(yyyy) * 10000 + std::stoi(mm) * 100 + std::stoi(dd);
    }

    bool adicionar(const Reserva& r) {
        std::string cod = r.getCodigo().getValor();
        if (reservas.count(cod)) return false;
        // minimal checks: reserva deve ter hospede/quarto/ hotel apontados
        if (!r.getHospede() || !r.getQuarto()) return false;
        reservas[cod] = r;
        return true;
    }

    bool remover(const Codigo& cod) {
        return reservas.erase(cod.getValor()) > 0;
    }

    std::vector<Reserva> listarPorEmail(const Email& e) const {
        std::vector<Reserva> lista;
        for (const auto& [codigo, r] : reservas) {
            if (r.getHospede() && r.getHospede()->getEmail().getValor() == e.getValor()) lista.push_back(r);
        }
        return lista;
    }

    bool buscarReserva(const Codigo& cod, Reserva& out) const {
        auto it = reservas.find(cod.getValor());
        if (it == reservas.end()) return false;
        out = it->second;
        return true;
    }

    bool atualizarReserva(const Reserva& r) {
        std::string cod = r.getCodigo().getValor();
        if (!reservas.count(cod)) return false;
        reservas[cod] = r;
        return true;
    }

    void removerPorHospede(const Email& e) {
        for (auto it = reservas.begin(); it != reservas.end(); ) {
            if (it->second.getHospede() && it->second.getHospede()->getEmail().getValor() == e.getValor()) it = reservas.erase(it);
            else ++it;
        }
    }

    // Nota: Reserva atualmente nao guarda ponteiro para Hotel; entao
    // nao podemos determinar facilmente qual hotel pertence a uma
    // reserva. Mantemos a função para compatibilidade, mas ela nao
    // remove nada enquanto a associacao entre Reserva<->Hotel nao
    // estiver definida.
    void removerPorHotel(const Codigo& /*codHotel*/) {
        // sem-op por agora
    }
};

#endif // CONTAINERS_HPP_INCLUDED
