//
// Created by alxma on 4/25/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "AbstractRepo.h"
#include "Exceptii.h"
using namespace std;

/// @brief Repository generic CRUD pentru elemente cu ID.
/// @tparam TElem
///   - Trebuie să expună metoda `int getId() const`
///   - Trebuie să aiba cosntructor prin copiere si constructor prin asignare
template<typename TElem>
class Repository : public AbstractRepo<TElem>{
private:
    vector<TElem> elems;
public:
    /* --- Operatii CRUD --- */

    /// Adauga un element nou, daca nu exista un element cu acelasi id in repository
    /// @param elemX Elementul ce se adauga
    /// @throw RepoError cu mesajul "Elementul de tip TElem exista deja in repository daca elementul exista deja in repository!\n", daca deja exista un element cu acelasi id in repository
    void repoAdaugaElem(const TElem& elemX) override{
        for (const auto& elem: elems)
            if (elem.getId() == elemX.getId())
                throw RepoError("Deja exista un element salvat, cu id-ul " + to_string(elemX.getId()) + "!\n");
        elems.push_back(elemX);
    }

    /// Modifica un element daca e existent in repository
    /// @param elemX Elementul cu care este modificat vechiul element
    /// @throw RepoError cu mesajul "Nu exista niciun element de tip TElem, cu id-ul elemX.getId()!\n", daca nu exista un element cu acelasi id in repository
    void repoModificaElem(const TElem& elemX) override{
        for (auto& elem: elems)
            if (elem.getId() == elemX.getId()) {
                elem = elemX;
                return;
            }
        throw RepoError("Nu exista niciun element, cu id-ul " + to_string(elemX.getId()) + "!\n");
    }

    /// Cauta un element in repository dupa id
    /// @param id id-ul elementului cautat
    /// @return Elementul gasit
    /// @throw RepoError cu mesajul "Nu exista niciun element de tip TElem, cu id-ul elemX.getId()!\n", daca nu exista un element cu acelasi id in repository
    TElem repoCautaElem(int id) override {
        /*for (const auto& elem : elems)
            if (elem.getId() == id)
                return elem;*/

        auto it = find_if(this->elems.begin(), this->elems.end(),
                         [id](const TElem& elem) {
                             return elem.getId() == id;
                         });

        if (it != elems.end()) {
            return *it;
        }

        throw RepoError("Nu exista niciun element, cu id-ul " + to_string(id) + "!\n");
    }

    /// Sterge un element din repository dupa id
    /// @param id id-ul elementului de sters
    /// @throw RepoError cu mesajul "Nu exista niciun element de tip TElem, cu id-ul elemX.getId()!\n", daca nu exista un element cu acelasi id in repository
    virtual void repoStergeElem(int id) override{
        for (auto it = elems.begin(); it != elems.end(); ++it) {
            if (it->getId() == id) {
                elems.erase(it);
                return;
            }
        }
        throw RepoError("Nu exista niciun element, cu id-ul " + to_string(id) + "!\n");
    }

    /* --- Operatii extra --- */

    /// Returneaza toate elementele din repository
    vector<TElem> repoGetAllElems() override{
        return this->elems;
    }

    /// Elementele din repository devin elemsX
    /// @param elemsX noile elemente din repository
    void repoSetAllElems(const vector<TElem>& elemsX) override{
        this->elems = elemsX;
    }

    /// Returneaza numarul de elemente din repository
    int repoGetSize() override{
        return this->elems.size();
    }
};

#endif //REPOSITORY_H
