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
    map<string, Gerente> gerentes;

public:
    bool adicionar(const Gerente& g) {
        string email = g.getEmail().getValor();
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
        string email = g.getEmail().getValor();
        if (!gerentes.count(email)) return false;
        gerentes.insert_or_assign(email, g);
        return true;
    }

    vector<Gerente> listarTodos() const {
        vector<Gerente> lista;
        for (const auto& [email, g] : gerentes) lista.push_back(g);
        return lista;
    }
};

class ContainerHoteis {
private:
    map<string, Hotel> hoteis;
    map<string, vector<Quarto>> quartosPorHotel;

public:
    bool adicionarHotel(const Hotel& h) {
        string cod = h.getCodigo().getValor();
        if (hoteis.count(cod)) return false;
        hoteis.insert_or_assign(cod, h);
        return true;
    }

    bool atualizarHotel(const Hotel& h) {
        string cod = h.getCodigo().getValor();
        if (!hoteis.count(cod)) return false;
        hoteis.insert_or_assign(cod, h);
        return true;
    }

    bool removerHotel(const Codigo& cod) {
        string c = cod.getValor();
        bool ok1 = (hoteis.erase(c) > 0);
        quartosPorHotel.erase(c);
        return ok1;
    }

    // Remove todos os hoteis cujo gerente/proprietario corresponde ao email fornecido.
    // Retorna lista de codigos removidos para que o chamador possa realizar limpeza adicional (ex.: reservas).
    vector<Codigo> removerPorGerente(const Email& gerenteEmail) {
        vector<Codigo> removidos;
        for (auto it = hoteis.begin(); it != hoteis.end(); ) {
            const Hotel& h = it->second;
            if (h.getGerenteEmail().getValor() == gerenteEmail.getValor()) {
                removidos.push_back(h.getCodigo());
                it = hoteis.erase(it);
                quartosPorHotel.erase(removidos.back().getValor());
            } else ++it;
        }
        return removidos;
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

    vector<Hotel> listarHoteis() const {
        vector<Hotel> lista;
        for (const auto& [c, h] : hoteis) lista.push_back(h);
        return lista;
    }

    vector<Quarto> listarQuartos(const Codigo& codHotel) const {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it != quartosPorHotel.end()) return it->second;
        return {};
    }

    // Busca um quarto persistente por numero dentro de um hotel
    Quarto* buscarQuarto(const Codigo& codHotel, const Numero& num) {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return nullptr;
        for (auto &q : it->second) {
            if (q.getNumero().getValor() == num.getValor()) return &q;
        }
        return nullptr;
    }
};

class ContainerHospedes {
private:
    map<string, Hospede> hospedes;

public:
    bool adicionar(const Hospede& h) {
        string email = h.getEmail().getValor();
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
        string email = h.getEmail().getValor();
        if (!hospedes.count(email)) return false;
        hospedes.insert_or_assign(email, h);
        return true;
    }

    vector<Hospede> listarTodos() const {
        vector<Hospede> lista;
        for (const auto& [email, h] : hospedes) lista.push_back(h);
        return lista;
    }
};

class ContainerReservas {
private:
    map<string, Reserva> reservas; // chave: codigo da reserva

public:
    // Converte Data "DD/MM/AAAA" ou "DD-MM-AAAA" em inteiro AAAAMMDD para comparacao
    static int dataParaInt(const Data& d) {
        string s = d.getValor();
        // Formato: DD-MMM-AAAA (Ex: 01-DEZ-2025)
        static const map<string, int> meses = {
            {"JAN", 1}, {"FEV", 2}, {"MAR", 3}, {"ABR", 4}, {"MAI", 5}, {"JUN", 6},
            {"JUL", 7}, {"AGO", 8}, {"SET", 9}, {"OUT", 10}, {"NOV", 11}, {"DEZ", 12}
        };

        string dd = s.substr(0,2);
        string mesStr = s.substr(3,3);
        string yyyy = s.substr(7,4);

        // Converter mês para maiúsculas e buscar no mapa
        for (char& c : mesStr) c = toupper(c);
        int mm = meses.at(mesStr);

        return stoi(yyyy) * 10000 + mm * 100 + stoi(dd);
    }

    bool adicionar(const Reserva& r) {
        string cod = r.getCodigo().getValor();
        if (reservas.count(cod)) return false;
        // minimal checks: reserva deve ter hospede apontado; quarto/hotel podem ser null (reserva pendente)
        if (!r.getHospede()) return false;
        // Verificar conflitos de datas com outras reservas do mesmo quarto
        if (r.getQuarto()) {
            int ns = dataParaInt(r.getCheckin());
            int ne = dataParaInt(r.getCheckout());
            for (const auto& [k, ex] : reservas) {
                if (!ex.getQuarto()) continue;
                // considerar mesmo hotel e mesmo numero de quarto (se hotel definido)
                bool mesmoHotel = true;
                if (r.getHotel() && ex.getHotel()) {
                    mesmoHotel = (r.getHotel()->getCodigo().getValor() == ex.getHotel()->getCodigo().getValor());
                }
                if (!mesmoHotel) continue;
                if (ex.getQuarto()->getNumero().getValor() == r.getQuarto()->getNumero().getValor()) {
                    int es = dataParaInt(ex.getCheckin());
                    int ee = dataParaInt(ex.getCheckout());
                    // se houver sobreposicao
                    if (!(ne <= es || ns >= ee)) return false;
                }
            }
        }

        reservas[cod] = r;
        return true;
    }

    bool remover(const Codigo& cod) {
        return reservas.erase(cod.getValor()) > 0;
    }

    vector<Reserva> listarPorEmail(const Email& e) const {
        vector<Reserva> lista;
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
        string cod = r.getCodigo().getValor();
        if (!reservas.count(cod)) return false;
        // Verificar conflitos de datas com outras reservas (exceto esta)
        if (r.getQuarto()) {
            int ns = dataParaInt(r.getCheckin());
            int ne = dataParaInt(r.getCheckout());
            for (const auto& [k, ex] : reservas) {
                if (k == cod) continue;
                if (!ex.getQuarto()) continue;
                bool mesmoHotel = true;
                if (r.getHotel() && ex.getHotel()) {
                    mesmoHotel = (r.getHotel()->getCodigo().getValor() == ex.getHotel()->getCodigo().getValor());
                }
                if (!mesmoHotel) continue;
                if (ex.getQuarto()->getNumero().getValor() == r.getQuarto()->getNumero().getValor()) {
                    int es = dataParaInt(ex.getCheckin());
                    int ee = dataParaInt(ex.getCheckout());
                    if (!(ne <= es || ns >= ee)) return false;
                }
            }
        }

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
    // Remove reservas associadas a um hotel, quando a reserva possui
    // ponteiro para Hotel definido.
    void removerPorHotel(const Codigo& codHotel) {
        for (auto it = reservas.begin(); it != reservas.end(); ) {
            if (it->second.getHotel() && it->second.getHotel()->getCodigo().getValor() == codHotel.getValor())
                it = reservas.erase(it);
            else ++it;
        }
    }
};

#endif // CONTAINERS_HPP_INCLUDED
