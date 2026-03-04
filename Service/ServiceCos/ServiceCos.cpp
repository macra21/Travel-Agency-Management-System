//
// Created by alxma on 4/26/2025.
//

#include "ServiceCos.h"

/* --- Operatii cos --- */

/// Goleste ofertele din cos
void ServiceCos::golesteCos() {
    this->cos.clear();
}

/// Adauga o oferta in cos
void ServiceCos::adaugaOfertaInCos(int id) {
    Oferta oferta = this->repoOferta.repoCautaElem(id);
    this->cos.push_back(oferta);
}

/// Genereaza un cos cu numar oferte aleatoare
void ServiceCos::genereazaCosAleator(int numar) {
    vector<Oferta> oferte = this->repoOferta.repoGetAllElems();
    if (oferte.empty())
        throw ServiceError("Nu exista oferte salvate pentru a genera un cos!\n");

    cos.clear();
    mt19937 mt{ std::random_device{}() };
    for (int i=0; i < numar; i++) {
        uniform_int_distribution<> dist(0, static_cast<int>(oferte.size() - 1));
        const int rndNr = dist(mt);
        cos.push_back(oferte[rndNr]);
    }
}

/// Exportă lista de oferte din coș într-un fișier CSV
/// @param filename Numele fișierului în care se face exportul (fără extensie)
/// @param mod Modul de exportare(1=csv, 2=html)
/// @throw ServiceError dacă fișierul nu poate fi deschis sau scris
void ServiceCos::exportaCosToCSV(const string& filename, int mod) const {
    // Deschide fișierul pentru scriere
    ofstream fout(filename);
    if (!fout) {
        throw ServiceError("Eroare la deschiderea fișierului pentru export!");
    }

    if (mod==1) {
        fout << "ID,Denumire,Destinatie,Tip,Pret\n";

        for (const auto& oferta : cos) {
            fout << oferta.getId() << ","
                << oferta.getDenumire() << ","
                << oferta.getDestinatie() << ","
                << oferta.getTip() << ","
                << oferta.getPret() << "\n";
        }
    }
    if (mod==2) {
        // Scriem începutul fișierului HTML
        fout << "<!DOCTYPE html>\n";
        fout << "<html>\n";
        fout << "<head>\n";
        fout << "  <meta charset=\"UTF-8\">\n";
        fout << "  <title>Lista de oferte</title>\n";
        fout << "  <style>\n"
               "    table { border-collapse: collapse; width: 100%; }\n"
               "    th, td { border: 1px solid #ddd; padding: 8px; }\n"
               "    th { background-color: #f2f2f2; }\n"
               "  </style>\n";
        fout << "</head>\n";
        fout << "<body>\n";
        fout << "  <h1>Cos de oferte</h1>\n";

        // Scriem un tabel cu oferte
        fout << "  <table>\n";
        fout << "    <tr>\n";
        fout << "      <th>Id</th>\n";
        fout << "      <th>Denumire</th>\n";
        fout << "      <th>Destinatie</th>\n";
        fout << "      <th>Tip</th>\n";
        fout << "      <th>Pret</th>\n";
        fout << "    </tr>\n";

        // Iterăm prin vectorul de oferte și le scriem rând cu rând
        for (const auto& oferta : this->cos) {
            fout << "    <tr>\n";
            fout << "      <td>" << oferta.getId() << "</td>\n";
            fout << "      <td>" << oferta.getDenumire() << "</td>\n";
            fout << "      <td>" << oferta.getDestinatie() << "</td>\n";
            fout << "      <td>" << oferta.getTip() << "</td>\n";
            fout << "      <td>" << oferta.getPret() << "</td>\n";
            fout << "    </tr>\n";
        }

        // Închidem tabelul și documentul HTML
        fout << "  </table>\n";
        fout << "</body>\n";
        fout << "</html>\n";
    }


    fout.close();
}

/* --- Operatii extra --- */

/// Returneaza toate ofertele din cos
vector<Oferta> ServiceCos::getCos() {
    return this->cos;
}

/// Returneaza numarul de oferte din cos
int ServiceCos::getSize() {
    return this->cos.size();
}

