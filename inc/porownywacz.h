#ifndef POROWNYWACZ_H
#define POROWNYWACZ_H

#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"

template <typename T, typename K>
struct porownywacz{
public:
    bool operator()(mkrawedz<T, K> *a, mkrawedz<T, K> *b){
	return a->dajWartosc() > b->dajWartosc();
    }

    bool operator()(mwierzcholek<T, K> *a, mwierzcholek<T, K> *b){
	return a->dajWartosc() > b->dajWartosc();
    }
};

#endif
