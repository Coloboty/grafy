#ifndef LISTA_H
#define LISTA_H

#include <iostream>
typedef unsigned int uint;
using namespace std;

/* Definicja/deklaracja klasy ogniwo */
template <typename T>
class ogniwo{
private:
    ogniwo *poprzedni, *nastepny;
    T wartosc;
    
public:
    void zmienWartosc(T nowa) {wartosc= nowa;}
    void zmienPoprzednik(ogniwo *n_poprzednik) {poprzedni= n_poprzednik;}
    void zmienNastepnik(ogniwo *n_nastepnik) {nastepny= n_nastepnik;}

    ogniwo *dajNastepnik(void) {return nastepny;}
    ogniwo *dajPoprzednik(void) {return poprzedni;}
    T dajWartosc(void) {return wartosc;}
};

/* Definicja klasy lista */
template <typename T>
class lista{
private:
    ogniwo<T> *glowa, *ogon;
    uint licznik;

public:
    lista();
    ~lista();
    
    ogniwo<T> *dajGlowe(void) {return glowa;}
    ogniwo<T> *dajOgon(void) {return ogon;}
    uint dajRozmiar(void) {return licznik;};
    
    ogniwo<T> *dajOstatnie(void){
	if(licznik) return ogon->dajPoprzednik();
	else return ogon;
    }
    
    ogniwo<T> *dajPierwsze(void){
	if(licznik) return glowa->dajNastepnik();
	else return glowa;
    }

    ogniwo<T> *dodajOgniwo(T wartosc){
	if(licznik == 0)
	    return dodajZa(wartosc, dajPierwsze());
	else
	    return dodajPrzed(wartosc, dajPierwsze());
    }
    
    ogniwo<T> *operator[](uint ind);
    ogniwo<T> *dajOgniwo(uint ind);

    void czyscListe(void){
	while(licznik)
	    usunOgniwo(dajOstatnie());
    }
    
    void usunOgniwo(ogniwo<T> *ogn);
    ogniwo<T> *dodajZa(T wartosc, ogniwo<T> *ogn);
    ogniwo<T> *dodajPrzed(T wartosc, ogniwo<T> *ogn);
    void dodajHurtowo(T*, uint);
};

/* DEKLARACJE/DEFINICJE FUNKCJI */

#endif
