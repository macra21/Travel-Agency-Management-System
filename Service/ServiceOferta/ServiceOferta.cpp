//
// Created by alxma on 4/25/2025.
//

#include "ServiceOferta.h"

#include "ValidatorOferta.h"

/* --- Operatii CRUD --- */

/// Adauga o oferta in repository, dupa validare.
/// @param ofertaX Oferta ce trebuie adaugata
/// @throw ValidationError daca validarea ofertei esueaza
/// @throw RepoError daca oferta exista deja in repository
void ServiceOferta::serviceAdaugaOferta(const Oferta& ofertaX) {
    ValidatorOferta::valideazaOferta(ofertaX);
    this->repoOferta.repoAdaugaElem(ofertaX);

    undoActions.push_back(make_unique<UndoAdaugaOferta>(this->repoOferta, ofertaX.getId()));
}

/// Modifica o oferta in repository, dupa verificare
/// @param ofertaX Oferta ce se modifica
/// @throw ValidationError daca validarea ofertei esueaza
/// @throw RepoError daca oferta nu exista in repository
void ServiceOferta::serviceModificaOferta(const Oferta& ofertaX) {
    ValidatorOferta::valideazaOferta(ofertaX);
    Oferta ofertaVeche = this->repoOferta.repoCautaElem(ofertaX.getId());
    this->repoOferta.repoModificaElem(ofertaX);

    undoActions.push_back(make_unique<UndoModificaOferta>(this->repoOferta, ofertaVeche));
}

/// Cauta o oferta in repository
/// @param id Id-ul ofertei ce este cautata
/// @return oferta, daca aceasta exista in repository
/// @throw RepoError daca oferta nu exista in repository
Oferta ServiceOferta::serviceCautaOferta(int id) const {
    return this->repoOferta.repoCautaElem(id);
}

/// Sterge o oferta din repository
/// @param id Id-ul ofertei ce se sterge
/// @throw RepoError daca oferta nu exista in repository
void ServiceOferta::serviceStergeOferta(int id) {
    Oferta ofertaVeche = this->repoOferta.repoCautaElem(id);
    this->repoOferta.repoStergeElem(id);
    undoActions.push_back(make_unique<UndoStergeOferta>(this->repoOferta, ofertaVeche));
}

/* --- Filtrare --- */

/// Filtreaza oferte dupa destinatie
/// @return vector<Oferta> cu ofertele filtrate
vector<Oferta> ServiceOferta::serviceFiltreazaDupaDestinatieOferta(const string &destinatie) const {
    vector<Oferta> rezultat;
    auto oferte = this->repoOferta.repoGetAllElems();
    
    copy_if(oferte.begin(), oferte.end(), back_inserter(rezultat), 
            [&destinatie](const Oferta& oferta) {
                return oferta.getDestinatie() == destinatie;
            });
    
    return rezultat;
}

/// Filtreaza oferte dupa pret
/// @return vector<Oferta> cu ofertele filtrate
vector<Oferta> ServiceOferta::serviceFiltreazaDupaPretOferta(double pretMin, double pretMax) const {
    vector<Oferta> rezultat;
    auto oferte = repoOferta.repoGetAllElems();
    
    copy_if(oferte.begin(), oferte.end(), back_inserter(rezultat), 
            [pretMin, pretMax](const Oferta& oferta) {
                return oferta.getPret() >= pretMin && oferta.getPret() <= pretMax;
            });
    
    return rezultat;
}

/* --- Sortare --- */

/// Sorteaza ofertele dupa denumire(mod=1), destinație(mod=2), tip + preț(mod=3)
/// @param mod Modul de sortare
void ServiceOferta::serviceSortareOferta(int mod) {
    vector<Oferta> oferteSortate = this->repoOferta.repoGetAllElems();
    if (mod == 1){
        sort(oferteSortate.begin(), oferteSortate.end(),
            [](const Oferta& oferta1, const Oferta& oferta2) {
                return oferta1.getDenumire() < oferta2.getDenumire();
            });
    }
    if (mod == 2) {
        sort(oferteSortate.begin(), oferteSortate.end(),
            [](const Oferta& oferta1, const Oferta& oferta2) {
                return oferta1.getDestinatie() < oferta2.getDestinatie();
            });
    }
    if (mod == 3) {
        sort(oferteSortate.begin(), oferteSortate.end(),
            [](const Oferta& oferta1, const Oferta& oferta2) {
                if (oferta1.getTip() == oferta2.getTip())
                    return oferta1.getPret() < oferta2.getPret();
                return oferta1.getTip() < oferta2.getTip();
            });
    }
    this->repoOferta.repoSetAllElems(oferteSortate);
}

/* --- Operatii Undo --- */

void ServiceOferta::serviceUndo() {
    if (this->undoActions.empty())
        throw ServiceError("Nu exista nicio operatie de undo!\n");

    undoActions.back()->doUndo();
    undoActions.pop_back();
}


/* --- Operatii extra --- */

/// Returneaza toate ofertele din repository
vector<Oferta> ServiceOferta::serviceGetAllOferte() const {
    return this->repoOferta.repoGetAllElems();
}

/// Elementele din repository devin elemsX
/// @param oferteX noile elemente din repository
void ServiceOferta::serviceSetAllOferte(const vector<Oferta>& oferteX) const {
    this->repoOferta.repoSetAllElems(oferteX);
}
