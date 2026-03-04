//
// Created by alxma on 4/26/2025.
//

#ifndef CONSOLE_H
#define CONSOLE_H
#include "Oferta.h"
#include "Repository.h"
#include "ServiceOferta/ServiceOferta.h"
#include "ServiceCos/ServiceCos.h"


class Consola {
private:
    Repository<Oferta>& repoOferta;
    ServiceOferta& serviceOferta;
    ServiceCos& serviceCos;
public:
    Consola(Repository<Oferta> &repoOfertaX, ServiceOferta &serviceOfertaX, ServiceCos &serviceCosX):
        repoOferta{repoOfertaX},serviceOferta{serviceOfertaX}, serviceCos{serviceCosX} {}

    /// Ruleaza Aplicatia cu interfata tip consola
    void runConsola();

    void consolaAdaugaOferta();
    void consolaModificaOferta();
    void consolaCautaOferta();
    void consolaStergeOferta();
    void consolaListeazaOferte();
    void consolaFiltrareOferte();
    void consolaSortareOferte();

    void consolaAdaugaOfertaInCos();

    void consolaGolesteCos();

    void consolaGenereazaCos();

    void consolaExportaCos();

    void consolaListeazaCos();

    void consolaUndo();
};



#endif //CONSOLE_H
