//
// Created by alxma on 4/26/2025.
//

#ifndef SERVICECOS_H
#define SERVICECOS_H
#include <vector>
#include <random>
#include "Oferta.h"
#include "Repository.h"


class ServiceCos {
private:
    vector<Oferta> cos;
    AbstractRepo<Oferta>& repoOferta;
public:
    /* --- Constructors --- */

    explicit ServiceCos(Repository<Oferta>& repoOfertaX):
        repoOferta{repoOfertaX}{}

    /* --- Operatii cos --- */

    void adaugaOfertaInCos(int index);

    /// Genereaza un cos cu numar oferte aleatoare
    /// @param numar Numarul de oferte generate
    void genereazaCosAleator(int numar);

    /// Goleste ofertele din cos
    void golesteCos();
    void exportaCosToCSV(const string& filename, int mod) const;

    vector<Oferta> getCos();

    int getSize();

    /* Operatii extra --- */
};



#endif //SERVICECOS_H
