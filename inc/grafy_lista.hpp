#ifndef GRAFY_LISTA_HPP
#define GRAFY_LISTA_HPP

#include "grafy_lista.h"

template<typename T, typename K>
wierzcholek<T, K> *graf_lista<T, K>::dodajWierzcholek(T wartosc){
    wierzcholek<T, K> *nowy_wierzcholek= wierzcholki + l_wierzcholkow;

    if(l_wierzcholkow >= rozmiar)
	return nullptr;
    
    nowy_wierzcholek->zmienWartosc(wartosc);
    l_wierzcholkow++;
    
    return nowy_wierzcholek;
}

template<typename T, typename K>
krawedz<T, K> *graf_lista<T, K>::dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
    krawedz<T, K> *nowa_krawedz= krawedzie + l_krawedzi;

    if(l_krawedzi >= max_krawedzi)
	return nullptr;
    
    nowa_krawedz->zmienWartosc(wartosc);
    incydencje[w1->dajKlucz()].dodajOgniwo(nowa_krawedz);
    incydencje[w2->dajKlucz()].dodajOgniwo(nowa_krawedz);
    l_krawedzi++;
	
    return nowa_krawedz;
}

template<typename T, typename K>
krawedz<T, K> *graf_lista<T, K>::dodajKrawedz(K wartosc, uint k1, uint k2){
    krawedz<T, K> *nowa_krawedz= krawedzie + l_krawedzi;

    if(l_krawedzi >= max_krawedzi)
	return nullptr;
    
    nowa_krawedz->zmienWartosc(wartosc);
    incydencje[k1].dodajOgniwo(nowa_krawedz);
    incydencje[k2].dodajOgniwo(nowa_krawedz);
    l_krawedzi++;
	
    return nowa_krawedz;
}

template<typename T, typename K>
wierzcholek<T, K> *graf_lista<T, K>::dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k){
    cout << "todo\n";
}

template<typename T, typename K>
wierzcholek<T, K> *graf_lista<T, K>::dajPrzeciwleglyWierzcholek(uint w, krawedz<T, K> *k){
    cout << "todo\n";
}

template<typename T, typename K>
bool graf_lista<T, K>::czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
    lista< krawedz<T, K>* > *l1, *l2;
    uint r1, r2;
    
    l1= incydencje[w1->dajKlucz()];
    l2= incydencje[w2->dajKlucz()];
    r1= l1->dajRozmiar();
    r2= l2->dajRozmiar();
	
    for(uint i= 0; i < r1; i++)
	for(uint j= 0; j < r2; j++)
	    if(l1->dajOgniwo(i)->dajWartosc() == l2->dajOgniwo(j)->dajWartosc())
		return true;

    return false;
}

template<typename T, typename K>
bool graf_lista<T, K>::czySasiedzi(uint w1, uint w2){
    lista< krawedz<T, K>* > *l1, *l2;
    uint r1, r2;
    
    l1= incydencje[w1];
    l2= incydencje[w2];
    r1= l1->dajRozmiar();
    r2= l2->dajRozmiar();
	
    for(uint i= 0; i < r1; i++)
	for(uint j= 0; j < r2; j++)
	    if(l1->dajOgniwo(i)->dajWartosc() == l2->dajOgniwo(j)->dajWartosc())
		return true;

    return false;
}

#endif
