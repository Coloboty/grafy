#ifndef GRAFY_MACIERZ_H
#define GRAFY_MACIERZ_H

#include <iostream>
using namespace std;

template <typename T>
class mwierzcholek{
private:
    T wartosc;
    uint klucz;
    ogniwo< mwierzcholek<T>* > *miejsce;
    
public:
    mwierzcholek(T w, uint k){
	wartosc= w;
	klucz= k;
    }
        
    void zmienMiejsce(ogniwo< mwierzcholek<T>* > *moje) {miejsce= moje;}
    void zmienWartosc(T nowa) {wartosc= nowa;}
    void zmienKlucz(uint k) {klucz= k;}
    
    T dajWartosc(void) {return wartosc;}
    ogniwo< mwierzcholek<T>* > *dajMiejsce(void) {return miejsce;}
    uint dajKlucz(void) {return klucz;}
};

/* ----------------------------- */

template <typename T, typename K>
class mkrawedz{
private:
    K wartosc;
    ogniwo< mkrawedz<T, K>* > *miejsce;
    mwierzcholek<T> *w1, *w2;

public:
    mkrawedz(K w, mwierzcholek<T> *w_1, mwierzcholek<T> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    void zmienWartosc(K nowa) {wartosc= nowa;}
    K dajWartosc(void) {return wartosc;}
    
    void zmienMiejsce(ogniwo< mkrawedz<T, K>* > *nowe) {miejsce= nowe;}
    ogniwo< mkrawedz<T, K>* > *dajMiejsce(void) {return miejsce;}
    
    mwierzcholek<T> *dajWierzcholek1(void) {return w1;}
    mwierzcholek<T> *dajWierzcholek2(void) {return w2;}
};

/* ----------------------------- */

template <typename T, typename K>
class graf_macierz{
private:
    uint rozmiar;
    lista< mwierzcholek<T>* > *wierzcholki;
    lista< mkrawedz<T, K>* > *krawedzie;
    mkrawedz<T, K> **macierz;

    mkrawedz<T, K> *zMacierzy(uint r, uint k) {return macierz[r*rozmiar + k];}
    
    void doMacierzy(uint r, uint k, mkrawedz<T, K> *elem){
	if(r >= rozmiar || k >= rozmiar)
	    return;
	macierz[r*rozmiar + k]= elem;
    }
    
public:
    graf_macierz(uint n){
	wierzcholki= new lista< mwierzcholek<T>* >;
	krawedzie= new lista< mkrawedz<T, K>* >;

	rozmiar= n;
	macierz= new mkrawedz<T, K>*[n*n];
	
	for(uint i= 0; i < n; i++)
	    macierz[i]= nullptr;
    }

    ~graf_macierz(){
	delete wierzcholki;
	delete krawedzie;
    }
    
    /* --- */

    mwierzcholek<T> *dodajWierzcholek(T wartosc){
	mwierzcholek<T> *nowy_wierzcholek= new mwierzcholek<T>(wartosc, wierzcholki->dajRozmiar());
	ogniwo< mwierzcholek<T>* > *miejsce_nowego= wierzcholki->dodajZa(nowy_wierzcholek, wierzcholki->dajPierwsze());
	nowy_wierzcholek->zmienMiejsce(miejsce_nowego);
	return nowy_wierzcholek;
    }

    mkrawedz<T, K> *dodajKrawedz(K wartosc, mwierzcholek<T> *w1, mwierzcholek<T> *w2){
	mkrawedz<T, K> *nowa_krawedz= new mkrawedz<T, K>(wartosc, w1, w2);
	ogniwo< mkrawedz<T, K>* > *miejsce_nowej= krawedzie->dodajZa(nowa_krawedz, krawedzie->dajPierwsze());
	nowa_krawedz->zmienMiejsce(miejsce_nowej);

	doMacierzy(w1->dajKlucz(), w2->dajKlucz(), nowa_krawedz);
	doMacierzy(w2->dajKlucz(), w1->dajKlucz(), nowa_krawedz);

	return nowa_krawedz;
    }

    void usunWierzcholek(mwierzcholek<T> *w){
	mkrawedz<T, K> *k;
	uint klucz= w->dajKlucz();

	for(uint i= 0; i < rozmiar; i++){
	    k= zMacierzy(klucz, i);
	    if(k != nullptr){
		delete k;
		doMacierzy(klucz, i, nullptr);
		doMacierzy(i, klucz, nullptr);
	    }
	}
	
	wierzcholki->usunOgniwo(w->dajMiejsce());
	delete w;
    }

    void usunKrawedz(mkrawedz<T, K> *k){
	uint klucz1, klucz2;
	klucz1= k->dajWierzcholek1()->dajKlucz();
	klucz2= k->dajWierzcholek2()->dajKlucz();

	doMacierzy(klucz1, klucz2, nullptr);
	doMacierzy(klucz2, klucz1, nullptr);

	krawedzie->usunOgniwo(k->dajMiejsce());
	delete k;
    }

    void zmienWartosc(mwierzcholek<T> *w, T nowa) {w->zmienWartosc(nowa);}
    void zmienWartosc(mkrawedz<T, K> *k, K nowa) {k->zmienWartosc(nowa);}
    T dajWartosc(mwierzcholek<T> *w) {return w->dajWartosc();}
    K dajWartosc(mkrawedz<T, K> *k) {return k->dajWartosc();}

    /* --- */
    
    mwierzcholek<T> *dajKoncowyWierzcholek1(mkrawedz<T, K> *k) {return k->dajWierzcholek1();}
    mwierzcholek<T> *dajKoncowyWierzcholek2(mkrawedz<T, K> *k){return k->dajWierzcholek2();}

    mwierzcholek<T> *dajPrzeciwleglyWierzcholek(mwierzcholek<T> *w, mkrawedz<T, K> *k){
	mwierzcholek<T> *w1, *w2;
	w1= k->dajWierzcholek1();
	w2= k->dajWierzcholek2();

	if(w == w1)
	    return w2;
	else if(w == w2)
	    return w1;
	else
	    return nullptr;
    }

    /* tutaj przydałby się shared_ptr */
    lista< mkrawedz<T, K>* > *dajIncydentneKrawedzie(mwierzcholek<T> *w){
	mkrawedz<T, K> *k;
	uint klucz= w->dajKlucz();
	lista< mkrawedz<T, K>* > *l= new lista< mkrawedz<T, K>* >;

	for(uint i= 0; i < rozmiar; i++){
	    k= zMacierzy(klucz, i);
	    if(k != nullptr)
		l->dodajZa(k->dajWartosc(), l->dajPierwsze());

	    return l;
	}
    }

    bool czySasiedzi(mwierzcholek<T> *w1, mwierzcholek<T> *w2){
	uint klucz1, klucz2;
	mkrawedz<T, K> *k;
	klucz1= w1->dajKlucz();
	klucz2= w2->dajKlucz();

	k= zMacierzy(klucz1, klucz2);
	if(k != nullptr)
	    return true;
	else
	    return false;
    }
    
    void drukujMacierz(void){
	mkrawedz<T, K> *k;
	
	for(uint i= 0; i < rozmiar; i++){
	    for(uint j= 0; j < rozmiar; j++){
		k= zMacierzy(i, j);
		if(k != nullptr)
		    cout << k->dajWartosc() << "   ";
		else
		    cout << "null   ";
	    }
	    cout << '\n';
	}
    }

    lista< mwierzcholek<T>* > *dajWierzcholki(void) {return wierzcholki;}
    lista< mkrawedz<T, K>* > *dajKrawedzie(void) {return krawedzie;}
};

#endif
