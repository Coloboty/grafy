#ifndef PRIM_H
#define PRIM_H

#include <iostream>

using namespace std;

/* template<typename T, typename K> */
template<typename X, typename D>
    shared_ptr< lista<X*> > mPrim(D graf, X krawedz){
/* shared_ptr< lista< mkrawedz<T, K> *> > mPrim(shared_ptr< graf_macierz<T, K> > graf){ */
    /* priority_queue<mkrawedz<T, K>*, vector<mkrawedz<T, K>*>, porownywacz<T, K>> kolejka; */
    /* shared_ptr< lista< mkrawedz<T, K> *> > drzewo= make_shared< lista< mkrawedz<T, K> *> >(); */
    shared_ptr< lista<X*> > drzewo= make_shared< lista<X*> >();
    
    uint licznik, rozmiar, l_krawedzi;

    licznik= 0;
    rozmiar= graf->dajRozmiar();
    l_krawedzi= graf->dajLiczbeKrawedzi();
    
    /* for(uint i= 0; i < l_krawedzi; i++) */
	/* kolejka.push(graf->dajKrawedz(i)); */

    for(uint i= 0; i < l_krawedzi; i++){
	/* std::cout << kolejka.top()->dajWartosc() << '\n'; */
	/* kolejka.pop(); */
    }

    drzewo->dodajOgniwo(graf->dajKrawedz(0));
    return drzewo;
}

#endif
