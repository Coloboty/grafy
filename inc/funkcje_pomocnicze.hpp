#ifndef FUNKCJE_POMOCNICZE_HPP
#define FUNKCJE_POMOCNICZE_HPP

#include <chrono>

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
    uint rozmiar= graf->dajRozmiar();
    
    for(uint i= 0; i < rozmiar; i++){
	if(graf->dajLiczbeKrawedzi(i) == 0)
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

#endif
