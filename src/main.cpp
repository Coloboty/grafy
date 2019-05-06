#include <iostream>
#include <chrono>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "funkcje_pomocnicze.hpp"
#include "kruskal.hpp"
#include "prim.hpp"

using namespace std;

int main(void){
    /* shared_ptr< graf_macierz<int, int> > test, rek; */
    shared_ptr< graf_lista<int, int> > ltest;
    shared_ptr< graf_macierz<int, int> > mtest, rek;
    shared_ptr<drzewo<int, int>> mst;

    uint rozmiar, gestosc;
    czas start, stop;
    rozmiar= 10;
    gestosc= 100;
    
    
    /* test= make_shared< graf_macierz<int, int> >(rozmiar); */
    /* rek= make_shared< graf_macierz<int, int> >(rozmiar); */
    ltest= make_shared< graf_lista<int, int> >(rozmiar);
    mtest= make_shared< graf_macierz<int, int> >(rozmiar);
    rek= make_shared< graf_macierz<int, int> >(rozmiar);

    mst= make_shared< drzewo<int, int> >();
    
    start= zegar::now();
    ltest->losujGraf(gestosc);
    stop= zegar::now();
    
    cout << "Stworzono losowy graf_lista w " << obliczCzas(start, stop, 'm') << " ms\n";

    start= zegar::now();
    mtest->losujGraf(gestosc);
    stop= zegar::now();
    
    cout << "Stworzono losowy graf_macierz w " << obliczCzas(start, stop, 'm') << " ms\n";
    
    cout << "graf ma " << rozmiar << " wierzcholkow i " <<
	mtest->dajLiczbeKrawedzi() << " krawedzi. ";

    cout << "gestosc to " << mtest->dajLiczbeKrawedzi()*100/((rozmiar*(rozmiar-1))/2) << '\n';

    
    start= zegar::now();
    prim(mtest, mst);
    stop= zegar::now();
    
    cout << "Wykonano alg. Prima w " << obliczCzas(start, stop, 'm') << " ms\n";
    
    cout << "mst ma " << mst->dajRozmiar() << " krawedzi\n\n";
    cout << '\n';
    
    /* rekonstruujGraf(rek, mtest, mst); */
    /* cout << testujSpojnoscGrafu(rek) << '\n'; */
    
    cout << "Koniec programu!\n";
    
    return 0;
}
