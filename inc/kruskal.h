#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <queue>
#include "grafy_macierz.hpp"

template<typename T, typename K>
void mKruskal(graf_macierz<T, K> *graf){
    /* shared_ptr< lista< mwierzcholek<T>* > > l= make_shared< lista< mwierzcholek<T>* > >(); */
    lista< mwierzcholek<T>* > wierzcholki_grafu;
    priority_queue< mkrawedz<T, K> > krawedzie_grafu;
    /* lista< mkrawedz<T, K>* > krawedzie_grafu; */
    krawedzie_grafu.push(graf->dajKrawedzie()->dajOgniwo(0)->dajWartosc());
    return;
}

#endif
