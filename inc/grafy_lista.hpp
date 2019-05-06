#ifndef GRAFY_LISTA_HPP
#define GRAFY_LISTA_HPP

#include "grafy_lista.h"

template<typename T, typename K>
lwierzcholek<T, K> *graf_lista<T, K>::dodajWierzcholek(T wartosc){
    lwierzcholek<T, K> *nowy_wierzcholek= wierzcholki + l_wierzcholkow;

    if(l_wierzcholkow >= rozmiar)
	return nullptr;
    
    nowy_wierzcholek->zmienWartosc(wartosc);
    l_wierzcholkow++;
    
    return nowy_wierzcholek;
}

template<typename T, typename K>
lkrawedz<T, K> *graf_lista<T, K>::dodajKrawedz(K wartosc, lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2){
    lkrawedz<T, K> *nowa_krawedz= krawedzie + l_krawedzi;

    if(l_krawedzi >= max_krawedzi)
	return nullptr;
    
    nowa_krawedz->zmienWartosc(wartosc);
    incydencje[w1->dajKlucz()].dodajOgniwo(nowa_krawedz);
    incydencje[w2->dajKlucz()].dodajOgniwo(nowa_krawedz);
    l_krawedzi++;
	
    return nowa_krawedz;
}

template<typename T, typename K>
lkrawedz<T, K> *graf_lista<T, K>::dodajKrawedz(K wartosc, uint k1, uint k2){
    lkrawedz<T, K> *nowa_krawedz= krawedzie + l_krawedzi;

    if(l_krawedzi >= max_krawedzi)
	return nullptr;
    
    nowa_krawedz->zmienWartosc(wartosc);
    incydencje[k1].dodajOgniwo(nowa_krawedz);
    incydencje[k2].dodajOgniwo(nowa_krawedz);
    l_krawedzi++;
	
    return nowa_krawedz;
}

template<typename T, typename K>
void graf_lista<T, K>::usunWierzcholek(lwierzcholek<T, K> *w){
    cout << "todo\n";
}

template<typename T, typename K>
void graf_lista<T, K>::usunKrawedz(lkrawedz<T, K> *k){
    cout << "todo\n";
}

template<typename T, typename K>
lwierzcholek<T, K> *graf_lista<T, K>::dajPrzeciwleglyWierzcholek(lwierzcholek<T, K> *w, lkrawedz<T, K> *k){
    cout << "todo\n";
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
