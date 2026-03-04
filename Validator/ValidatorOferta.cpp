//
// Created by alxma on 4/25/2025.
//

#include "ValidatorOferta.h"

void ValidatorOferta::valideazaOferta(const Oferta &oferta) {
    string erori="";
    if (oferta.getDestinatie() == "")
        erori += "Destinatia trebuie sa fie nevida!\n";
    if (oferta.getDenumire() == "")
        erori += "Denumirea trebuie sa fie nevida!\n";
    if (oferta.getTip() == "")
        erori += "Tipul trebuie sa fie nevid!\n";
    if (oferta.getPret() < 0)
        erori += "Pretul trebuie sa fie un numar pozitiv!\n";
    if (oferta.getId() < 0 || floor(oferta.getId()) != oferta.getId())
        erori += "Id-ul trebuie sa fie un numar natural!\n";
    if (!erori.empty())
        throw ValidationError(erori);
}
