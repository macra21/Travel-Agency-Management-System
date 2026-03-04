 /*
  *===============================
Lab 6-7
Timp de lucru 2 săptămâni
Cerințe generale:
– Creați o aplicație C++, folosiți paradigma orientat obiect
– Aplicația are interfața utilizator tip consola
– Utilizați procesul de dezvoltare bazat pe funcționalități (Feature driven
development). Identificați funcționalitățile și planificați-le pe doua iterații
– Folosiți o arhitectură stratificata (UI / Services(GRASP Controller) / Repository).
Creati clase pentru: Domain, Service, UI, Repository.
– Toate funcțiile necesare vor fi specificate și testate. (Test Code Coverage >99% la
toate modulele in afara de UI)
– Fara warninguri (in Visual Studio warning level /W4, treat warning as errors)
– Const Correctness: – folosiți calificativul const pentru variabile/parametrii care nu sunt modificați
                     – folosiți calificativul const pentru metode care nu modifica starea obiectelor
                     – transmiteți parametrii prin const & peste tot unde este posibil
                     – evitați copierea obiectelor când nu este necesar.
Iterație 1:
    – Folosiți clasa std::string si clasa std::vector din STL (librăria standard C++)
    – Nu folosiți pointeri.
    – Nu alocați dinamic.
Iterația 2:
    – Înlocuiți clasa std::vector cu o clasa proprie parametrizata (Template) care
        implementează o lista folosind structura de date lista înlănțuita sau vector
        dinamic (la alegere).
    – Validarea datelor. Utilizatorul este anunțat printr-un mesaj daca:  introduce
        valori de intrare greșite; încearcă sa adauge o entitate de doua ori, încearcă
        sa șteargă / modifice o entitate inexistenta (se vor folosi  excepții)
    – Creați o diagramă UML a claselor pentru a schița arhitectura aplicației

6 Agenție de turism
Creați o aplicație care permite:
· gestiunea unei liste de oferte turistice. Oferta: denumire, destinație, tip, preț
· adăugare, ștergere, modificare și afișare  oferte turistice
· căutare oferta
· filtrare oferte turistice după: destinație, preț
· sortare oferte după: denumire, destinație, tip + preț
=====================================
Lab 8-9
Timp de lucru 2 săptămâni
    Cerințe generale:
• Fără memory leak.
• Test Code Coerage >99% pe tot codul in afara de UI
• Compilatorul setat la „treat Warning as Errors”, Warning Level /W4
• Soluționat majoritatea erorilor raportate de linter: Activat „code analysis on
    build” selectat „"C++ Core Check rules". Va încurajez ca la fiecare
    eroare/sugestie raportata sa citiți partea relevanta din guidline (eroarea din VS
    oferă un link către secțiune), este e metoda buna pentru a explora limbajul
    C++. Daca va merge greu compilarea puteți sa activați doar din când in când
    analiza pentru a vedea ce erori raportează.

    Cerințe Iterația 1:
    • Modificați aplicația: folosiți clasa vector din STL si înlocuiți toate for-urile din
aplicație cu algoritmi din STL si varianta c++11 de for (range for).  Exemplu
de algoritmi:  copy_if (la filtrare), find_if (căutare), sort
    • Folosiți excepții pentru a raporta erori (creați clase proprii pentru excepții).
    • Adăugați funcționalitatea noua (descris la fiecare problema).
    • Pentru a alege aleator elemente puteți folosi:
#include <random>
std::mt19937 mt{ std::random_device{}() };
std::uniform_int_distribution<> dist(0, v.size()-1);
int rndNr = dist(mt);// numar aleator intre [0,size-1]
#include <algorithm>
#include <random>
#include <chrono>
// std::default_random_engine
// std::chrono::system_clock
auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::shuffle(v.begin(),v.end(), std::default_random_engine(seed)); //amesteca vectorul v

    Cerințe Iterația 2:
    Adăugați partea cu salvarea in fișiere pentru produse/filme/cărți, etc.
    Adăugați posibilitatea de undo pentru operațiile: adaugă, șterge si modifică.
    Pentru implementare folosiți moștenire si polimorfism:
    • Creați o clasa abstracta ActiuneUndo care are o singura metoda: doUndo.
    • Creați 3 clase derivate UndoAdauga, UndoSterge, UndoModifica care in
        metoda doUndo implementează partea care reface situația de dinaintea
        adăugării/ștergerii/modificării.
    • In controller se v-a tine o lista de ActiuniUndo care se pot executa in orice
        moment. Se va face un apel polimorfic la metoda doUndo.
    • Acordați atenție gestiunii memoriei, evitați fenomenul de slicing.


6 Agenție de turism
Introduceți posibilitatea de a crea un wishlist. Utilizatorul poate crea interactiv o lista
de destinații pe care dorește sa le viziteze.
Adăugați următoarele acțiuni (elemente de meniu):
• Golește cos: șterge toate ofertele din cos.
• Adaugă in cos:  adaugă in cos o oferta turistica după denumire
• Generează cos: utilizatorul introduce numărul total de oferte, coșul se
populează aleator cu oferte turistice
• Export. Salvează cos in fișier : CVS sau HTML. Se face salvarea in fișier doar
când s-a selectat acest meniu, coșul nu este persistent (la repornire aplicație
coșul este din nou gol) , utilizatorul introduce numele fișierului unde se
salvează la fiecare export.
După fiecare acțiune utilizator se afișează numărul total al ofertelor din cos.
*/
#include <bits/stdc++.h>

//#include "Repository.h"
#include "FileRepository.h"
#include "Service/ServiceOferta/ServiceOferta.h"
#include "ServiceCos/ServiceCos.h"
#include "Teste/Teste.h"
#include "UI/InterfataConsola/Consola.h"

 using namespace std;

int main() {
    Teste::testAll();
    FileRepository<Oferta> repoOferta{"../Exports/data.txt"};
    ServiceOferta serviceOferta{repoOferta};
    ServiceCos serviceCos{repoOferta};
    Consola consola{repoOferta, serviceOferta, serviceCos};
    consola.runConsola();

    return 0;
}

/*int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}*/