#ifndef GRAFY_MACIERZ_HPP
#define GRAFY_MACIERZ_HPP

#include "grafy_macierz.h"

template<typename T, typename K>
wierzcholek<T, K> *graf_macierz<T, K>::dodajWierzcholek(T wartosc){
    wierzcholek<T, K> *w= wierzcholki + l_wierzcholkow;
	
    if(l_wierzcholkow >= rozmiar)
	return nullptr;

    zmienWartosc(w, wartosc);
	
    l_wierzcholkow++;
	
    return w;
}

template<typename T, typename K>
krawedz<T, K> *graf_macierz<T, K>::dodajKrawedz(K wartosc, wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
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

template<typename T, typename K>
wierzcholek<T, K> *graf_macierz<T, K>::dajPrzeciwleglyWierzcholek(wierzcholek<T, K> *w, krawedz<T, K> *k){
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

template<typename T, typename K>
uint graf_macierz<T, K>::dajLiczbeIncydencji(wierzcholek<T, K> *w){
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

template<typename T, typename K>
uint graf_macierz<T, K>::dajLiczbeIncydencji(uint klucz){
    uint licznik;
    krawedz<T, K> *k;
	
    licznik=  0;
    	
    for(uint i= 0; i < rozmiar; i++){
	k= zMacierzy(klucz, i);
	if(k != nullptr)
	    licznik++;
    }

    return licznik;
}

template<typename T, typename K>
bool graf_macierz<T, K>::czySasiedzi(wierzcholek<T, K> *w1, wierzcholek<T, K> *w2){
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

template<typename T, typename K>
bool graf_macierz<T, K>::czySasiedzi(uint k1, uint k2){
    
    krawedz<T, K> *k;

    k= zMacierzy(k1, k2);
    if(k != nullptr)
	return true;
    else
	return false;
}

template<typename T, typename K>
void graf_macierz<T, K>::drukujMacierz(void){
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

template<typename T, typename K>
void graf_macierz<T, K>::losujMacierz(uint gestosc){
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

template<typename T, typename K>
shared_ptr< lista< krawedz<T, K>* > > graf_macierz<T, K>::dajKrawedzie(wierzcholek<T, K> *w){
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

template<typename T, typename K>
shared_ptr< lista< krawedz<T, K>* > > graf_macierz<T, K>::dajKrawedzie(uint klucz){
    krawedz<T, K> *k;
    shared_ptr< lista< krawedz<T, K>* > > l= make_shared< lista< krawedz<T, K>* > >();
	
    for(uint i= 0; i < rozmiar; i++){
	k= zMacierzy(i, klucz);
	if(k != nullptr)
	    l->dodajOgniwo(k);
    }
	
    return l;
}

#endif
