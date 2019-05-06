#ifndef GRAFY_KLASY_H
#define GRAFY_KLASY_H

template <typename T, typename K>
class wierzcholek{
private:
    T wartosc;
    uint klucz;
            
public:
    wierzcholek(T w, uint k){
	wartosc= w;
	klucz= k;
    }

    wierzcholek(){
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
class krawedz{
private:
    K wartosc;
    wierzcholek<T, K> *w1, *w2;

public:
    krawedz(K w, wierzcholek<T, K> *w_1, wierzcholek<T, K> *w_2){
	wartosc= w;
	w1= w_1;
	w2= w_2;
    }

    krawedz(){
	wartosc= 0;
	w1= nullptr;
	w2= nullptr;
    }

    void zmienWartosc(K nowa) {wartosc= nowa;}
    K dajWartosc(void) {return wartosc;}

    void zmienW1(wierzcholek<T, K> *w) {w1= w;}
    wierzcholek<T, K> *dajW1(void) {return w1;}
    void zmienW2(wierzcholek<T, K> *w) {w2= w;}
    wierzcholek<T, K> *dajW2(void) {return w2;}
};

#endif
