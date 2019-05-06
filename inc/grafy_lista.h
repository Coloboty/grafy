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

    lwierzcholek(){
	wartosc= 0;
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
    lwierzcholek<T, K> *w1, *w2;

public:
    lkrawedz(T w, lwierzcholek<T, K> *w_1, lwierzcholek<T, K> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    lkrawedz(){
	wartosc= 0;
	w1= nullptr;
	w2= nullptr;
    }

    void zmienWartosc(K w) {wartosc= w;}
    void zmienW1(lwierzcholek<T, K> *w) {w1= w;}
    void zmienW2(lwierzcholek<T, K> *w) {w2= w;}
    
    shared_ptr< lista< lwierzcholek<T, K>* > > dajWierzcholki(void){
	shared_ptr< lista< lwierzcholek<T, K>* > > liz= make_shared< lista< lwierzcholek<T, K>* > >();
	liz->dodajZa(w1, liz->dajPierwsze());
	liz->dodajZa(w2, liz->dajPierwsze());

	return liz;
    }

    lwierzcholek<T, K> *dajW1(void) {return w1;}
    lwierzcholek<T, K> *dajW2(void) {return w2;}

    K dajWartosc(void) {return wartosc;}
};

/* -------------------------- */

template <typename T, typename K>
class graf_lista{
private:
    lwierzcholek<T, K> *wierzcholki;
    lkrawedz<T, K> *krawedzie;
    uint rozmiar, max_krawedzi;
    uint l_wierzcholkow, l_krawedzi;
    
public:
    graf_lista(uint r){
	rozmiar= r;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	wierzcholki= new lwierzcholek<T, K>[rozmiar];
	krawedzie= new lkrawedz<T, K>[max_krawedzi];
	l_wierzcholkow= l_krawedzi= 0;
    }
    
    ~graf_lista(){
	delete[] wierzcholki;
	delete[] krawedzie;
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

    lwierzcholek<T, K> *dajW1(lkrawedz<T, K> *k) {return k->dajWierzcholek1();}
    lwierzcholek<T, K> *dajW2(lkrawedz<T, K> *k) {return k->dajWierzcholek2();}

    void zmienWartosc(lwierzcholek<T, K> *w, T wart) {w->zmienWartosc(wart);}
    void zmienWartosc(lkrawedz<T, K> *k, K wart) {k->zmienWartosc(wart);}

    lwierzcholek<T, K> *dajPrzeciwleglyWierzcholek(lwierzcholek<T, K> *w, lkrawedz<T, K> *k);
    lista< lkrawedz<T, K>* > *dajIncydentneKrawedzie(lwierzcholek<T, K> *w) {return w->dajListeIncydencji();}

    bool czySasiedzi(lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2);

    lwierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    lwierzcholek<T, K> dajWierzcholek(uint i) {return wierzcholki+i;}
    lkrawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    lkrawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}
    
};

#endif
