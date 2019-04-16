#ifndef GRAFY_MACIERZ_H
#define GRAFY_MACIERZ_H

template <typename T>
class wierzcholek{
private:
    T wartosc;
    uint klucz;
    ogniwo< wierzcholek<T>* > *miejsce;
    
public:
    wierzcholek(T w) {wartosc= w;}
        
    void zmienMiejsce(ogniwo< wierzcholek<T>* > *moje) {miejsce= moje;}
    void zmienWartosc(T nowa) {wartosc= nowa;}
    void zmienKlucz(uint k) {klucz= k;}
    
    T dajWartosc(void) {return wartosc;}
    ogniwo< wierzcholek<T>* > *dajMiejsce(void) {return miejsce;}
    uint dajKlucz(void) {return klucz;}
};

/* ----------------------------- */

template <typename T, typename K>
class krawedz{
private:
    K wartosc;
    ogniwo< krawedz<T, K>* > *miejsce;
    wierzcholek<T, K> *w1, *w2;

public:
    krawedz(K w, wierzcholek<T> *w_1, wierzcholek<T> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

};

/* ----------------------------- */

template <typename T, typename K>
class graf_macierz{
private:
    uint rozmiar;
    lista< wierzcholek<T>* > *wierzcholki;
    lista< krawedz<T, K>* > *krawedzie;
    krawedz<T, K> **macierz;
    
public:
    graf_macierz(uint n){
	wierzcholki= new lista< wierzcholek<T>* >;
	krawedzie= new lista< krawedz<T, K>* >;
	macierz= new krawedz<T, K>[n*n];
	rozmiar= n;
    }

    ~graf_macierz(){
	delete wierzcholki;
	delete krawedzie;
    }

};

#endif
