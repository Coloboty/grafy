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
    shared_ptr< lista< krawedz<T, K>* > > *incydencje;
    /* lista< krawedz<T, K>* > *incydencje; */
    uint rozmiar, max_krawedzi;
    uint l_wierzcholkow, l_krawedzi;
    
public:
    graf_lista(uint r){
	rozmiar= r;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	l_wierzcholkow= l_krawedzi= 0;
	
	wierzcholki= new wierzcholek<T, K>[rozmiar];
	krawedzie= new krawedz<T, K>[max_krawedzi];
	/* incydencje= new lista< krawedz<T,K>* >[rozmiar]; */
	incydencje= new shared_ptr<lista< krawedz<T, K>* > >[rozmiar];

	for(uint i= 0; i < rozmiar; i++){
	    wierzcholki[i].zmienKlucz(i);
	    incydencje[i]= make_shared< lista< krawedz<T, K>* > >();
	}
    }
    
    ~graf_lista(){
	delete[] wierzcholki;
	delete[] krawedzie;
	/* delete[] incydencje; */
    }
    
    /* Metody główne */
    
    wierzcholek<T, K> *dodajWierzcholek(T wartosc);
    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);
    krawedz<T, K> *dodajKrawedz(K wartosc, uint k1, uint k2);

    void losujGraf(uint gestosc);
    
    /* --------------------- */

    wierzcholek<T, K> *dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k);
    wierzcholek<T, K> *dajPrzeciwleglyWierzcholek(uint w, krawedz<T, K> *k);
    
    bool czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);
    bool czySasiedzi(uint w1, uint w2);

    wierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    wierzcholek<T, K> *dajWierzcholek(uint i) {return wierzcholki+i;}
    
    krawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    krawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}
    
    shared_ptr< lista< krawedz<T, K>* > > dajKrawedzie(wierzcholek<T, K> *w) {return incydencje[w->dajKlucz()];}
    shared_ptr< lista< krawedz<T, K>* > > dajKrawedzie(uint i) {return incydencje[i];}

    uint dajLiczbeKrawedzi(wierzcholek<T, K> *w) {return incydencje[w->dajKlucz()]->dajRozmiar();}
    uint dajLiczbeKrawedzi(uint k) {return incydencje[k]->dajRozmiar();}
    
    uint dajLiczbeKrawedzi(void) {return l_krawedzi;}
    uint dajRozmiar(void) {return rozmiar;}
};



#endif
