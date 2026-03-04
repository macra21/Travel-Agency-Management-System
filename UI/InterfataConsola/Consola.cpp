//
// Created by alxma on 4/26/2025.
//

#include "Consola.h"

/* ===== Functii ajutatoare ===== */

/// Citeste un numar int
int citesteInt(const string& mesaj) {
    int valoare;
    string input;

    while (true) {
        cout << mesaj;
        getline(cin, input);

        if (input.empty()) {
            cout << "Introduceti o valoare!\n";
            continue;
        }

        try {
            valoare = stoi(input);
            return valoare;
        }
        catch (const invalid_argument&) {
            cout << "Trebuie sa introduceti un numar intreg valid!\n";
        }
        catch (const out_of_range&) {
            cout << "Numarul este prea mare!\n";
        }
    }
}

/// Citeste un double
double citesteDouble(const string& mesaj) {
    double valoare;
    string input;

    while (true) {
        cout << mesaj;
        getline(cin, input);

        if (input.empty()) {
            cout << "Introduceti o valoare!\n";
            continue;
        }

        try {
            valoare = stod(input);
            return valoare;
        }
        catch (const invalid_argument&) {
            cout << "Trebuie sa introduceti un numar valid!\n";
        }
        catch (const out_of_range&) {
            cout << "Numarul este prea mare!\n";
        }
    }
}


/// Citeste parametrii unei oferte, o creeaza si o returneaza
Oferta citesteOferta() {
    cin.ignore();
    cout<<"Denumire oferta: ";
    string denumire;
    getline(cin, denumire);
    cout<<"Destinatie oferta: ";
    string destinatie;
    getline(cin, destinatie);
    cout<<"Tip oferta: ";
    string tip;
    getline(cin, tip);
    cout<<"Pret oferta: ";
    double pret = citesteDouble("Pret oferta: ");
    int id = citesteInt("Id oferta: ");
    return Oferta{denumire, destinatie, tip, pret, id};
}

/// Afiseaza o oferta intr-un format clar si ordonat
void afiseazaOferta(const Oferta& oferta) {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║                DETALII OFERTA                ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║ Denumire:   " << setw(32) << left << oferta.getDenumire() << " ║" << endl;
    cout << "║ Destinatie: " << setw(32) << left << oferta.getDestinatie() << " ║" << endl;
    cout << "║ Tip:        " << setw(32) << left << oferta.getTip() << " ║" << endl;
    cout << "║ Pret:       " << setw(32) << left << fixed << setprecision(2) << oferta.getPret() << " ║" << endl;
    cout << "║ ID:         " << setw(32) << left << oferta.getId() << " ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
}

/* ====== Operatii UI ===== */

/* --- Operatii CRUD --- */

/// Meniu de help ce afiseaza toate comenzile disponibile
void consolaHelp() {
    cout << "Comenzi disponibile:\n";
    cout << "-- Operatii CRUD --\n";
    cout << "1. adaugaOferta - adauga o oferta\n";
    cout << "2. cautaOferta - cauta o oferta\n";
    cout << "3. modificaOferta - modifica o oferta\n";
    cout << "4. stergeOferta - sterge o oferta\n";
    cout << "5. listeazaOferte - listeaza toate ofertele\n";

    cout << "\n-- Operatii de filtrare si sortare --\n";
    cout << "6. filtrareOferte - filtreaza ofertele dupa destinatie sau pret\n";
    cout << "7. sortareOferte - sorteaza ofertele dupa diverse criterii\n";

    cout << "\n-- Operatii pentru cos --\n";
    cout << "8. adaugaInCos - adauga o oferta in cos dupa denumire\n";
    cout << "9. golesteCos - goleste cosul\n";
    cout << "10. genereazaCos - genereaza aleator un cos\n";
    cout << "11. exportaCos - exporta cosul in format CSV\n";
    cout << "12. listeazaCos - afiseaza continutul cosului\n";

    cout << "\n-- Alte comenzi --\n";
    cout << "13. help - afiseaza acest meniu\n";
    cout << "14. exit - iesire din aplicatie\n";
    cout << "15. undo - anuleaza ultima operatie de adaugare, modificare sau stergere\n";

}


/// Adauga o oferta
void Consola::consolaAdaugaOferta() {
    Oferta oferta = citesteOferta();
    this->serviceOferta.serviceAdaugaOferta(oferta);
    cout<<"Oferta adaugata cu succes!\n";
}

/// Modifica o oferta
void Consola::consolaModificaOferta() {
    Oferta oferta = citesteOferta();
    this->serviceOferta.serviceModificaOferta(oferta);
    cout<<"Oferta modificata cu succes!\n";
}

/// Cauta o oferta dupa id
void Consola::consolaCautaOferta() {
    int id = citesteInt("Id oferta: ");
    Oferta oferta = this->serviceOferta.serviceCautaOferta(id);
    cout<<"Oferta gasita cu succes!\n";
    afiseazaOferta(oferta);
}

/// Sterge o oferta dupa id
void Consola::consolaStergeOferta() {
    int id = citesteInt("Id oferta: ");
    this->serviceOferta.serviceStergeOferta(id);
    cout<<"Oferta stearsa cu succes!\n";
}

/// Afiseaza toate ofertele
void Consola::consolaListeazaOferte() {
    cout<<"Lista oferte:\n";
    for (const auto& oferta : this->serviceOferta.serviceGetAllOferte()) {
        afiseazaOferta(oferta);
    }
}

/* ===== Filtrari ===== */

/// Filtreaza ofertele
void Consola::consolaFiltrareOferte() {
    cout<<"Alegeti un mod de filtrare(1/2):\n1. Dupa destinatie\n2. Dupa pret\n";
    int mod = citesteInt(">>>");
    if (mod == 1) {
        cout<<"Introduceti destinatie: ";
        string destinatie;
        cin>>destinatie;
        cout<<"Lista oferte:\n";
        for (const auto& oferta: this->serviceOferta.serviceFiltreazaDupaDestinatieOferta(destinatie)) {
            afiseazaOferta(oferta);
        }
    }
    else if (mod == 2) {
        double pretMin = citesteDouble("Introduceti pret minim: ");
        double pretMax = citesteDouble("Introduceti pret maxim: ");
        cout<<"Lista oferte:\n";
        for (const auto& oferta: this->serviceOferta.serviceFiltreazaDupaPretOferta(pretMin, pretMax)) {
            afiseazaOferta(oferta);
        }
    }
    else {
        cout<<"Modul de filtrare este invalid!\n";
    }
}

/* ===== Sortari ===== */

/// Sortare oferte
void Consola::consolaSortareOferte(){
    cout<<"Alegeti un mod de sortare(1/2/3):\n1. Dupa Denumire\n2. Dupa Destinatie\n3. Tip + Pret\n";
    int mod = citesteInt(">>>");
    if (mod!=1 && mod!=2 && mod!=3) {
        cout<<"Modul de sortare este invalid!\n";
        return;
    }
    cout<<"Lista oferte:\n";
    this->serviceOferta.serviceSortareOferta(mod);
    this->consolaListeazaOferte();
}

/* ===== Operatii Cos ===== */

/// Adauga o oferta in cos
void Consola::consolaAdaugaOfertaInCos() {
    int id = citesteInt("Id oferta: ");
    this->serviceCos.adaugaOfertaInCos(id);
    cout<<"Oferta adaugata cu succes!\n";
}

/// Goleste cosul
void Consola::consolaGolesteCos() {
    this->serviceCos.golesteCos();
    cout<<"Cos golit!\n";
}

/// Genereaza un cos cu oferte aleatoare din repo
void Consola::consolaGenereazaCos() {
    int numar = citesteInt("Introduceti numarul de oferte aleatoare: ");
    this->serviceCos.genereazaCosAleator(numar);
    cout<<"Cos generat cu succes!\n";
}

/// Exporta cosul intr-un fisier csv
void Consola::consolaExportaCos() {
    int mod;
    string filename;
    cout<<"Introduceti numele fisierului in care se face exportul(fara extensii): ";
    cin>>filename;
    cin.ignore();
    while (true) {
        cout<<"Alegeti un mod de export(1/2):\n1. Export in format CSV\n2. Export in format html\n";
        mod = citesteInt(">>>");
        if (mod == 1) {
            filename = "../Exports/" + filename + ".csv";
            break;
        }
        else if (mod == 2) {
            filename = "../Exports/" + filename + ".html";
            break;
        }
        cout<<"Modul de export este invalid!\n";
    }

    this->serviceCos.exportaCosToCSV(filename, mod);
    cout<<"Cos exportat cu succes!\n";
}

/// Listeaza Ofertele din cos
void Consola::consolaListeazaCos() {
    cout<<"Lista oferte:\n";
    for (const auto& oferta : this->serviceCos.getCos()) {
        afiseazaOferta(oferta);
    }
}

/* --- Undo ---*/

void Consola::consolaUndo() {
    this->serviceOferta.serviceUndo();
    cout<<"Undo realizat cu succes!\n";
}

/* --- Rulare --- */

/// Ruleaza Aplicatia cu interfata tip consola
void Consola::runConsola() {
    cout<<"Aplicatie de gestiune a ofertelor turistice.\n";
    consolaHelp();
    while (true) {
        try {
            cout<<"Oferte in cos: "<<this->serviceCos.getSize()<<'\n';
            cout << ">>> ";
            string comanda;
            cin >> comanda;
            cin.ignore();
            // Comenzi CRUD
            if (comanda == "adaugaOferta" || comanda == "1")
                consolaAdaugaOferta();
            else if (comanda == "cautaOferta" || comanda == "2")
                consolaCautaOferta();
            else if (comanda == "modificaOferta" || comanda == "3")
                consolaModificaOferta();
            else if (comanda == "stergeOferta" || comanda == "4")
                consolaStergeOferta();
            else if (comanda == "listeazaOferte" || comanda == "5")
                consolaListeazaOferte();

            // Comenzi de filtrare și sortare
            else if (comanda == "filtrareOferte" || comanda == "6")
                consolaFiltrareOferte();
            else if (comanda == "sortareOferte" || comanda == "7")
                consolaSortareOferte();

            // Comenzi pentru coș
            else if (comanda == "adaugaInCos" || comanda == "8")
                consolaAdaugaOfertaInCos();
            else if (comanda == "golesteCos" || comanda == "9")
                consolaGolesteCos();
            else if (comanda == "genereazaCos" || comanda == "10")
                consolaGenereazaCos();
            else if (comanda == "exportaCos" || comanda == "11")
                consolaExportaCos();
            else if (comanda == "listeazaCos" || comanda == "12")
                consolaListeazaCos();

            // Comenzi Undo + Redo
            else if (comanda == "undo" || comanda == "15")
                consolaUndo();

            // Alte comenzi
            else if (comanda == "help" || comanda == "13")
                consolaHelp();
            else if (comanda == "exit" || comanda == "14")
                break;
            else
                cout << "Comanda necunoscuta! Incercati 'help' pentru lista comenzilor.\n";
        }
        catch (const ValidationError& error) {
            cout << "Eroare validare date!\n" << error.getMessage();
        }
        catch (const RepoError& error) {
            cout << "Eroare repository!\n" << error.getMessage();
        }
        catch (const ServiceError& error) {
            cout << "Eroare service!\n" << error.getMessage();
        }
        catch (...) {
            cout << "Eroare necunoscuta!\n";
        }
    }

}