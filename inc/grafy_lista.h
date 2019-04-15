#ifndef GRAFY_LISTA_H
#define GRAFY_LISTA_H

#include <iostream>
/* #include "lista.hpp" */

template<typename T, typename K> class krawedz;

template <typename T, typename K>
class wierzcholek{
private:
    T wartosc;
    ogniwo< wierzcholek<T, K>* > *miejsce;
    lista< krawedz<T, K>* > *incydencje;

public:
    wierzcholek(T w){
	wartosc= w;
	incydencje= new lista< krawedz<T, K>* >;
    }

    ~wierzcholek(){
	delete incydencje;
    }
    
    void zmienMiejsce(ogniwo< wierzcholek<T, K>* > *moje) {miejsce= moje;}
    void zmienWartosc(T nowa) {wartosc= nowa;}

    ogniwo< krawedz<T, K>* > *dodajIncydencje(krawedz<T, K> *k){
	return incydencje->dodajZa(k, incydencje->dajPierwsze());
    }

    void usunIncydencje(krawedz<T, K> *k){
	incydencje->usunOgniwo(k->dajIncydencje(this));
    }

    lista< krawedz<T, K>* > *dajListeIncydencji(void) {return incydencje;}
    
    T dajWartosc(void) {return wartosc;};
    ogniwo< wierzcholek<T, K>* > *dajMiejsce(void) {return miejsce;}
};

/* ----------------------------------------- */

template <typename T, typename K>
class krawedz{
private:
    K wartosc;
    ogniwo< krawedz<T, K>* > *miejsce, *i1, *i2;
    wierzcholek<T, K> *w1, *w2;

public:
    krawedz(T w, wierzcholek<T, K> *w_1, wierzcholek<T, K> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    void zmienWartosc(K w) {wartosc= w;}
    void zmienMiejsce(ogniwo< krawedz<T, K>* > *moje) {miejsce= moje;}
    void zmienIncydencje(ogniwo< krawedz<T, K>* > *i, wierzcholek<T, K> *w){
	if(w == w1)
	    i1= i;
	else if(w == w2)
	    i2= i;
    }
    
    ogniwo< krawedz<T, K>* > *dajMiejsce(void) {return miejsce;}
    wierzcholek<T, K> *dajWierzcholek1(void) {return w1;}
    wierzcholek<T, K> *dajWierzcholek2(void) {return w2;}

    K dajWartosc(void) {return wartosc;}
    ogniwo< krawedz<T, K>* > *dajIncydencje(wierzcholek<T, K> *w){
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
    lista< wierzcholek<T, K>* > *wierzcholki;
    lista< krawedz<T, K>* > *krawedzie;
    
public:
    graf_lista(){
	wierzcholki= new(lista< wierzcholek<T, K>* >);
	krawedzie= new(lista< krawedz<T, K>* >);
    }
    
    ~graf_lista(){
	while(wierzcholki->dajRozmiar() > 0)
	    usunWierzcholek(wierzcholki->dajPierwsze()->dajWartosc());
	
	delete wierzcholki;
	delete krawedzie;
    }
    /* ------------ */
    T dajWartosc(wierzcholek<T, K> *w){
	return w->dajWartosc();
    }

    K dajWartosc(krawedz<T, K> *k){
	return k->dajWartosc();
    }
    

    wierzcholek<T, K> *dodajWierzcholek(T wartosc);
    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);
					
    void usunWierzcholek(wierzcholek<T, K> *w);
    void usunKrawedz(krawedz<T, K> *k);

    /* --------------------- */

    wierzcholek<T, K> *dajKoncowyWierzcholek1(krawedz<T, K> *k) {return k->dajWierzcholek1();}
    wierzcholek<T, K> *dajKoncowyWierzcholek2(krawedz<T, K> *k){return k->dajWierzcholek2();}

    void zmienWartosc(wierzcholek<T, K> *w, T wart) {w->zmienWartosc(wart);}
    void zmienWartosc(krawedz<T, K> *k, K wart) {k->zmienWartosc(wart);}

    wierzcholek<T, K> *dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k);
    lista< krawedz<T, K>* > *dajIncydentneKrawedzie(wierzcholek<T, K> *w) {return w->dajListeIncydencji();}

    bool czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2);

    lista< wierzcholek<T, K>* > *dajWierzcholki(void) {return wierzcholki;}
    lista< krawedz<T, K>* > *dajKrawedzie(void) {return krawedzie;}
};

#endif
