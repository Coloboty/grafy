#ifndef GRAFY_LISTA_H
#define GRAFY_LISTA_H

#include <iostream>
#include "lista.hpp"



template <typename T>
class wierzcholek{
private:
    T wartosc;
    /* ogniwo< wierzcholek<T>* > *miejsce; */
    /* lista< krawedz<T> *> *incydencje; */

public:
    /* wierzcholek(ogniwo< wierzcholek<T>* > *moje) {miejsce= moje;} */
    wierzcholek(T w) {wartosc= w;}
    /* void zmienMiejsce(ogniwo< wierzcholek<T>* > *moje) {miejsce= moje;} */

    void zmienWartosc(T nowa){wartosc= nowa;}
    
    T dajWartosc(void) {return wartosc;};
    /* ogniwo< wierzcholek<T>* > *dajMiejsce(void) {return miejsce;} */
};

template <typename T, typename K>
class krawedz{
private:
    K wartosc;
    ogniwo< krawedz<T, K>* > *miejsce;
    ogniwo< wierzcholek<T>* > *w1, *w2;

public:
    krawedz(T w,
	    ogniwo< wierzcholek<T>* > *w_1,
	    ogniwo< wierzcholek<T>* > *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

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

    T dajWartosc(ogniwo< wierzcholek<T>* > *w){
	return w->dajWartosc()->dajWartosc();
    }

    K dajWartosc(ogniwo< krawedz<T, K>* > *k){
	return k->dajWartosc()->dajWartosc();
    }

    ogniwo< wierzcholek<T>* > *dodajWierzcholek(T wartosc){
	wierzcholek<T> *nowy_wierzcholek= new(wierzcholek<T>)(wartosc);
	return wierzcholki->dodajZa(nowy_wierzcholek, wierzcholki->dajPierwsze());
    }

    ogniwo< krawedz<T, K>* > *dodajKrawedz(
	K wartosc,
	ogniwo< wierzcholek<T>* > *w1,
	ogniwo< wierzcholek<T>* > *w2){
	krawedz<T, K> *nowa_krawedz= new krawedz<T, K>(wartosc, w1, w2);
	return krawedzie->dodajZa(nowa_krawedz, krawedzie->dajPierwsze());
    }
					

    void usunWierzcholek(ogniwo< wierzcholek<T>* > *w){
	wierzcholki->usunOgniwo(w);
    }
};

#endif
