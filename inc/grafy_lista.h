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
    uint klucz;
        
public:
    lwierzcholek(T w, uint k){
	wartosc= w;
	klucz= k;
    }

    lwierzcholek(){
	wartosc= 0;
	klucz= 0;
    }

    ~lwierzcholek(){
    }
    
    void zmienWartosc(T nowa) {wartosc= nowa;}
    T dajWartosc(void) {return wartosc;};
    void zmienKlucz(uint k){klucz= k;}
    uint dajKlucz(void) {return klucz;}
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
    lista< lkrawedz<T, K>* > *incydencje;
    uint rozmiar, max_krawedzi;
    uint l_wierzcholkow, l_krawedzi;
    
public:
    graf_lista(uint r){
	rozmiar= r;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	l_wierzcholkow= l_krawedzi= 0;
	
	wierzcholki= new lwierzcholek<T, K>[rozmiar];
	krawedzie= new lkrawedz<T, K>[max_krawedzi];
	incydencje= new lista< lkrawedz<T,K>* >[rozmiar];

	for(uint i= 0; i < rozmiar; i++){
	    wierzcholki[i].zmienKlucz(i);
	}
    }
    
    ~graf_lista(){
	delete[] wierzcholki;
	delete[] krawedzie;
	delete[] incydencje;
    }
    
    /* ------------ */
    
    lwierzcholek<T, K> *dodajWierzcholek(T wartosc);
    lkrawedz<T, K> *dodajKrawedz(K wartosc, lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2);
					
    void usunWierzcholek(lwierzcholek<T, K> *w);
    void usunKrawedz(lkrawedz<T, K> *k);

    /* --------------------- */

    lwierzcholek<T, K> *dajW1(lkrawedz<T, K> *k) {return k->dajW1();}
    lwierzcholek<T, K> *dajW2(lkrawedz<T, K> *k) {return k->dajW2();}

    void zmienWartosc(lwierzcholek<T, K> *w, T wart) {w->zmienWartosc(wart);}
    void zmienWartosc(lkrawedz<T, K> *k, K wart) {k->zmienWartosc(wart);}

    lwierzcholek<T, K> *dajPrzeciwleglyWierzcholek(lwierzcholek<T, K> *w, lkrawedz<T, K> *k);
    

    bool czySasiedzi(lwierzcholek<T, K> *w1, lwierzcholek<T, K> *w2);

    lwierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    lwierzcholek<T, K> *dajWierzcholek(uint i) {return wierzcholki+i;}
    lkrawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    lista< lkrawedz<T, K>* > *dajKrawedzie(lwierzcholek<T, K> *w) {return incydencje+w->dajKlucz();}
    lista< lkrawedz<T, K>* > *dajKrawedzie(uint i) {return incydencje+i;}
    lkrawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}
    
};

#endif
