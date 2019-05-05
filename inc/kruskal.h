#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <queue>
#include "grafy_macierz.hpp"
#include "porownywacz.h"

template<typename T, typename K>
void mKruskal(graf_macierz<T, K> *graf){
    /* shared_ptr< lista< mwierzcholek<T>* > > l= make_shared< lista< mwierzcholek<T>* > >(); */
    lista< mwierzcholek<T, K>* > wierzcholki_grafu;
    lista< mkrawedz<T, K>* > *krawedzie_grafu;
    priority_queue<mkrawedz<int, int>*, vector<mkrawedz<int, int>*>, porownywacz<int, int>> kolejka;

    krawedzie_grafu= graf->dajKrawedzie();

    for(uint i= 0; i < krawedzie_grafu->dajRozmiar(); i++)
	kolejka.push(krawedzie_grafu->dajOgniwo(i)->dajWartosc());

    while(!kolejka.empty()){
	std::cout << kolejka.top()->dajWartosc() << '\n';
	kolejka.pop();
    }
    return;
}

#endif
