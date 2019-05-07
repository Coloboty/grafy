#ifndef GRAFY_MACIERZ_H
#define GRAFY_MACIERZ_H

#include <iostream>
#include <memory>
#include "grafy_klasy.h"

using namespace std;

/* ----------------------------- */

template <typename T, typename K>
class graf_macierz{
private:
    uint rozmiar, max_krawedzi;
    uint l_krawedzi, l_wierzcholkow;
    wierzcholek<T, K> *wierzcholki;
    krawedz<T, K> *krawedzie;
    krawedz<T, K> **macierz;

    krawedz<T, K> *zMacierzy(uint r, uint k) {return macierz[r*rozmiar + k];}
    
    void doMacierzy(uint r, uint k, krawedz<T, K> *elem){
	if(r >= rozmiar || k >= rozmiar || r == k)
	    return;
	macierz[r*rozmiar + k]= elem;
    }
    
public:
    graf_macierz(uint n){
	rozmiar= n;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	l_krawedzi= 0;
	l_wierzcholkow= 0;
	wierzcholki= new wierzcholek<T, K>[rozmiar];

	/* Zawsze rezerwujemy wystarczająco dużo pamięci na pełny graf, */
	/* bo tak łatwiej */
	krawedzie= new krawedz<T, K>[max_krawedzi];

	
	macierz= new krawedz<T, K>*[rozmiar*rozmiar];

	/* Porządek w macierzy i klucze po kolei */
	for(uint i= 0; i < rozmiar; i++){
	    macierz[i]= nullptr;
	    wierzcholki[i].zmienKlucz(i);
	}
    }

    ~graf_macierz(){
	delete[] wierzcholki;
	delete[] krawedzie;
	delete[] macierz;
    }
    
    /* Metody główne */

    wierzcholek<T, K> *dodajWierzcholek(T wartosc);
    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);
    krawedz<T, K> *dodajKrawedz(K wartosc, uint k1, uint k2);

    void losujGraf(uint gestosc);
    
    /* --- */

    wierzcholek<T, K> *dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k);

    bool czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);
    bool czySasiedzi(uint k1, uint k2);

    void drukujMacierz(void);
    
    wierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    wierzcholek<T, K> *dajWierzcholek(uint i) {return wierzcholki+i;}
    
    krawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    krawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}

    krawedz<T, K> *dajKrawedz(uint k1, uint k2) {return zMacierzy(k1, k2);}
    krawedz<T, K> *dajKrawedz(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
	return zMacierzy(w1->dajKlucz(), w2->dajKlucz());
    }

    shared_ptr< lista< krawedz<T, K>* > > dajKrawedzie(wierzcholek<T, K> *w);
    shared_ptr< lista< krawedz<T, K>* > > dajKrawedzie(uint klucz);

    uint dajLiczbeKrawedzi(wierzcholek<T, K> *w);
    uint dajLiczbeKrawedzi(uint klucz);
    
    uint dajLiczbeKrawedzi(void) {return l_krawedzi;}
    uint dajRozmiar(void) {return rozmiar;}
};

#endif
