//
// Created by alxma on 4/24/2025.
//
#include "Oferta.h"

/* --- Getters --- */

/// Returneaza denumirea ofertei
string Oferta::getDenumire() const{
    return this->denumire;
}

/// Returneaza destinatia ofertei
string Oferta::getDestinatie() const{
    return this->destinatie;
}

/// Returneaza tipul ofertei
string Oferta::getTip() const{
    return this->tip;
}

/// Returneaza pretul ofertei
double Oferta::getPret() const{
    return this->pret;
}

/// Returneaza id-ul ofertei
int Oferta::getId() const{
    return this->id;
}

/* --- Setters --- */

/// Seteaza denumirea ofertei la denumireX
/// @param denumireX : noua denumire a ofertei
void Oferta::setDenumire(const string& denumireX) {
    this->denumire = denumireX;
}


/// Seteaza destinatia ofertei la destinatieX
/// @param destinatieX : noua destinatie a ofertei
void Oferta::setDestinatie(const string& destinatieX) {
    this->destinatie = destinatieX;
}


/// Seteaza noul tip al ofertei la tipX
/// @param tipX : noul tip al ofertei
void Oferta::setTip(const string& tipX) {
    this->tip = tipX;
}

/// Seteaza noul pret al ofertei la pretX
/// @param pretX : noul pret al ofertei
void Oferta::setPret(const double pretX) {
    this->pret = pretX;
}

/* --- Serializare+Deserializare pentru lucrul cu fisiere --- */

/// Creeaza un nou obiect Oferta din linia de text
/// @param line : linia de text
/// @return un obiect Oferta
Oferta Oferta::lineToTElem(const string& line) {
    vector<string> params;
    size_t pos, prevPos = 0;
    while ( (pos = line.find(',', prevPos)) != string::npos) {
        params.push_back(line.substr(prevPos, pos - prevPos));
        prevPos = pos + 1;
    }
    params.push_back(line.substr(prevPos));
    return Oferta(params[0], params[1], params[2], stod(params[3]), stoi(params[4]));
}

/// Creeaza o linie de text cu continutul ofertei
/// @param ofertaX : un obiect Oferta
/// @return linia de text
string Oferta::TElemToLine(const Oferta& ofertaX) {
    return ofertaX.getDenumire() + "," + ofertaX.getDestinatie() + "," + 
           ofertaX.getTip() + "," + to_string(ofertaX.getPret()) + "," + to_string(ofertaX.getId());
}