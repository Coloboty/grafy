

#ifndef LISTA_H
#define LISTA_H

typedef unsigned int uint;

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

    ogniwo<T> *dajGlowe(void) {return glowa;}
    ogniwo<T> *dajOgon(void) {return ogon;}

    void dodajZa(T wartosc, ogniwo<T> *ogn){
	ogniwo<T> *temp= new(ogniwo<T>);
	ogniwo<T> *przed_nowym= ogn->dajNastepnik();
	
	temp->zmienWartosc(wartosc);
	temp->zmienNastepnik(przed_nowym);
	temp->zmienPoprzednik(ogn);
	ogn->zmienNastepnik(temp);
        przed_nowym->zmienPoprzednik(temp);
    }

    void dodajPrzed(T wartosc, ogniwo<T> *ogn){
	ogniwo<T> *temp= new(ogniwo<T>);
	ogniwo<T> *za_nowym= ogn->dajPoprzednik();
	
	temp->zmienWartosc(wartosc);
	temp->zmienNastepnik(ogn);
	temp->zmienPoprzednik(za_nowym);
	ogn->zmienPoprzednik(temp);
        za_nowym->zmienNastepnik(temp);
    }
};

#endif
