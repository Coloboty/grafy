#ifndef GRAFY_LISTA_H
#define GRAFY_LISTA_H

#include <iostream>
#include <memory>
#include "lista.hpp"
#include "grafy_klasy.h"

using namespace std;

template <typename T, typename K>
class graf_lista{
private:
    wierzcholek<T, K> *wierzcholki;
    krawedz<T, K> *krawedzie;
    lista< krawedz<T, K>* > *incydencje;
    uint rozmiar, max_krawedzi;
    uint l_wierzcholkow, l_krawedzi;
    
public:
    graf_lista(uint r){
	rozmiar= r;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	l_wierzcholkow= l_krawedzi= 0;
	
	wierzcholki= new wierzcholek<T, K>[rozmiar];
	krawedzie= new krawedz<T, K>[max_krawedzi];
	incydencje= new lista< krawedz<T,K>* >[rozmiar];

	for(uint i= 0; i < rozmiar; i++){
	    wierzcholki[i].zmienKlucz(i);
	}
    }
    
    ~graf_lista(){
	delete[] wierzcholki;
	delete[] krawedzie;
	delete[] incydencje;
    }
    
    /* ------------ */
    
    wierzcholek<T, K> *dodajWierzcholek(T wartosc);
    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);
    krawedz<T, K> *dodajKrawedz(K wartosc, uint k1, uint k2);
					
    void usunWierzcholek(wierzcholek<T, K> *w);
    void usunKrawedz(krawedz<T, K> *k);

    /* --------------------- */

    wierzcholek<T, K> *dajW1(krawedz<T, K> *k) {return k->dajW1();}
    wierzcholek<T, K> *dajW2(krawedz<T, K> *k) {return k->dajW2();}

    wierzcholek<T, K> *dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k);

    bool czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);

    wierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    wierzcholek<T, K> *dajWierzcholek(uint i) {return wierzcholki+i;}
    
    krawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    krawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}
    
    lista< krawedz<T, K>* > *dajKrawedzie(wierzcholek<T, K> *w) {return incydencje+(w->dajKlucz());}
    lista< krawedz<T, K>* > *dajKrawedzie(uint i) {return incydencje+i;}
    
    
};

#endif
