//
// Created by alxma on 4/24/2025.
//

#include "Teste.h"

#include "FileRepository.h"
#include "Repository.h"
#include "ServiceOferta/ServiceOferta.h"
#include "ServiceCos/ServiceCos.h"

/// Teste pentru functiile din domeniul ofertei
void testeDomeniuOferta() {
    /* --- Test constructor cu parametrii --- */
    Oferta oferta1("Denumire1", "Destinatie1", "Tip1", 1.1, 1);

    /* --- Teste Getters --- */
    assert(oferta1.getDenumire() == "Denumire1");
    assert(oferta1.getDestinatie() == "Destinatie1");
    assert(oferta1.getTip() == "Tip1");
    assert(oferta1.getPret() == 1.1);
    assert(oferta1.getId() == 1);

    /* --- Test constructor prin copiere --- */

    Oferta oferta2(oferta1);
    assert(oferta2.getDenumire() == "Denumire1");
    assert(oferta2.getDestinatie() == "Destinatie1");
    assert(oferta2.getTip() == "Tip1");
    assert(oferta2.getPret() == 1.1);
    assert(oferta2.getId() == 1);

    /* --- Test constructor prin atribuire --- */
    Oferta oferta3("", "", "", 0, 5);
    oferta3 = oferta2;

    /* --- Teste setters --- */
    oferta3.setDenumire("Denumire3");
    oferta3.setDestinatie("Destinatie3");
    oferta3.setTip("Tip3");
    oferta3.setPret(3.3);
    assert(oferta3.getDenumire() == "Denumire3");
    assert(oferta3.getDestinatie() == "Destinatie3");
    assert(oferta3.getTip() == "Tip3");
    assert(oferta3.getPret() == 3.3);

}

/// Teste pentru validatorul ofertei
void testeValidatorOferta() {
    Oferta oferta1("Denumire1", "Destinatie1", "Tip1", 1.1, 1);
    try {
        ValidatorOferta::valideazaOferta(oferta1);
        assert(true);
    }
    catch (const ValidationError &error) {
        assert(false);
    }
    Oferta oferta2("", "", "", -1, -1);
    try {
        ValidatorOferta::valideazaOferta(oferta2);
        assert(false);
    }
    catch (const ValidationError &error) {
        assert(error.getMessage()=="Destinatia trebuie sa fie nevida!\n"
                                   "Denumirea trebuie sa fie nevida!\n"
                                   "Tipul trebuie sa fie nevid!\n"
                                   "Pretul trebuie sa fie un numar pozitiv!\n"
                                   "Id-ul trebuie sa fie un numar natural!\n");
    }
}

/// Teste pentru repository (testat pe oferta, dar e generic)
void testeRepository() {
    Repository<Oferta> repoOferta;

    /* Teste operatii CRUD --- */

    /* --- Test adaugare --- */
    assert(repoOferta.repoGetSize() == 0);
    // Test adaugare cu oferta inexistenta
    Oferta oferta1("Denumire1", "Destinatie1", "Tip1", 1.1, 1);
    repoOferta.repoAdaugaElem(oferta1);
    assert(repoOferta.repoGetSize() == 1);
    // Test adaugare cu oferta existenta
    try {
        repoOferta.repoAdaugaElem(oferta1);
        assert(false);
    }
    catch (const RepoError &error) {
        assert(error.getMessage() == "Deja exista un element salvat, cu id-ul 1!\n");
    }

    /* --- Test cautare --- */
    // Test cautare oferta existenta
    assert(repoOferta.repoCautaElem(1) == oferta1);
    // Test cautare oferta inexistenta
    try {
        repoOferta.repoCautaElem(2);
        assert(false);
    }
    catch (const RepoError &error) {
        assert(error.getMessage() == "Nu exista niciun element, cu id-ul 2!\n");
    }


    /* --- Test modificare --- */
    // Test modificare oferta existenta
    Oferta oferta2("Denumire2", "Destinatie2", "Tip2", 2.2, 1);
    repoOferta.repoModificaElem(oferta2);
    assert(repoOferta.repoCautaElem(1) == oferta2);
    // Test modificare oferta inexistenta
    Oferta oferta3("Denumire3", "Destinatie3", "Tip3", 3.3, 2);
    try {
        repoOferta.repoModificaElem(oferta3);
        assert(false);
    }
    catch (const RepoError &error) {
        assert(error.getMessage() == "Nu exista niciun element, cu id-ul 2!\n");
    }

    /* --- Test stergere --- */
    // Test stergere oferta existenta
    repoOferta.repoStergeElem(1);
    assert(repoOferta.repoGetSize() == 0);
    // Test stergere oferta inexistenta
    try {
        repoOferta.repoStergeElem(2);
        assert(false);
    }
    catch (const RepoError &error) {
        assert(error.getMessage() == "Nu exista niciun element, cu id-ul 2!\n");
    }
}

/// Teste pentru serviceOferta
void testeServiceOferta() {
    Repository<Oferta> repoOferta;
    ServiceOferta service{repoOferta};
    
    /* --- Test adaugare --- */
    // Test adaugare oferta valida
    Oferta oferta1{"Denumire1", "Destinatie1", "Tip1", 100.0, 1};
    service.serviceAdaugaOferta(oferta1);
    assert(service.serviceGetAllOferte().size() == 1);
    
    // Test adaugare oferta invalida
    Oferta oferta2{"", "", "", -100.0, -1};
    try {
        service.serviceAdaugaOferta(oferta2);
        assert(false);
    }
    catch (const ValidationError& error) {
        assert(error.getMessage() == "Destinatia trebuie sa fie nevida!\n"
                                   "Denumirea trebuie sa fie nevida!\n"
                                   "Tipul trebuie sa fie nevid!\n"
                                   "Pretul trebuie sa fie un numar pozitiv!\n"
                                   "Id-ul trebuie sa fie un numar natural!\n");
    }
    
    // Test adaugare oferta cu id existent
    Oferta oferta3{"AltaDenumire", "AltaDestinatie", "AltTip", 200.0, 1};
    try {
        service.serviceAdaugaOferta(oferta3);
        assert(false);
    }
    catch (const RepoError& error) {
        assert(error.getMessage() == "Deja exista un element salvat, cu id-ul 1!\n");
    }
    
    /* --- Test cautare --- */
    // Test cautare oferta existenta
    Oferta oferta4 = service.serviceCautaOferta(1);
    assert(oferta4 == oferta1);
    
    // Test cautare oferta inexistenta
    try {
        service.serviceCautaOferta(999);
        assert(false);
    }
    catch (const RepoError& error) {
        assert(error.getMessage() == "Nu exista niciun element, cu id-ul 999!\n");
    }
    
    /* --- Test modificare --- */
    // Test modificare oferta existenta
    Oferta oferta5{"DenumireNoua", "DestinatieNoua", "TipNou", 150.0, 1};
    service.serviceModificaOferta(oferta5);
    assert(service.serviceCautaOferta(1) == oferta5);
    
    // Test modificare oferta invalida
    try {
        service.serviceModificaOferta(oferta2);
        assert(false);
    }
    catch (const ValidationError& error) {
        assert(error.getMessage() == "Destinatia trebuie sa fie nevida!\n"
                                   "Denumirea trebuie sa fie nevida!\n"
                                   "Tipul trebuie sa fie nevid!\n"
                                   "Pretul trebuie sa fie un numar pozitiv!\n"
                                   "Id-ul trebuie sa fie un numar natural!\n");
    }
    
    // Test modificare oferta inexistenta
    Oferta oferta6{"Denumire", "Destinatie", "Tip", 100.0, 999};
    try {
        service.serviceModificaOferta(oferta6);
        assert(false);
    }
    catch (const RepoError& error) {
        assert(error.getMessage() == "Nu exista niciun element, cu id-ul 999!\n");
    }
    
    /* --- Test stergere --- */
    // Test stergere oferta existenta
    service.serviceStergeOferta(1);
    assert(service.serviceGetAllOferte().empty());
    
    // Test stergere oferta inexistenta
    try {
        service.serviceStergeOferta(999);
        assert(false);
    }
    catch (const RepoError& error) {
        assert(error.getMessage() == "Nu exista niciun element, cu id-ul 999!\n");
    }

    /* --- Test filtrare --- */

    Oferta of1{"Hotel1", "Romania", "Cazare", 100.0, 1};
    Oferta of2{"Hotel2", "Romania", "Cazare", 200.0, 2};
    Oferta of3{"Hotel3", "Italia", "Cazare", 150.0, 3};
    service.serviceAdaugaOferta(of1);
    service.serviceAdaugaOferta(of2);
    service.serviceAdaugaOferta(of3);

    // Filtrare după destinație
    auto filtruDestinatie = service.serviceFiltreazaDupaDestinatieOferta("Romania");
    assert(filtruDestinatie.size() == 2);
    assert(filtruDestinatie[0].getDestinatie() == "Romania");
    assert(filtruDestinatie[1].getDestinatie() == "Romania");

    // Filtrare după destinație inexistentă
    auto filtruDestinatieInexistenta = service.serviceFiltreazaDupaDestinatieOferta("Spania");
    assert(filtruDestinatieInexistenta.empty());

    // Filtrare după preț
    auto filtruPret = service.serviceFiltreazaDupaPretOferta(120.0, 250.0);
    assert(filtruPret.size() == 2);
    for (const auto& o : filtruPret) {
        assert(o.getPret() >= 120.0 && o.getPret() <= 250.0);
    }

    /* --- Test sortare --- */

    // Sortare după denumire
    service.serviceSortareOferta(1);
    auto sortDenumire = service.serviceGetAllOferte();
    assert(sortDenumire.size() == 3);
    assert(is_sorted(sortDenumire.begin(), sortDenumire.end(),
           [](const Oferta& o1, const Oferta& o2) { return o1.getDenumire() < o2.getDenumire(); }));

    // Sortare după destinație
    service.serviceSortareOferta(2);
    auto sortDestinatie = service.serviceGetAllOferte();
    assert(sortDestinatie.size() == 3);
    assert(is_sorted(sortDestinatie.begin(), sortDestinatie.end(),
           [](const Oferta& o1, const Oferta& o2) { return o1.getDestinatie() < o2.getDestinatie(); }));

    // Sortare după tip+preț
    Oferta of4{"Hotel4", "Grecia", "Excursie", 80.0, 4}; // Tip diferit: "Excursie" vs "Cazare"
    service.serviceAdaugaOferta(of4);
    service.serviceSortareOferta(3);
    auto sortTipPret = service.serviceGetAllOferte();
    assert(sortTipPret.size() == 4);

    assert(is_sorted(sortTipPret.begin(), sortTipPret.end(),
           [](const Oferta& o1, const Oferta& o2) {
               if (o1.getTip() == o2.getTip())
                   return o1.getPret() < o2.getPret();
               return o1.getTip() < o2.getTip();
           }));


    /* --- Test getAllOferte --- */

    assert(service.serviceGetAllOferte().size() == 4);

    /* --- Test setAllOferte --- */

    vector<Oferta> oferteNoi = {of1, of2};
    service.serviceSetAllOferte(oferteNoi);
    assert(service.serviceGetAllOferte().size() == 2);

}

/// Teste Service Cos
void testeServiceCos() {
    Repository<Oferta> repo;
    ServiceOferta serviceOferta{repo};
    ServiceCos serviceCos{repo};
    
    Oferta o1{"Hotel Malibu", "Mamaia", "Hotel", 500.0, 1};
    Oferta o2{"Vila Maria", "Sinaia", "Vila", 350.0, 2};
    Oferta o3{"Pensiune Alpin", "Predeal", "Pensiune", 200.0, 3};
    
    serviceOferta.serviceAdaugaOferta(o1);
    serviceOferta.serviceAdaugaOferta(o2);
    serviceOferta.serviceAdaugaOferta(o3);
    
    serviceCos.adaugaOfertaInCos(1);
    assert(serviceCos.getSize() == 1);
    
    serviceCos.adaugaOfertaInCos(2);
    assert(serviceCos.getSize() == 2);
    
    auto cosOferte = serviceCos.getCos();
    assert(cosOferte[0].getId() == 1);
    assert(cosOferte[1].getId() == 2);
    
    try {
        serviceCos.adaugaOfertaInCos(99);
        assert(false);
    } catch (const RepoError& err) {
        assert(err.getMessage() == "Nu exista niciun element, cu id-ul 99!\n");
    }

    serviceCos.golesteCos();
    assert(serviceCos.getSize() == 0);

    serviceCos.genereazaCosAleator(2);
    assert(serviceCos.getSize() == 2);

    serviceCos.golesteCos();
    repo.repoSetAllElems({});

    try {
        serviceCos.genereazaCosAleator(10);
        assert(false);
    } catch (const ServiceError& err) {
        assert(err.getMessage() == "Nu exista oferte salvate pentru a genera un cos!\n");
    }

}

/// Teste pentru FileRepository (testat pe oferta, dar e generic)
void testeFileRepository() {
    string testFile = "test_file_repo.txt";
    remove(testFile.c_str());
    
    FileRepository<Oferta> repo{testFile};
    assert(repo.repoGetAllElems().empty());
    
    Oferta o1{"Test1", "Dest1", "Tip1", 100.0, 1};
    repo.repoAdaugaElem(o1);
    assert(repo.repoGetAllElems().size() == 1);
    
    Oferta o2{"Test2", "Dest2", "Tip2", 200.0, 2};
    repo.repoAdaugaElem(o2);
    assert(repo.repoGetAllElems().size() == 2);
    
    Oferta o3{"ModTest", "ModDest", "ModTip", 300.0, 1};
    repo.repoModificaElem(o3);
    
    Oferta gasita = repo.repoCautaElem(1);
    assert(gasita.getDenumire() == "ModTest");
    
    repo.repoStergeElem(1);
    assert(repo.repoGetAllElems().size() == 1);
    
    vector<Oferta> lista = {
        Oferta{"New1", "New1", "New1", 150.0, 5},
        Oferta{"New2", "New2", "New2", 250.0, 6}
    };
    repo.repoSetAllElems(lista);
    assert(repo.repoGetAllElems().size() == 2);
    
    FileRepository<Oferta> repo2{testFile};
    assert(repo2.repoGetAllElems().size() == 2);
    assert(repo2.repoGetAllElems()[0].getId() == 5);
    repo2.repoSetAllElems({});
    
    ofstream fout(testFile);
    fout << "TestLoad,DestLoad,TipLoad,175.000000,7" << endl;
    fout.close();
    
    FileRepository<Oferta> repo3{testFile};
    assert(repo3.repoGetAllElems().size() == 1);
    assert(repo3.repoGetAllElems()[0].getId() == 7);
    
    remove(testFile.c_str());
}

void Teste::testAll() {
    testeDomeniuOferta();
    testeValidatorOferta();
    testeRepository();
    testeServiceOferta();
    testeServiceCos();
    testeFileRepository();
    cout<<"Teste rulate cu succes!\n";
}