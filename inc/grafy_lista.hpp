#ifndef GRAFY_LISTA_HPP
#define GRAFY_LISTA_HPP

#include "grafy_lista.h"

template<typename T, typename K>
wierzcholek<T, K> *graf_lista<T, K>::dodajWierzcholek(T wartosc){
    wierzcholek<T, K> *nowy_wierzcholek= new(wierzcholek<T, K>)(wartosc);
    ogniwo< wierzcholek<T, K>* > *miejsce_nowego= wierzcholki->dodajZa(nowy_wierzcholek, wierzcholki->dajPierwsze());
    nowy_wierzcholek->zmienMiejsce(miejsce_nowego);
	
    return nowy_wierzcholek;
}

template<typename T, typename K>
krawedz<T, K> *graf_lista<T, K>::dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
    ogniwo< krawedz<T, K>* > *i1, *i2;
    krawedz<T, K> *nowa_krawedz= new krawedz<T, K>(wartosc, w1, w2);
    ogniwo< krawedz<T, K>* > *miejsce_nowej= krawedzie->dodajZa(nowa_krawedz, krawedzie->dajPierwsze());
    nowa_krawedz->zmienMiejsce(miejsce_nowej);

    i1= w1->dodajIncydencje(nowa_krawedz);
    i2= w2->dodajIncydencje(nowa_krawedz);

    nowa_krawedz->zmienIncydencje(i1, w1);
    nowa_krawedz->zmienIncydencje(i2, w2);
	
    return nowa_krawedz;
}

template<typename T, typename K>
void graf_lista<T, K>::usunWierzcholek(wierzcholek<T, K> *w){
    lista< krawedz<T, K>* > *inc= w->dajListeIncydencji();
    while(inc->dajRozmiar() > 0)
	usunKrawedz(inc->dajPierwsze()->dajWartosc());
	
    wierzcholki->usunOgniwo(w->dajMiejsce());
    delete w;
}

template<typename T, typename K>
void graf_lista<T, K>::usunKrawedz(krawedz<T, K> *k){
    k->dajWierzcholek1()->usunIncydencje(k);
    k->dajWierzcholek2()->usunIncydencje(k);
    krawedzie->usunOgniwo(k->dajMiejsce());
    delete k;
}

template<typename T, typename K>
wierzcholek<T, K> *graf_lista<T, K>::dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k){
    if(k->dajWierzcholek1() == w)
	return k->dajWierzcholek2();
    else if(k->dajWierzcholek2() == w)
	return k->dajWierzcholek1();
    else
	return nullptr;
}

template<typename T, typename K>
bool graf_lista<T, K>::czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
    lista< krawedz<T, K>* > *l1, *l2;
    l1= w1->dajListeIncydencji();
    l2= w2->dajListeIncydencji();
	
    for(uint i= 0; i < l1->dajRozmiar(); i++)
	for(uint j= 0; j < l2->dajRozmiar(); j++)
	    if((*l1)[i]->dajWartosc() == (*l2)[j]->dajWartosc())
		return true;

    return false;
}

#endif
