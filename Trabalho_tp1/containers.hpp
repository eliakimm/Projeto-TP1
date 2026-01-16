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
 * uma API consistente usada pelos stubs e servicos do projeto.
 */

/**
* @class ContainerGerentes
* @brief Container em memoria para gerentes.
*
* @details Armazena objetos da classe Gerente indexados pelo email.
* Permite operacões de CRUD (adicionar, remover, buscar, atualizar)
* e listagem de todos os gerentes cadastrados.
* @author Eliakim Pereira da Silva - 231021440
*/
class ContainerGerentes {
private:
    map<string, Gerente> gerentes;

public:
    /**
    * @brief Adiciona um novo gerente ao container.
    * @param g Objeto Gerente a ser inserido.
    * @return true se inserido com sucesso, false se ja existir.
    */
    bool adicionar(const Gerente& g) {
        string email = g.getEmail().getValor();
        if (gerentes.count(email)) return false;
        gerentes.insert_or_assign(email, g);
        return true;
    }

    /**
    * @brief Remove um gerente pelo email.
    * @param e Email do gerente a ser removido.
    * @return true se removido, false caso nao exista.
    */
    bool remover(const Email& e) {
        return gerentes.erase(e.getValor()) > 0;
    }

    /**
    * @brief Busca um gerente pelo email.
    * @param e Email do gerente.
    * @return Ponteiro para o gerente encontrado ou nullptr se nao existir.
    */
    Gerente* buscar(const Email& e) {
        auto it = gerentes.find(e.getValor());
        if (it != gerentes.end()) return &it->second;
        return nullptr;
    }

    /**
    * @brief Atualiza os dados de um gerente existente.
    * @param g Objeto Gerente atualizado.
    * @return true se atualizado com sucesso, false caso nao exista.
    */
    bool atualizar(const Gerente& g) {
        string email = g.getEmail().getValor();
        if (!gerentes.count(email)) return false;
        gerentes.insert_or_assign(email, g);
        return true;
    }

    /**
    * @brief Lista todos os gerentes cadastrados.
    * @return Vetor contendo todos os gerentes.
    */
    vector<Gerente> listarTodos() const {
        vector<Gerente> lista;
        for (const auto& [email, g] : gerentes) lista.push_back(g);
        return lista;
    }
};

/**
* @class ContainerHoteis
* @brief Container em memoria para hoteis e seus quartos.
*
* @details Armazena objetos da classe Hotel indexados pelo codigo,
* alem de quartos associados a cada hotel.
* Permite operacões de CRUD sobre hoteis e quartos,
* alem de consultas especificas.
* @author Eliakim Pereira da Silva - 231021440
*/
class ContainerHoteis {
private:
    map<string, Hotel> hoteis;
    map<string, map<string, Quarto>> quartosPorHotel;

public:
    /**
    * @brief Adiciona um novo hotel.
    * @param h Objeto Hotel a ser inserido.
    * @return true se inserido com sucesso, false se ja existir.
    */
    bool adicionarHotel(const Hotel& h) {
        string cod = h.getCodigo().getValor();
        if (hoteis.count(cod)) return false;
        hoteis.insert_or_assign(cod, h);
        return true;
    }

    /**
    * @brief Atualiza os dados de um hotel existente.
    * @param h Objeto Hotel atualizado.
    * @return true se atualizado com sucesso, false caso nao exista.
    */
    bool atualizarHotel(const Hotel& h) {
        string cod = h.getCodigo().getValor();
        if (!hoteis.count(cod)) return false;
        hoteis.insert_or_assign(cod, h);
        return true;
    }

    /**
    * @brief Remove um hotel pelo codigo.
    * @param cod Codigo do hotel.
    * @return true se removido com sucesso, false caso nao exista.
    */
    bool removerHotel(const Codigo& cod) {
        string c = cod.getValor();
        bool ok1 = (hoteis.erase(c) > 0);
        quartosPorHotel.erase(c);
        return ok1;
    }

    /**
    * @brief Remove todos os hoteis de um gerente especifico.
    * @param gerenteEmail Email do gerente/proprietario.
    * @return Lista de codigos dos hoteis removidos.
    */
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

    /**
    * @brief Busca um hotel pelo codigo.
    * @param cod Codigo do hotel.
    * @return Ponteiro para o hotel encontrado ou nullptr se nao existir.
    */
    Hotel* buscarHotel(const Codigo& cod) {
        auto it = hoteis.find(cod.getValor());
        if (it != hoteis.end()) return &it->second;
        return nullptr;
    }

    /**
    * @brief Adiciona um quarto a um hotel.
    * @param codHotel Codigo do hotel.
    * @param q Objeto Quarto a ser inserido.
    * @return true se inserido com sucesso.
    */
    bool adicionarQuarto(const Codigo& codHotel, const Quarto& q) {
        quartosPorHotel[codHotel.getValor()].insert_or_assign(q.getNumero().getValor(), q);
        return true;
    }

    /**
    * @brief Edita os dados de um quarto existente.
    * @param codHotel Codigo do hotel.
    * @param q Objeto Quarto atualizado.
    * @return true se atualizado com sucesso, false caso nao exista.
    */
    bool editarQuarto(const Codigo& codHotel, const Quarto& q) {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return false;
        auto &inner = it->second;
        auto itq = inner.find(q.getNumero().getValor());
        if (itq == inner.end()) return false;
        itq->second = q;
        return true;
    }

    /**
    * @brief Remove um quarto de um hotel.
    * @param codHotel Codigo do hotel.
    * @param num Número do quarto.
    * @return true se removido com sucesso, false caso nao exista.
    */
    bool removerQuarto(const Codigo& codHotel, const Numero& num) {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return false;
        auto &inner = it->second;
        return inner.erase(num.getValor()) > 0;
    }

    /**
    * @brief Lista todos os hoteis cadastrados.
    * @return Vetor contendo todos os hoteis.
    */
    vector<Hotel> listarHoteis() const {
        vector<Hotel> lista;
        for (const auto& [c, h] : hoteis) lista.push_back(h);
        return lista;
    }

    /**
    * @brief Lista todos os quartos de um hotel.
    * @param codHotel Codigo do hotel.
    * @return Vetor contendo todos os quartos do hotel.
    */
    vector<Quarto> listarQuartos(const Codigo& codHotel) const {
        vector<Quarto> lista;
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return lista;
        for (const auto& [num, q] : it->second) lista.push_back(q);
        return lista;
    }

    /**
    * @brief Busca um quarto especifico dentro de um hotel.
    * @param codHotel Codigo do hotel.
    * @param num Número do quarto.
    * @return Ponteiro para o quarto encontrado ou nullptr se nao existir.
    */
    Quarto* buscarQuarto(const Codigo& codHotel, const Numero& num) {
        auto it = quartosPorHotel.find(codHotel.getValor());
        if (it == quartosPorHotel.end()) return nullptr;
        auto itq = it->second.find(num.getValor());
        if (itq != it->second.end()) return &itq->second;
        return nullptr;
    }
};

/**
* @class ContainerHospedes
* @brief Container em memoria para hospedes.
*
* @details Armazena objetos da classe Hospede indexados pelo email.
*          Permite operacões de CRUD (adicionar, remover, buscar, atualizar)
*          e listagem de todos os hospedes cadastrados.
* @author Eliakim Pereira da Silva - 231021440
*/
class ContainerHospedes {
private:
    map<string, Hospede> hospedes;

public:
    /**
    * @brief Adiciona um novo hospede ao container.
    * @param h Objeto Hospede a ser inserido.
    * @return true se inserido com sucesso, false se ja existir.
    */
    bool adicionar(const Hospede& h) {
        string email = h.getEmail().getValor();
        if (hospedes.count(email)) return false;
        hospedes.insert_or_assign(email, h);
        return true;
    }

    /**
    * @brief Remove um hospede pelo email.
    * @param e Email do hospede a ser removido.
    * @return true se removido, false caso nao exista.
    */
    bool remover(const Email& e) {
        return hospedes.erase(e.getValor()) > 0;
    }

    /**
    * @brief Busca um hospede pelo email.
    * @param e Email do hospede.
    * @return Ponteiro para o hospede encontrado ou nullptr se nao existir.
    */
    Hospede* buscar(const Email& e) {
        auto it = hospedes.find(e.getValor());
        if (it != hospedes.end()) return &it->second;
        return nullptr;
    }

    /**
    * @brief Atualiza os dados de um hospede existente.
    * @param h Objeto Hospede atualizado.
    * @return true se atualizado com sucesso, false caso nao exista.
    */
    bool atualizar(const Hospede& h) {
        string email = h.getEmail().getValor();
        if (!hospedes.count(email)) return false;
        hospedes.insert_or_assign(email, h);
        return true;
    }

    /**
    * @brief Lista todos os hospedes cadastrados.
    * @return Vetor contendo todos os hospedes.
    */
    vector<Hospede> listarTodos() const {
        vector<Hospede> lista;
        for (const auto& [email, h] : hospedes) lista.push_back(h);
        return lista;
    }
};

/**
* @class ContainerReservas
* @brief Container em memoria para reservas.
*
* @details Armazena objetos da classe Reserva indexados pelo codigo.
*          Permite operacões de CRUD, busca por email, remocao por hospede ou hotel,
*          alem de validacao de conflitos de datas entre reservas.
* @author Eliakim Pereira da Silva - 231021440
*/
class ContainerReservas {
private:
    map<string, Reserva> reservas; // chave: codigo da reserva

public:
    /**
     * @brief Converte uma data em formato "DD-MMM-AAAA" para inteiro AAAAMMDD.
     * @param d Objeto Data.
     * @return Inteiro representando a data no formato AAAAMMDD.
     */
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

    /**
    * @brief Adiciona uma nova reserva.
    * @param r Objeto Reserva a ser inserido.
    * @return true se inserido com sucesso, false se ja existir ou houver conflito.
    *
    * @details Valida:
    * - Se ha hospede associado.
    * - Se nao ha sobreposicao de datas com reservas existentes do mesmo quarto.
    */
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

    /**
    * @brief Lista todas as reservas associadas a um hospede.
    * @param e Email do hospede.
    * @return Vetor contendo todas as reservas do hospede.
    */
    bool remover(const Codigo& cod) {
        return reservas.erase(cod.getValor()) > 0;
    }

    /**
    * @brief Busca uma reserva pelo codigo.
    * @param cod Codigo da reserva.
    * @param out Objeto Reserva de saida.
    * @return true se encontrada, false caso contrario.
    */
    vector<Reserva> listarPorEmail(const Email& e) const {
        vector<Reserva> lista;
        for (const auto& [codigo, r] : reservas) {
            if (r.getHospede() && r.getHospede()->getEmail().getValor() == e.getValor()) lista.push_back(r);
        }
        return lista;
    }

    /**
    * @brief Atualiza os dados de uma reserva existente.
    * @param r Objeto Reserva atualizado.
    * @return true se atualizado com sucesso, false caso nao exista ou haja conflito.
    *
    * @details Valida conflitos de datas com outras reservas do mesmo quarto,
    * exceto a propria reserva sendo atualizada.
    */
    bool buscarReserva(const Codigo& cod, Reserva& out) const {
        auto it = reservas.find(cod.getValor());
        if (it == reservas.end()) return false;
        out = it->second;
        return true;
    }

    /**
    * @brief Remove todas as reservas associadas a um hospede.
    * @param e Email do hospede.
    */
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

    /**
    * @brief Remove todas as reservas associadas a um hotel.
    * @param codHotel Codigo do hotel.
    *
    * @details So remove reservas que possuem ponteiro para Hotel definido.
    */
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
