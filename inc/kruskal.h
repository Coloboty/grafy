#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <queue>
#include "grafy_macierz.hpp"
#include "porownywacz.h"

template<typename T, typename K>
using drzewo= lista< krawedz<T, K>* >;

template<typename T>
class galaz {
    T elem;
    uint ojciec, ja;
    uint ranga;

public:
    void zmienElement(T nowy) {elem= nowy;}
    T dajElement(void) {return elem;}

    void zmienOjca(uint nowy) {ojciec= nowy;}
    uint dajOjca(void) {return ojciec;}

    void zmienRange(uint nowa) {ranga= nowa;}
    uint dajRange(void) {return ranga;}
};

template<typename T>
class las_zbiorow{
    galaz<T> *galezie;
    uint rozmiar;

public:
    las_zbiorow(uint r){
	rozmiar= r;
	galezie= new galaz<T>[rozmiar];

	for(uint i=0; i < rozmiar; i++){
	    galezie[i].zmienOjca(i);
	    galezie[i].zmienRange(0);
	}
    }

    ~las_zbiorow(){
	delete[] galezie;
    }

    /*  */

    void dodajElement(T elem, uint ktory) {galezie[ktory].zmienElement(elem);}
    T dajElement(uint ktory) {return galezie[ktory].dajElement();}

    uint szukaj(uint x){
	if(galezie[x].dajOjca() != x)
	    galezie[x].zmienOjca(szukaj(galezie[x].dajOjca()));
	return galezie[x].dajOjca();
    }

    void polacz(uint x, uint y){
	uint ox, oy, temp;
	ox= galezie[x].dajOjca();
	oy= galezie[y].dajOjca();

	if(ox == oy)
	    return;

	if(galezie[ox].dajRange() < galezie[oy].dajRange()){
	    temp= ox;
	    ox= oy;
	    oy= temp;
	}

	galezie[oy].zmienOjca(ox);
	if(galezie[ox].dajRange() == galezie[oy].dajRange())
	    galezie[ox].zmienRange(galezie[ox].dajRange()+1);
	   
    }
};

/* ------------Alg. Kruskala----------- */

template<typename T, typename K, typename G>
void kruskal(G graf, shared_ptr< drzewo<T, K> > mst){
    priority_queue<krawedz<T, K>*, vector<krawedz<T, K>*>, porownywacz<T, K>> kolejka;
    wierzcholek<T, K> *w1, *w2;
    krawedz<T, K> *k;
    las_zbiorow<wierzcholek<T, K> *> *las;
    uint licznik, rozmiar, l_krawedzi;

    /* Otrzymany wskaźnik musi wskazywać na konkretną listę */
    if(!mst)
	return;

    /* Podana lista musi być pusta */
    if(mst->dajRozmiar() > 0)
	return;
    
    licznik= 0;
    rozmiar= graf->dajRozmiar();
    l_krawedzi= graf->dajLiczbeKrawedzi();

    las= new las_zbiorow<wierzcholek<T, K> *>(rozmiar);
    
    for(uint i= 0; i < l_krawedzi; i++)
	kolejka.push(graf->dajKrawedz(i));
    
    while(licznik < rozmiar-1){
	k= kolejka.top();
	kolejka.pop();
	w1= k->dajW1();
	w2= k->dajW2();

	if(las->szukaj(w1->dajKlucz()) != las->szukaj(w2->dajKlucz())){
	    las->polacz(w1->dajKlucz(), w2->dajKlucz());
	    mst->dodajOgniwo(k);
	    licznik++;
	}
    }

    delete las;
}

#endif
