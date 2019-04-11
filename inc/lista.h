#ifndef LISTA_H
#define LISTA_H

#include <iostream>
typedef unsigned int uint;
using namespace std;

/* DEKLARACJE/DEFINICJE KLAS */

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

template <typename T>
class lista{
private:
    ogniwo<T> *glowa, *ogon;
    uint licznik;

public:
    lista(){
	glowa= new(ogniwo<T>);
	ogon= new(ogniwo<T>);

	glowa->zmienPoprzednik(nullptr);
	glowa->zmienNastepnik(ogon);
	ogon->zmienPoprzednik(glowa);
	ogon->zmienNastepnik(nullptr);

	licznik= 0;
    }

    ~lista(){
	/* cout << "destruktor obiektu lista\n"; */
	while(licznik > 0)
	    usunOgniwo(ogon->dajPoprzednik());

	delete(glowa);
	delete(ogon);
    }

    ogniwo<T> *dajGlowe(void) {return glowa;}
    ogniwo<T> *dajOgon(void) {return ogon;}

    void usunOgniwo(ogniwo<T> *ogn){
	ogniwo<T> *przed, *za;

	if(ogn == nullptr || licznik == 0)
	    return;

	/* cout << "usuwam ogniwo o wartosci " << ogn->dajWartosc() << '\n'; */
	
	przed= ogn->dajNastepnik();
	za= ogn->dajPoprzednik();

	przed->zmienPoprzednik(za);
	za->zmienNastepnik(przed);
	delete(ogn);
	licznik--;
    }
    
    ogniwo<T> *dodajZa(T wartosc, ogniwo<T> *ogn){
	ogniwo<T> *temp= new(ogniwo<T>);
	ogniwo<T> *przed_nowym= ogn->dajNastepnik();
	
	temp->zmienWartosc(wartosc);
	temp->zmienNastepnik(przed_nowym);
	temp->zmienPoprzednik(ogn);
	ogn->zmienNastepnik(temp);
        przed_nowym->zmienPoprzednik(temp);

	licznik++;
	return temp;
    }

    ogniwo<T> *dodajPrzed(T wartosc, ogniwo<T> *ogn){
	ogniwo<T> *temp= new(ogniwo<T>);
	ogniwo<T> *za_nowym= ogn->dajPoprzednik();
	
	temp->zmienWartosc(wartosc);
	temp->zmienNastepnik(ogn);
	temp->zmienPoprzednik(za_nowym);
	ogn->zmienPoprzednik(temp);
        za_nowym->zmienNastepnik(temp);

	licznik++;
	return temp;
    }
};

/* DEKLARACJE/DEFINICJE FUNKCJI */

template <typename T>
void zapelnijListe(lista<T> *l, T *elementy, uint ile){
    ogniwo <T> *temp= l->dajGlowe();
    
    for(uint i= 0; i < ile; i++){
	temp= l->dodajZa(elementy[i], temp);
    }

    return;
}
#endif
