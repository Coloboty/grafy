#ifndef GRAFY_LISTA_HPP
#define GRAFY_LISTA_HPP

#include "grafy_lista.h"

template<typename T, typename K>
lwierzcholek<T, K> *graf_lista<T, K>::dodajWierzcholek(T wartosc){
    lwierzcholek<T, K> *nowy_lwierzcholek= new(lwierzcholek<T, K>)(wartosc);
    ogniwo< lwierzcholek<T, K>* > *miejsce_nowego= wierzcholki->dodajZa(nowy_lwierzcholek, wierzcholki->dajPierwsze());
    nowy_lwierzcholek->zmienMiejsce(miejsce_nowego);
	
    return nowy_lwierzcholek;
}

template<typename T, typename K>
lkrawedz<T, K> *graf_lista<T, K>::dodajKrawedz(K wartosc, lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2){
    ogniwo< lkrawedz<T, K>* > *i1, *i2;
    lkrawedz<T, K> *nowa_lkrawedz= new lkrawedz<T, K>(wartosc, w1, w2);
    ogniwo< lkrawedz<T, K>* > *miejsce_nowej= lkrawedzie->dodajZa(nowa_lkrawedz, lkrawedzie->dajPierwsze());
    nowa_lkrawedz->zmienMiejsce(miejsce_nowej);

    i1= w1->dodajIncydencje(nowa_lkrawedz);
    i2= w2->dodajIncydencje(nowa_lkrawedz);

    nowa_lkrawedz->zmienIncydencje(i1, w1);
    nowa_lkrawedz->zmienIncydencje(i2, w2);
	
    return nowa_lkrawedz;
}

template<typename T, typename K>
void graf_lista<T, K>::usunWierzcholek(lwierzcholek<T, K> *w){
    lista< lkrawedz<T, K>* > *inc= w->dajListeIncydencji();
    while(inc->dajRozmiar() > 0)
	usunKrawedz(inc->dajPierwsze()->dajWartosc());
	
    wierzcholki->usunOgniwo(w->dajMiejsce());
    delete w;
}

template<typename T, typename K>
void graf_lista<T, K>::usunKrawedz(lkrawedz<T, K> *k){
    k->dajWierzcholek1()->usunIncydencje(k);
    k->dajWierzcholek2()->usunIncydencje(k);
    lkrawedzie->usunOgniwo(k->dajMiejsce());
    delete k;
}

template<typename T, typename K>
lwierzcholek<T, K> *graf_lista<T, K>::dajPrzeciwleglyWierzcholek(lwierzcholek<T, K> *w, lkrawedz<T, K> *k){
    if(k->dajWierzcholek1() == w)
	return k->dajWierzcholek2();
    else if(k->dajWierzcholek2() == w)
	return k->dajWierzcholek1();
    else
	return nullptr;
}

template<typename T, typename K>
bool graf_lista<T, K>::czySasiedzi(lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2){
    lista< lkrawedz<T, K>* > *l1, *l2;
    l1= w1->dajListeIncydencji();
    l2= w2->dajListeIncydencji();
	
    for(uint i= 0; i < l1->dajRozmiar(); i++)
	for(uint j= 0; j < l2->dajRozmiar(); j++)
	    if((*l1)[i]->dajWartosc() == (*l2)[j]->dajWartosc())
		return true;

    return false;
}

#endif
