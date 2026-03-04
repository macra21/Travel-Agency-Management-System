//
// Created by alxma on 4/26/2025.
//

#ifndef FILEREPOSITORY_H
#define FILEREPOSITORY_H
#include <fstream>

#include "Repository.h"
/// @tparam TElem trebuie sa aiba functiile lineToTElem() si TElemToLine()
/// pentru a asigura citirea si scrierea corecta in fisiere, mentinant abstractia
template<typename TElem>
class FileRepository : public Repository<TElem>{
private:
    string filename;

    /* --- Operatii fisiere --- */

    /// Incarca datele in fisier in Repository
    void loadFromFile() {
        ifstream fin(this->filename);
        if (!fin.is_open()) {
            Repository<TElem>::repoSetAllElems({});
            return;
        }

        string line;
        vector<TElem> elems;
        while (getline(fin, line)) {
            TElem elem = TElem::lineToTElem(line);
            elems.push_back(elem);
        }
        Repository<TElem>::repoSetAllElems(elems);
        fin.close();
    }

    /// Salveaza datele din Repository in fisier
    void storeToFile() {
        ofstream fout(this->filename);

        for (const auto& elem: Repository<TElem>::repoGetAllElems()) {
            string line = TElem::TElemToLine(elem);
            fout<<line<<endl;
        }
        fout.close();
    }
public:
    /* --- Constructors --- */
    /// Constructor care si incarca datele din fisier automat
    explicit FileRepository(const string& filenameX):Repository<TElem>(),filename{filenameX} {
        this->loadFromFile();
    }

    /* --- Destructors --- */

    /// Destructor care salveaza datele in fisier automat
    ~FileRepository() override {
        this->storeToFile();
    }

    /* --- Operatii CRUD --- */

    /// Adauga un element si salveaza datele in fisier
    void repoAdaugaElem(const TElem& elemX) override {
        Repository<TElem>::repoAdaugaElem(elemX);
        this->storeToFile();
    }

    /// Modifica un element si salveaza datele in fisier
    void repoModificaElem(const TElem& elemX) override {
        Repository<TElem>::repoModificaElem(elemX);
        this->storeToFile();
    }

    /// Sterge un element si salveaza datele in fisier
    void repoStergeElem(int id) override {
        Repository<TElem>::repoStergeElem(id);
        this->storeToFile();
    }

    /* --- Operatii extra --- */

    /// Modifica tot repo cu un vector nou de elemente si salveaza datele in fisier
    void repoSetAllElems(const vector<TElem>& elemsX) override {
        Repository<TElem>::repoSetAllElems(elemsX);
        this->storeToFile();
    }
};

#endif //FILEREPOSITORY_H
