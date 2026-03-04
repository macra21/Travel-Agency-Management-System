//
// Created by alxma on 4/30/2025.
//

#ifndef ABSTRACTREPO_H
#define ABSTRACTREPO_H
#include <vector>
using namespace std;
template<typename TElem>
class AbstractRepo {
public:
    virtual ~AbstractRepo() = default;
    virtual void repoAdaugaElem(const TElem& elemX) = 0;
    virtual void repoModificaElem(const TElem& elemx) = 0;
    virtual TElem repoCautaElem(int id) = 0;
    virtual void repoStergeElem(int id) = 0;
    virtual void repoSetAllElems(const vector<TElem>& elemsX) = 0;
    virtual vector<TElem> repoGetAllElems() = 0;
    virtual int repoGetSize() = 0;
};

#endif //ABSTRACTREPO_H
