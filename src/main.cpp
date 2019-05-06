#include <iostream>
#include <chrono>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "kruskal.hpp"

using namespace std;
using namespace std::chrono;
typedef high_resolution_clock zegar;
typedef zegar::time_point czas;

unsigned long obliczCzas(czas start, czas stop, char jednostka){
    switch(jednostka){
    case 's':
	
	break;
    case 'm':
	return duration_cast<milliseconds>(stop-start).count();
	break;
    case 'u':
	return duration_cast<microseconds>(stop-start).count();
	break;
    case 'n':
	return duration_cast<nanoseconds>(stop-start).count();
	break;

    default:
	return 0;
    }

    return 0;
}

template<typename T>
bool testujSpojnoscGrafu(T graf){
/* bool testujSpojnoscGrafu(shared_ptr< lista< krawedz<T, K> *> > graf){ */
    
    uint rozmiar= graf->dajRozmiar();
    for(uint i= 0; i < rozmiar; i++){
	if(graf->dajLiczbeIncydencji(graf->dajWierzcholek(i)) == 0)
	    return false;
    }

    return true;
}

template<typename T, typename K>
void rekonstruujGraf(T rek, T graf, K mst){
    for(uint i= 0; i < mst->dajRozmiar(); i++){
	rek->dodajKrawedz(mst->dajOgniwo(i)->dajWartosc()->dajWartosc(),
			  mst->dajOgniwo(i)->dajWartosc()->dajW1(),
			  mst->dajOgniwo(i)->dajWartosc()->dajW2());
	/* cout << w1->dajKlucz() << "---" << w2->dajKlucz() << '\n'; */
    }
}

int main(void){
    shared_ptr< graf_macierz<int, int> > test, rek;
    /* shared_ptr< lista< krawedz<int, int> *> > mst; */
    shared_ptr<drzewo<int, int>> mst;
    uint rozmiar, gestosc;
    czas start, stop;
    rozmiar= 1000;
    gestosc= 100;
    
    
    test= make_shared< graf_macierz<int, int> >(rozmiar, gestosc);
    rek= make_shared< graf_macierz<int, int> >(rozmiar, gestosc);
    start= zegar::now();
    test->losujMacierz();
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
