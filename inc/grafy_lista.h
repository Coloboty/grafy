#ifndef GRAFY_LISTA_H
#define GRAFY_LISTA_H

#include <iostream>
#include <memory>
#include "lista.hpp"

using namespace std;

template<typename T, typename K> class lkrawedz;

template <typename T, typename K>
class lwierzcholek{
private:
    T wartosc;
    ogniwo< lwierzcholek<T, K>* > *miejsce;
    lista< lkrawedz<T, K>* > *incydencje;

public:
    lwierzcholek(T w){
	wartosc= w;
	incydencje= new lista< lkrawedz<T, K>* >;
    }

    ~lwierzcholek(){
	delete incydencje;
    }
    
    void zmienMiejsce(ogniwo< lwierzcholek<T, K>* > *moje) {miejsce= moje;}
    void zmienWartosc(T nowa) {wartosc= nowa;}

    ogniwo< lkrawedz<T, K>* > *dodajIncydencje(lkrawedz<T, K> *k){
	return incydencje->dodajZa(k, incydencje->dajPierwsze());
    }

    void usunIncydencje(lkrawedz<T, K> *k){
	incydencje->usunOgniwo(k->dajIncydencje(this));
    }

    lista< lkrawedz<T, K>* > *dajListeIncydencji(void) {return incydencje;}
    
    T dajWartosc(void) {return wartosc;};
    ogniwo< lwierzcholek<T, K>* > *dajMiejsce(void) {return miejsce;}
};

/* ----------------------------------------- */

template <typename T, typename K>
class lkrawedz{
private:
    K wartosc;
    ogniwo< lkrawedz<T, K>* > *miejsce, *i1, *i2;
    lwierzcholek<T, K> *w1, *w2;

public:
    lkrawedz(T w, lwierzcholek<T, K> *w_1, lwierzcholek<T, K> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    void zmienWartosc(K w) {wartosc= w;}
    void zmienMiejsce(ogniwo< lkrawedz<T, K>* > *moje) {miejsce= moje;}
    void zmienIncydencje(ogniwo< lkrawedz<T, K>* > *i, lwierzcholek<T, K> *w){
	if(w == w1)
	    i1= i;
	else if(w == w2)
	    i2= i;
    }
    
    ogniwo< lkrawedz<T, K>* > *dajMiejsce(void) {return miejsce;}
    
    shared_ptr< lista< lwierzcholek<T, K>* > > dajWierzcholki(void){
	shared_ptr< lista< lwierzcholek<T, K>* > > liz= make_shared< lista< lwierzcholek<T, K>* > >();
	liz->dodajZa(w1, liz->dajPierwsze());
	liz->dodajZa(w2, liz->dajPierwsze());

	return liz;
    }

    K dajWartosc(void) {return wartosc;}
    ogniwo< lkrawedz<T, K>* > *dajIncydencje(lwierzcholek<T, K> *w){
	if(w == w1)
	    return i1;
	else if(w == w2)
	    return i2;
	else
	    return nullptr;
    }
};

/* -------------------------- */

template <typename T, typename K>
class graf_lista{
private:
    lista< lwierzcholek<T, K>* > *wierzcholki;
    lista< lkrawedz<T, K>* > *lkrawedzie;
    
public:
    graf_lista(){
	wierzcholki= new(lista< lwierzcholek<T, K>* >);
	lkrawedzie= new(lista< lkrawedz<T, K>* >);
    }
    
    ~graf_lista(){
	while(wierzcholki->dajRozmiar() > 0)
	    usunWierzcholek(wierzcholki->dajPierwsze()->dajWartosc());
	
	delete wierzcholki;
	delete lkrawedzie;
    }
    /* ------------ */
    T dajWartosc(lwierzcholek<T, K> *w){
	return w->dajWartosc();
    }

    K dajWartosc(lkrawedz<T, K> *k){
	return k->dajWartosc();
    }
    

    lwierzcholek<T, K> *dodajWierzcholek(T wartosc);
    lkrawedz<T, K> *dodajKrawedz(K wartosc, lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2);
					
    void usunWierzcholek(lwierzcholek<T, K> *w);
    void usunKrawedz(lkrawedz<T, K> *k);

    /* --------------------- */

    shared_ptr< lista< lwierzcholek<T, K>* > > dajKoncoweWierzcholki(lkrawedz<T, K> *k){
	return k->dajWierzcholki();
    }

    void zmienWartosc(lwierzcholek<T, K> *w, T wart) {w->zmienWartosc(wart);}
    void zmienWartosc(lkrawedz<T, K> *k, K wart) {k->zmienWartosc(wart);}

    lwierzcholek<T, K> *dajPrzeciwleglyWierzcholek(lwierzcholek<T, K> *w, lkrawedz<T, K> *k);
    lista< lkrawedz<T, K>* > *dajIncydentneKrawedzie(lwierzcholek<T, K> *w) {return w->dajListeIncydencji();}

    bool czySasiedzi(lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2);

    lista< lwierzcholek<T, K>* > *dajWierzcholki(void) {return wierzcholki;}
    lista< lkrawedz<T, K>* > *dajKrawedzie(void) {return lkrawedzie;}
};

#endif
