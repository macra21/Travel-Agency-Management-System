//
// Created by alxma on 4/25/2025.
//

#ifndef SERVICEOFERTA_H
#define SERVICEOFERTA_H
#include "../Repository/Repository.h"
#include "Oferta.h"
#include "Undo/ActiuneUndo.h"

class ServiceOferta{
private:
    AbstractRepo<Oferta>& repoOferta;
    vector<unique_ptr<ActiuneUndo>> undoActions;
public:
    /* --- Constructors --- */

    explicit ServiceOferta(Repository<Oferta>& repoOfertaX):
        repoOferta{repoOfertaX}{}

    /* --- Operatii CRUD --- */

     /// Adauga o oferta in repository, dupa validare.
     /// @param ofertaX Oferta ce trebuie adaugata
     /// @throw ValidationError daca validarea ofertei esueaza
     /// @throw RepoError daca oferta exista deja in repository
    void serviceAdaugaOferta(const Oferta& ofertaX);

    /// Modifica o oferta in repository, dupa verificare
    /// @param ofertaX Oferta ce se modifica
    /// @throw ValidationError daca validarea ofertei esueaza
    /// @throw RepoError daca oferta nu exista in repository
    void serviceModificaOferta(const Oferta& ofertaX);

    /// Cauta o oferta in repository
    /// @param id Id-ul ofertei ce este cautata
    /// @return oferta, daca aceasta exista in repository
    /// @throw RepoError daca oferta nu exista in repository
    Oferta serviceCautaOferta(int id) const;

    /// Sterge o oferta din repository
    /// @param id Id-ul ofertei ce se sterge
    /// @throw RepoError daca oferta nu exista in repository
    void serviceStergeOferta(int id);

    /* --- Filtrare --- */

    /// Filtreaza oferte dupa destinatie
    /// @return vector<Oferta> cu ofertele filtrate
    vector<Oferta> serviceFiltreazaDupaDestinatieOferta(const string &destinatie) const;

    /// Filtreaza oferte dupa pret
    /// @return vector<Oferta> cu ofertele filtrate
    vector<Oferta> serviceFiltreazaDupaPretOferta(double pretMin, double pretMax) const;

    /* --- Sortare --- */

    /// Sorteaza ofertele dupa denumire(mod=1), destinație(mod=2), tip + preț(mod=3)
    /// @param mod Modul de sortare
    void serviceSortareOferta(int mod);

    /* --- Operatii Undo --- */

    void serviceUndo();

    /* --- Operatii extra --- */

    /// Returneaza toate ofertele din repository
    vector<Oferta> serviceGetAllOferte() const;

    /// Elementele din repository devin elemsX
    /// @param oferteX noile elemente din repository
    void serviceSetAllOferte(const vector<Oferta> &oferteX) const;
};



#endif //SERVICEOFERTA_H
