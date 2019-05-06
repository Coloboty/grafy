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
    shared_ptr< graf_macierz<int, int> > test, rek;
    /* shared_ptr< lista< krawedz<int, int> *> > mst; */
    shared_ptr<drzewo<int, int>> mst;

    uint rozmiar, gestosc;
    czas start, stop;
    rozmiar= 10;
    gestosc= 100;
    
    
    test= make_shared< graf_macierz<int, int> >(rozmiar);
    rek= make_shared< graf_macierz<int, int> >(rozmiar);
    start= zegar::now();
    test->losujMacierz(gestosc);

    stop= zegar::now();
    

    cout << "Stworzono losowy graf w " << obliczCzas(start, stop, 'u') << " us\n";
    
    cout << "graf ma " << rozmiar << " wierzcholkow i " <<
	test->dajLiczbeKrawedzi() << " krawedzi. ";

    cout << "gestosc to " << test->dajLiczbeKrawedzi()*100/((rozmiar*(rozmiar-1))/2) << '\n';


    start= zegar::now();
    mst= mKruskal(test);

    stop= zegar::now();

    cout << "Wykonano alg. Kruskala w " << obliczCzas(start, stop, 'm') << " ms\n";
    
    cout << "mst ma " << mst->dajRozmiar() << " krawedzi\n\n";

    /*
    for(uint i= 0; i < mst->dajRozmiar(); i++){
	k= mst->dajOgniwo(i)->dajWartosc();
	
	w1= k->dajWierzcholek1();
	w2= k->dajWierzcholek2();
	rek->dodajKrawedz(2137, w1, w2);
    }
    */
    rekonstruujGraf(rek, test, mst);
    cout << '\n';

    cout << testujSpojnoscGrafu(rek) << '\n';

    cout << "Koniec programu!\n";
    return 0;
}
