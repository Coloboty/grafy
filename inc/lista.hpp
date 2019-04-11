#include "lista.h"

#ifndef LISTA_HPP
#define LISTA_HPP

/* METODY KLAS */

template <typename T>
lista<T>::lista(){
    glowa= new(ogniwo<T>);
    ogon= new(ogniwo<T>);

    glowa->zmienPoprzednik(nullptr);
    glowa->zmienNastepnik(ogon);
    ogon->zmienPoprzednik(glowa);
    ogon->zmienNastepnik(nullptr);

    licznik= 0;
}

template <typename T>
lista<T>::~lista(){
    /* cout << "destruktor obiektu lista\n"; */
    while(licznik > 0)
	usunOgniwo(ogon->dajPoprzednik());

    delete(glowa);
    delete(ogon);
}

template <typename T>
void lista<T>::usunOgniwo(ogniwo<T> *ogn){
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

template <typename T>
ogniwo<T> *lista<T>::dodajZa(T wartosc, ogniwo<T> *ogn){
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

template <typename T>
ogniwo<T> *lista<T>::dodajPrzed(T wartosc, ogniwo<T> *ogn){
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

template <typename T>
void lista<T>::dodajHurtowo(T *elementy, uint ile){
    ogniwo <T> *temp= glowa;
    
    for(uint i= 0; i < ile; i++){
	temp= dodajZa(elementy[i], temp);
    }

    return;
}

#endif
