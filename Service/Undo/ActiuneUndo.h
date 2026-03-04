//
// Created by alxma on 4/26/2025.
//

#ifndef ACTIUNEUNDO_H
#define ACTIUNEUNDO_H
#include "Oferta.h"
#include "Repository.h"

class ActiuneUndo {
public:
    virtual ~ActiuneUndo() = default;

    virtual void doUndo() = 0;
};

class UndoAdaugaOferta : public ActiuneUndo {
private:
    AbstractRepo<Oferta>& repoOferta;
    int id;
public:
    UndoAdaugaOferta(AbstractRepo<Oferta>& repoOfertaX, int idX):
        repoOferta{repoOfertaX},id{idX}{}
    void doUndo() override {
        repoOferta.repoStergeElem(id);
    }
};

class UndoModificaOferta : public ActiuneUndo {
private:
    AbstractRepo<Oferta>& repoOferta;
    Oferta ofertaVeche;
public:
    UndoModificaOferta(AbstractRepo<Oferta>& repoOfertaX, const Oferta& ofertaX):
        repoOferta{repoOfertaX},ofertaVeche{ofertaX}{}
    void doUndo() override {
        repoOferta.repoModificaElem(ofertaVeche);
    }
};

class UndoStergeOferta : public ActiuneUndo {
private:
    AbstractRepo<Oferta>& repoOferta;
    Oferta ofertaVeche;
public:
    UndoStergeOferta(AbstractRepo<Oferta>& repoOfertaX, const Oferta& ofertaX):
        repoOferta{repoOfertaX},ofertaVeche{ofertaX}{}
    void doUndo() override {
        repoOferta.repoAdaugaElem(ofertaVeche);
    }
};
#endif //ACTIUNEUNDO_H
