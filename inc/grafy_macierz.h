#ifndef GRAFY_MACIERZ_H
#define GRAFY_MACIERZ_H

#include <iostream>
#include <memory>
#include "grafy_klasy.h"

using namespace std;

/* ----------------------------- */

template <typename T, typename K>
class graf_macierz{
private:
    uint rozmiar, max_krawedzi;
    uint l_krawedzi, l_wierzcholkow;
    wierzcholek<T, K> *wierzcholki;
    krawedz<T, K> *krawedzie;
    krawedz<T, K> **macierz;

    krawedz<T, K> *zMacierzy(uint r, uint k) {return macierz[r*rozmiar + k];}
    
    void doMacierzy(uint r, uint k, krawedz<T, K> *elem){
	if(r >= rozmiar || k >= rozmiar || r == k)
	    return;
	macierz[r*rozmiar + k]= elem;
    }
    
public:
    graf_macierz(uint n){
	rozmiar= n;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	l_krawedzi= 0;
	l_wierzcholkow= 0;
	wierzcholki= new wierzcholek<T, K>[rozmiar];

	/* Zawsze rezerwujemy wystarczająco dużo pamięci na pełny graf, */
	/* bo tak łatwiej */
	krawedzie= new krawedz<T, K>[max_krawedzi];

	
	macierz= new krawedz<T, K>*[rozmiar*rozmiar];

	/* Porządek w macierzy i klucze po kolei */
	for(uint i= 0; i < rozmiar; i++){
	    macierz[i]= nullptr;
	    wierzcholki[i].zmienKlucz(i);
	}
    }

    ~graf_macierz(){
	delete[] wierzcholki;
	delete[] krawedzie;
	delete[] macierz;
    }
    
    /* Metody główne */

    wierzcholek<T, K> *dodajWierzcholek(T wartosc){
	wierzcholek<T, K> *w= wierzcholki + l_wierzcholkow;
	
	if(l_wierzcholkow >= rozmiar)
	    return nullptr;

	zmienWartosc(w, wartosc);
	
	l_wierzcholkow++;
	
	return w;
    }

    krawedz<T, K> *dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
	krawedz<T, K> *nowa_krawedz= krawedzie + l_krawedzi;
	
	if(l_krawedzi >= max_krawedzi)
	    return nullptr;

	nowa_krawedz->zmienWartosc(wartosc);
	nowa_krawedz->zmienW1(w1);
	nowa_krawedz->zmienW2(w2);
	
	doMacierzy(w1->dajKlucz(), w2->dajKlucz(), nowa_krawedz);
	doMacierzy(w2->dajKlucz(), w1->dajKlucz(), nowa_krawedz);
	
	l_krawedzi++;

	return nowa_krawedz;
    }

    void zmienWartosc(wierzcholek<T, K> *w, T nowa) {w->zmienWartosc(nowa);}
    void zmienWartosc(krawedz<T, K> *k, K nowa) {k->zmienWartosc(nowa);}
    T dajWartosc(wierzcholek<T, K> *w) {return w->dajWartosc();}
    K dajWartosc(krawedz<T, K> *k) {return k->dajWartosc();}

    /* --- */

    wierzcholek<T, K> *dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k){
	wierzcholek<T, K> *w1, *w2;
	w1= k->dajW1();
	w2= k->dajW2();

	if(w == w1)
	    return w2;
	else if(w == w2)
	    return w1;
	else
	    return nullptr;
    }

    uint dajLiczbeIncydencji(wierzcholek<T, K> *w){
	uint klucz, licznik;
	krawedz<T, K> *k;
	
	licznik=  0;
	klucz= w->dajKlucz();
	
	for(uint i= 0; i < rozmiar; i++){
	    k= zMacierzy(klucz, i);
	    if(k != nullptr)
		licznik++;
	}

	return licznik;
    }

    bool czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
	uint klucz1, klucz2;
	krawedz<T, K> *k;
	klucz1= w1->dajKlucz();
	klucz2= w2->dajKlucz();

	k= zMacierzy(klucz1, klucz2);
	if(k != nullptr)
	    return true;
	else
	    return false;
    }
    
    void drukujMacierz(void){
	krawedz<T, K> *k;
	
	for(uint i= 0; i < rozmiar; i++){
	    for(uint j= 0; j <= rozmiar-1; j++){
		k= zMacierzy(i, j);
		if(k != nullptr)
		    cout << k->dajWartosc() << "   ";
		else if(i == j)
		    cout << "----   ";
		else
		    cout << "null   ";
	    }
	    cout << '\n';
	}
    }

    void losujMacierz(uint gestosc){
	uint dzielnik;

	if(gestosc == 25 || gestosc == 75)
	    dzielnik= 4;
	else if(gestosc == 50)
	    dzielnik= 2;
	else if(gestosc == 100)
	    dzielnik= 1;
	srand( time(NULL) );

	/* Drzewo rozpinające */
	for(uint i= 0; i < rozmiar-1; i++){
	    dodajKrawedz(rand()%100+1000, wierzcholki+i, wierzcholki+i+1);
	}
		
	if(gestosc != 75){
	    for(uint i= 0; i < rozmiar-1; i++){
		for(uint j= i+2; j < rozmiar; j++){
		    if((i+j)%dzielnik == 0){		    
			dodajKrawedz(rand()%100+1000, wierzcholki+j, wierzcholki+i);
		    }
		}
	    }
	}
	else{
	    for(uint i= 0; i < rozmiar-1; i++){
		for(uint j= i+2; j < rozmiar; j++){
		    if((i+j)%dzielnik != 0){		    
			dodajKrawedz(rand()%100+1000, wierzcholki+j, wierzcholki+i);
		    }
		}
	    }
	}
    }

    wierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    wierzcholek<T, K> *dajWierzcholek(uint i) {return wierzcholki+i;}
    
    krawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    krawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}

    krawedz<T, K> *dajKrawedz(uint k1, uint k2) {return zMacierzy(k1, k2);}
        krawedz<T, K> *dajKrawedz(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
	return zMacierzy(w1->dajKlucz(), w2->dajKlucz());
    }

    shared_ptr< lista< krawedz<T, K>* > > dajKrawedzie(wierzcholek<T, K> *w){
	krawedz<T, K> *k;
	uint klucz= w->dajKlucz();
	shared_ptr< lista< krawedz<T, K>* > > l= make_shared< lista< krawedz<T, K>* > >();
	
	for(uint i= 0; i < rozmiar; i++){
	    k= zMacierzy(i, klucz);
	    if(k != nullptr)
		l->dodajOgniwo(k);
	}
	
	return l;
    }
    
    uint dajLiczbeKrawedzi(void) {return l_krawedzi;}
    uint dajRozmiar(void) {return rozmiar;}
};

#endif
