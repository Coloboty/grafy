#include <iostream>
#include <chrono>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "funkcje_pomocnicze.hpp"
#include "kruskal.hpp"
#include "prim.hpp"

using namespace std;

template<typename G>
void testowyGraf(G graf){
    graf->dodajKrawedz(3, 0, 1);
    graf->dodajKrawedz(4, 0, 5);
    graf->dodajKrawedz(7, 1, 6);
    graf->dodajKrawedz(2, 1, 2);
    graf->dodajKrawedz(3, 2, 3);
    graf->dodajKrawedz(8, 2, 6);
    graf->dodajKrawedz(5, 3, 6);
    graf->dodajKrawedz(12, 6, 5);
    graf->dodajKrawedz(11, 6, 4);

    graf->dodajKrawedz(10, 0, 6);
}

int main(void){
    shared_ptr< graf_lista<int, int> > ltest, lrek;
    shared_ptr< graf_macierz<int, int> > mtest, mrek;
    shared_ptr<drzewo<int, int>> mst;

    uint rozmiar, gestosc;
    /* uint rozmiar; */
    czas start, stop;
    rozmiar= 10;
    gestosc= 100;
    
    
    /* test= make_shared< graf_macierz<int, int> >(rozmiar); */
    /* rek= make_shared< graf_macierz<int, int> >(rozmiar); */
    ltest= make_shared< graf_lista<int, int> >(rozmiar);
    mtest= make_shared< graf_macierz<int, int> >(rozmiar);
    lrek= make_shared< graf_lista<int, int> >(rozmiar);
    mrek= make_shared< graf_macierz<int, int> >(rozmiar);

    mst= make_shared< drzewo<int, int> >();
    
    start= zegar::now();
    ltest->losujGraf(gestosc);
    /* mtest->losujGraf(gestosc); */
    stop= zegar::now();

    /* testowyGraf(ltest); */
    /* testowyGraf(mtest); */
    
    /* cout << "Stworzono losowy graf_lista w " << obliczCzas(start, stop, 'm') << " ms\n"; */

    /*
    start= zegar::now();
    mtest->losujGraf(gestosc);
    stop= zegar::now();
    
    cout << "Stworzono losowy graf_macierz w " << obliczCzas(start, stop, 'm') << " ms\n";
    */

    cout << "graf ma " << rozmiar << " wierzcholkow i " <<
	ltest->dajLiczbeKrawedzi() << " krawedzi. ";

    cout << "gestosc to " << ltest->dajLiczbeKrawedzi()*100/((rozmiar*(rozmiar-1))/2) << '\n';
    
    
    start= zegar::now();
    prim(ltest, mst);
    /* prim(mtest, mst); */
    stop= zegar::now();
    
    cout << "Wykonano alg. Prima w " << obliczCzas(start, stop, 'm') << " ms\n";
    
    cout << "mst ma " << mst->dajRozmiar() << " krawedzi\n\n";
    

    for(uint i= 0; i < mst->dajRozmiar(); i++)
	cout << mst->dajOgniwo(i)->dajWartosc()->dajW1()->dajKlucz() << " --- " << mst->dajOgniwo(i)->dajWartosc()->dajW2()->dajKlucz() << '\n';

    cout << '\n';
    rekonstruujGraf(lrek, ltest, mst);
    cout << "Graf spójny?: " << testujSpojnoscGrafu(lrek) << '\n';
    
    cout << "Koniec programu!\n";
    
    return 0;
}
