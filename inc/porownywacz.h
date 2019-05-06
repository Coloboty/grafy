#ifndef POROWNYWACZ_H
#define POROWNYWACZ_H

#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"

template <typename T, typename K>
struct porownywacz{
public:
    bool operator()(krawedz<T, K> *a, krawedz<T, K> *b){
	return a->dajWartosc() > b->dajWartosc();
    }

    bool operator()(wierzcholek<T, K> *a, wierzcholek<T, K> *b){
	return a->dajWartosc() > b->dajWartosc();
    }
};

#endif
