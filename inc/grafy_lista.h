#ifndef GRAFY_LISTA_H
#define GRAFY_LISTA_H

#include <iostream>
#include "lista.hpp"



template <typename T>
class wierzcholek{
private:
    T wartosc;
    ogniwo< wierzcholek<T>* > *miejsce;
    /* lista< krawedz<T> *> *incydencje; */

public:
    wierzcholek(T w) {wartosc= w;}
    
    void zmienMiejsce(ogniwo< wierzcholek<T>* > *moje) {miejsce= moje;}
    void zmienWartosc(T nowa){wartosc= nowa;}
    
    T dajWartosc(void) {return wartosc;};
    ogniwo< wierzcholek<T>* > *dajMiejsce(void) {return miejsce;}
};

template <typename T, typename K>
class krawedz{
private:
    K wartosc;
    ogniwo< krawedz<T, K>* > *miejsce;
    wierzcholek<T> *w1, *w2;

public:
    krawedz(T w, wierzcholek<T> *w_1, wierzcholek<T> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    void zmienWartosc(K w) {wartosc= w;}
    void zmienMiejsce(ogniwo< krawedz<T, K>* > *moje) {miejsce= moje;}

    ogniwo< krawedz<T, K>* > *dajMiejsce(void) {return miejsce;}
    K dajWartosc(void) {return wartosc;}
};


template <typename T, typename K>
class graf_lista{
private:
    lista< wierzcholek<T>* > *wierzcholki;
    lista< krawedz<T, K>* > *krawedzie;
    /* lista< lista< krawedz<T> *> > incydencje; */

public:
    graf_lista(){
	wierzcholki= new(lista< wierzcholek<T>* >);
	krawedzie= new(lista< krawedz<T, K>* >);
    }

    ~graf_lista(){
	delete wierzcholki;
	delete krawedzie;
    }

    
    T dajWartosc(wierzcholek<T> *w){
	return w->dajWartosc();
    }

    K dajWartosc(krawedz<T, K> *k){
	return k->dajWartosc();
    }
    

    wierzcholek<T> *dodajWierzcholek(T wartosc){
	wierzcholek<T> *nowy_wierzcholek= new(wierzcholek<T>)(wartosc);
	ogniwo< wierzcholek<T>* > *miejsce_nowego= wierzcholki->dodajZa(nowy_wierzcholek, wierzcholki->dajPierwsze());
	nowy_wierzcholek->zmienMiejsce(miejsce_nowego);
	return nowy_wierzcholek;
    }

    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T> *w1, wierzcholek<T> *w2){
	krawedz<T, K> *nowa_krawedz= new krawedz<T, K>(wartosc, w1, w2);
	ogniwo< krawedz<T, K>* > *miejsce_nowej= krawedzie->dodajZa(nowa_krawedz, krawedzie->dajPierwsze());
	nowa_krawedz->zmienMiejsce(miejsce_nowej);
	return nowa_krawedz;
    }
					
    void usunWierzcholek(wierzcholek<T> *w){
	wierzcholki->usunOgniwo(w->dajMiejsce);
    }

    void usunKrawedz(krawedz<T, K> *k){
	krawedzie->usunOgniwo(k->dajMiejsce());
    }
};

#endif
