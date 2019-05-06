#ifndef PRIM_H
#define PRIM_H

#include <iostream>

using namespace std;

template<typename T, typename K>
using drzewo= lista< krawedz<T, K>* >;

/* template<typename T, typename K> */
template<typename T, typename K, typename G>
void prim(G graf, shared_ptr< drzewo<T, K> > mst){
    uint licznik, rozmiar, l_krawedzi;
    priority_queue< krawedz<T, K>*, vector<krawedz<T, K>*>, porownywacz<T, K> > kolejka;
    
    if(!mst)
	return;
    

    licznik= 0;
    rozmiar= graf->dajRozmiar();
    l_krawedzi= graf->dajLiczbeKrawedzi();
    
    for(uint i= 0; i < l_krawedzi; i++)
	kolejka.push(graf->dajKrawedz(i));

    for(uint i= 0; i < l_krawedzi; i++){
	std::cout << kolejka.top()->dajWartosc() << '\n';
	kolejka.pop();
    }

    /* mst->dodajOgniwo(graf->dajKrawedz(0)); */
}

#endif
