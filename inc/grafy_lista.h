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
    /* void zmienIncydencje2(wierzcholek<T, K> *w){}; */

    ogniwo< krawedz<T, K>* > *dajMiejsce(void) {return miejsce;}
    wierzcholek<T, K> *dajWierzcholek1(void) {return w1;}
    wierzcholek<T, K> *dajWierzcholek2(void) {return w2;}
    
    ogniwo< krawedz<T, K>* > *dajIncydencje(wierzcholek<T, K> *w){
	if(w == w1)
	    return i1;
	else if(w == w2)
	    return i2;
	else
	    return nullptr;
    }
    /* ogniwo< krawedz<T, K>* > *dajIncydencje2(void) {return i2;} */
    K dajWartosc(void) {return wartosc;}
};

template <typename T, typename K>
class graf_lista{
private:
    lista< wierzcholek<T, K>* > *wierzcholki;
    lista< krawedz<T, K>* > *krawedzie;
    /* lista< lista< krawedz<T> *> > incydencje; */

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

    
    T dajWartosc(wierzcholek<T, K> *w){
	return w->dajWartosc();
    }

    K dajWartosc(krawedz<T, K> *k){
	return k->dajWartosc();
    }
    

    wierzcholek<T, K> *dodajWierzcholek(T wartosc){
	wierzcholek<T, K> *nowy_wierzcholek= new(wierzcholek<T, K>)(wartosc);
	ogniwo< wierzcholek<T, K>* > *miejsce_nowego= wierzcholki->dodajZa(nowy_wierzcholek, wierzcholki->dajPierwsze());
	nowy_wierzcholek->zmienMiejsce(miejsce_nowego);
	
	return nowy_wierzcholek;
    }

    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
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
					
    void usunWierzcholek(wierzcholek<T, K> *w){
	lista< krawedz<T, K>* > *inc= w->dajListeIncydencji();
	while(inc->dajRozmiar() > 0)
	    usunKrawedz(inc->dajPierwsze()->dajWartosc());
	
	wierzcholki->usunOgniwo(w->dajMiejsce());
	delete w;
    }

    void usunKrawedz(krawedz<T, K> *k){
	k->dajWierzcholek1()->usunIncydencje(k);
	k->dajWierzcholek2()->usunIncydencje(k);
	krawedzie->usunOgniwo(k->dajMiejsce());
	delete k;
    }
};

#endif
