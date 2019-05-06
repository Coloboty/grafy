#ifndef GRAFY_MACIERZ_H
#define GRAFY_MACIERZ_H

#include <iostream>
#include <memory>

using namespace std;

template <typename T, typename K>
class mwierzcholek{
private:
    T wartosc;
    uint klucz;
            
public:
    mwierzcholek(T w, uint k){
	wartosc= w;
	klucz= k;
    }

    mwierzcholek(){
	wartosc= 0;
	klucz= 0;
    }
    
    void zmienWartosc(T nowa) {wartosc= nowa;}
    T dajWartosc(void) {return wartosc;}
    void zmienKlucz(uint k) {klucz= k;}
    uint dajKlucz(void) {return klucz;}
};

/* ----------------------------- */

template <typename T, typename K>
class mkrawedz{
private:
    K wartosc;
    mwierzcholek<T, K> *w1, *w2;

public:
    mkrawedz(K w, mwierzcholek<T, K> *w_1, mwierzcholek<T, K> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    mkrawedz(){
	wartosc= 0;
	w1= nullptr;
	w2= nullptr;
    }

    void zmienWartosc(K nowa) {wartosc= nowa;}
    K dajWartosc(void) {return wartosc;}

    void zmienW1(mwierzcholek<T, K> *w) {w1= w;}
    void zmienW2(mwierzcholek<T, K> *w) {w2= w;}
    
    mwierzcholek<T, K> *dajW1(void) {return w1;}
    mwierzcholek<T, K> *dajW2(void) {return w2;}
};

/* ----------------------------- */

template <typename T, typename K>
class graf_macierz{
private:
    uint rozmiar, max_krawedzi, liczba_krawedzi, liczba_wierzcholkow, gestosc;
    mwierzcholek<T, K> *wierzcholki;
    mkrawedz<T, K> *krawedzie;
    mkrawedz<T, K> **macierz;

    mkrawedz<T, K> *zMacierzy(uint r, uint k) {return macierz[r*rozmiar + k];}
    
    void doMacierzy(uint r, uint k, mkrawedz<T, K> *elem){
	if(r >= rozmiar || k >= rozmiar || r == k)
	    return;
	macierz[r*rozmiar + k]= elem;
    }
    
public:
    graf_macierz(uint n, uint g){
	rozmiar= n;
	gestosc= g;
	max_krawedzi= (rozmiar*(rozmiar-1))/2;
	liczba_krawedzi= 0;
	liczba_wierzcholkow= 0;
	wierzcholki= new mwierzcholek<T, K>[rozmiar];

	/* Zawsze rezerwujemy wystarczająco dużo pamięci na pełny graf, */
	/* bo tak łatwiej */
	krawedzie= new mkrawedz<T, K>[max_krawedzi];

	
	macierz= new mkrawedz<T, K>*[rozmiar*rozmiar];

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

    mwierzcholek<T, K> *dodajWierzcholek(T wartosc){
	mwierzcholek<T, K> *w= wierzcholki + liczba_wierzcholkow;
	
	if(liczba_wierzcholkow >= rozmiar)
	    return nullptr;

	zmienWartosc(w, wartosc);
	
	liczba_wierzcholkow++;
	
	return w;
    }

    mkrawedz<T, K> *dodajKrawedz(K wartosc, mwierzcholek<T, K> *w1, mwierzcholek<T, K> *w2){
	mkrawedz<T, K> *nowa_krawedz= krawedzie + liczba_krawedzi;
	
	if(liczba_krawedzi >= max_krawedzi)
	    return nullptr;

	nowa_krawedz->zmienWartosc(wartosc);
	nowa_krawedz->zmienW1(w1);
	nowa_krawedz->zmienW2(w2);
	
	doMacierzy(w1->dajKlucz(), w2->dajKlucz(), nowa_krawedz);
	doMacierzy(w2->dajKlucz(), w1->dajKlucz(), nowa_krawedz);
	
	liczba_krawedzi++;

	return nowa_krawedz;
    }

    void zmienWartosc(mwierzcholek<T, K> *w, T nowa) {w->zmienWartosc(nowa);}
    void zmienWartosc(mkrawedz<T, K> *k, K nowa) {k->zmienWartosc(nowa);}
    T dajWartosc(mwierzcholek<T, K> *w) {return w->dajWartosc();}
    K dajWartosc(mkrawedz<T, K> *k) {return k->dajWartosc();}

    /* --- */

    mwierzcholek<T, K> *dajPrzeciwleglyWierzcholek(mwierzcholek<T, K> *w, mkrawedz<T, K> *k){
	mwierzcholek<T, K> *w1, *w2;
	w1= k->dajW1();
	w2= k->dajW2();

	if(w == w1)
	    return w2;
	else if(w == w2)
	    return w1;
	else
	    return nullptr;
    }

    uint dajLiczbeIncydencji(mwierzcholek<T, K> *w){
	uint klucz, licznik;
	mkrawedz<T, K> *k;
	
	licznik=  0;
	klucz= w->dajKlucz();
	
	for(uint i= 0; i < rozmiar; i++){
	    k= zMacierzy(klucz, i);
	    if(k != nullptr)
		licznik++;
	}

	return licznik;
    }

    bool czySasiedzi(mwierzcholek<T, K> *w1, mwierzcholek<T, K> *w2){
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
	    for(uint j= 0; j <= rozmiar-1; j++){
		k= zMacierzy(i, j);
		if(k != nullptr)
		    cout << k->dajWartosc() << "   ";
		    /* cout << "0000   "; */
		    /* cout << k << "    "; */
		else if(i == j)
		    cout << "----   ";
		else
		    cout << "null   ";
	    }
	    cout << '\n';
	}
    }

    void losujMacierz(void){
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

    mwierzcholek<T, K> *dajWierzcholki(void) {return wierzcholki;}
    mwierzcholek<T, K> *dajWierzcholek(uint i) {return wierzcholki+i;}
    
    mkrawedz<T, K> *dajKrawedzie(void) {return krawedzie;}
    mkrawedz<T, K> *dajKrawedz(uint i) {return krawedzie+i;}

    mkrawedz<T, K> *dajKrawedz(uint k1, uint k2) {return zMacierzy(k1, k2);}
        mkrawedz<T, K> *dajKrawedz(mwierzcholek<T, K> *w1, mwierzcholek<T, K> *w2){
	return zMacierzy(w1->dajKlucz(), w2->dajKlucz());
    }

    shared_ptr< lista< mkrawedz<T, K>* > > dajKrawedzie(mwierzcholek<T, K> *w){
	mkrawedz<T, K> *k;
	uint klucz= w->dajKlucz();
	shared_ptr< lista< mkrawedz<T, K>* > > l= make_shared< lista< mkrawedz<T, K>* > >();
	
	for(uint i= 0; i < rozmiar; i++){
	    k= zMacierzy(i, klucz);
	    if(k != nullptr)
		l->dodajOgniwo(k);
	}
	
	return l;
    }
    
    uint dajLiczbeKrawedzi(void) {return liczba_krawedzi;}
    uint dajRozmiar(void) {return rozmiar;}
};

#endif
