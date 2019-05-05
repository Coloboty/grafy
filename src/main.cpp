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

void wypiszElementy(lista<int> &x);

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

int main(void){
    shared_ptr< graf_macierz<int, int> > test;
    /* mwierzcholek<int, int> *w; */
    uint rozmiar, gestosc;
    czas start, stop;
    rozmiar= 100;
    gestosc= 100;
    
    
    test= make_shared< graf_macierz<int, int> >(rozmiar, gestosc);
    start= zegar::now();
    test->losujMacierz();
    stop= zegar::now();
    

    cout << "Stworzono losowy graf w " << obliczCzas(start, stop, 'u') << " us\n";
    
    cout << "graf ma " << rozmiar << " wierzcholkow i " <<
	test->dajLiczbeKrawedzi() << " krawedzi.\n";

    cout << "gestosc to " << test->dajLiczbeKrawedzi()*100/((rozmiar*(rozmiar-1))/2) << '\n';

    
/* mKruskal(test); */
    
    cout << "Koniec programu!\n";
    return 0;
}

void wypiszElementy(lista<int> &x){
    ogniwo<int> *leb, *ogon;
    leb= x.dajGlowe();
    ogon= x.dajOgon();
    ogon= ogon->dajPoprzednik();

    while(leb != ogon){
	leb= leb->dajNastepnik();
	cout << leb->dajWartosc() << '\n';
    }
}
