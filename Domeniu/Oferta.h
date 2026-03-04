//
// Created by alxma on 4/24/2025.
//

#ifndef OFERTA_H
#define OFERTA_H
#include <bits/stdc++.h>

#include <utility>
using namespace std;
class Oferta {
private:
    string denumire, destinatie, tip;
    double pret;
    int id;
public:
    /* --- Constructors --- */

    ///Constructor cu parametrii
    Oferta(string  denumireX, string  destinatieX, string  tipX, const double pretX, const int idX):
        denumire{move(denumireX)}, destinatie{move(destinatieX)}, tip{move(tipX)}, pret{pretX},id{idX} {}

    ///Constructor prin copiere
    Oferta(const Oferta& ofertaX):
        denumire{ofertaX.getDenumire()}, destinatie{ofertaX.getDestinatie()}, tip{ofertaX.getTip()}, pret{ofertaX.getPret()},id{ofertaX.getId()} {}

    ///Cosntructor prin asiganre
    Oferta& operator=(const Oferta& ofertaX) = default;

    /* --- Suprascrieri operatori --- */
    bool operator==(const Oferta& other) const {
        return denumire == other.denumire &&
               destinatie == other.destinatie &&
               tip == other.tip &&
               pret == other.pret &&
               id == other.id;
    }

    /* --- Getters --- */

    /// Returneaza denumirea ofertei
    [[nodiscard]] string getDenumire() const;

    /// Returneaza destinatia ofertei
    [[nodiscard]] string getDestinatie() const;

    /// Returneaza tipul ofertei
    [[nodiscard]] string getTip() const;

    /// Returneaza pretul ofertei
    [[nodiscard]] double getPret() const;

    /// Returneaza id-ul ofertei
    [[nodiscard]] int getId() const;

    /* --- Setters --- */

    /// Seteaza denumirea ofertei la denumireX
    /// @param denumireX : noua denumire a ofertei
    void setDenumire(const string& denumireX);

    /// Seteaza destinatia ofertei la destinatieX
    /// @param destinatieX : noua destinatie a ofertei
    void setDestinatie(const string& destinatieX);

    /// Seteaza noul tip al ofertei la tipX
    /// @param tipX : noul tip al ofertei
    void setTip(const string& tipX);

    /// Seteaza noul pret al ofertei la pretX
    /// @param pretX : noul pret al ofertei
    void setPret(const double pretX);

    /* --- Serializare+Deserializare pentru lucrul cu fisiere --- */

    /// Creeaza un nou obiect Oferta din linia de text
    /// @param line : linia de text
    /// @return un obiect Oferta
    static Oferta lineToTElem(const string& line);

    /// Creeaza o linie de text cu continutul ofertei
    /// @param ofertaX : un obiect Oferta
    /// @return linia de text
    static string TElemToLine(const Oferta& ofertaX);

    /* --- Destructors --- */

    //Destructor default
    ~Oferta() = default;
};



#endif // OFERTA_H
