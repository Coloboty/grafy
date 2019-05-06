#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <queue>
#include "grafy_macierz.hpp"
#include "porownywacz.h"

template<typename T>
class galaz {
    T elem;
    /* galaz<T> *ojciec; */
    uint ojciec, ja;
    uint ranga;

public:
    void zmienElement(T nowy) {elem= nowy;}
    T dajElement(void) {return elem;}

    /* void zmienOjca(galaz<T> *nowy) {ojciec= nowy;} */
    /* galaz<T> *dajOjca(void) {return ojciec;} */
    void zmienOjca(uint nowy) {ojciec= nowy;}
    uint dajOjca(void) {return ojciec;}

    void zmienRange(uint nowa) {ranga= nowa;}
    uint dajRange(void) {return ranga;}

    /* void zmienMnie(uint nowy) {ja= nowy;} */
    /* uint dajMnie(void) {return ja;} */
};

template<typename T>
class las_zbiorow{
    galaz <T> *galezie;
    uint rozmiar;

public:
    las_zbiorow(uint r){
	rozmiar= r;
	galezie= (galaz<T> *)malloc(sizeof(galaz<T>)*rozmiar);

	for(uint i=0; i < rozmiar; i++){
	    /* galezie[i].zmienMnie(i); */
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

template<typename T, typename K>
shared_ptr< lista< krawedz<T, K> *> > mKruskal(shared_ptr< graf_macierz<T, K> > graf){
    /* lista< wierzcholek<T, K>* > wierzcholki_grafu; */
    priority_queue<krawedz<T, K>*, vector<krawedz<T, K>*>, porownywacz<T, K>> kolejka;
    shared_ptr< lista< krawedz<T, K> *> > drzewo= make_shared< lista< krawedz<T, K> *> >();
    wierzcholek<T, K> *w1, *w2;
    krawedz<T, K> *k;
    las_zbiorow<wierzcholek<T, K> *> *las;
    uint *kolory;
    uint licznik, rozmiar, l_krawedzi;
    
    licznik= 0;
    rozmiar= graf->dajRozmiar();
    l_krawedzi= graf->dajLiczbeKrawedzi();

    las= new las_zbiorow<wierzcholek<T, K> *>(rozmiar);

    kolory= (uint*)malloc(sizeof(uint)*graf->dajRozmiar());
    for(uint i= 0; i < rozmiar; i++){
	kolory[i]= i;
    }

    
    for(uint i= 0; i < l_krawedzi; i++)
	kolejka.push(graf->dajKrawedz(i));

    
    while(licznik < rozmiar-1){
	/* std::cout << kolejka.top()->dajWartosc() << '\n'; */
	/* kolejka.pop(); */
	k= kolejka.top();
	kolejka.pop();
	w1= k->dajW1();
	w2= k->dajW2();

	if(las->szukaj(w1->dajKlucz()) != las->szukaj(w2->dajKlucz())){
	    las->polacz(w1->dajKlucz(), w2->dajKlucz());
	    drzewo->dodajOgniwo(k);
	    licznik++;
	}
	
    }

    delete[] kolory;
    delete las;
    return drzewo;
}

#endif
