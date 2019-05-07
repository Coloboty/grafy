#ifndef PRIM_H
#define PRIM_H

#include <iostream>

using namespace std;

template<typename T, typename K>
using drzewo= lista< krawedz<T, K>* >;

template<typename T, typename K, typename G>
void prim(G graf, shared_ptr< drzewo<T, K> > mst){
    uint rozmiar, l_krawedzi;
    T *stare_wartosci;
    wierzcholek<T, K> *w1, *w2;
    krawedz<T, K> *k;
    krawedz<T, K> **krawedzie;
    shared_ptr< lista< krawedz<T, K>* > > incydencje;
    vector< wierzcholek<T, K>* > kolejka;

    /* Otrzymany wskaźnik musi wskazywać na konkretną listę */
    if(!mst)
	return;

    /* Podana lista musi być pusta */
    if(mst->dajRozmiar() > 0)
	return;
    
    /* Inicjalizuj używane zmienne */
    rozmiar= graf->dajRozmiar();
    krawedzie= new krawedz<T, K>*[rozmiar];
    for(uint i= 0; i < rozmiar; i++)
	krawedzie[i]= nullptr;
    
    /* Zachowaj oryginalne wartości wierzchołków grafu na potem, */
    /* inicjalizuj je wszystkie jakąś liczbą, wrzuć do kolejki */
    stare_wartosci= new T[rozmiar];
    for(uint i= 0; i < rozmiar; i++){
	stare_wartosci[i]= graf->dajWierzcholek(i)->dajWartosc();
    	graf->dajWierzcholek(i)->zmienWartosc(2000);
    	kolejka.push_back(graf->dajWierzcholek(i));
    }
        
    /* Zmień wartość któregoś węzła, żeby był wzięty jako pierwszy */
    graf->dajWierzcholek(0)->zmienWartosc(2);
    /* Utwórz strukturę kolejki/kopca */
    make_heap(kolejka.begin(), kolejka.end(), porownywacz<T, K>());
    
    while(kolejka.size() > 0){
	/* Weź wierzchołek o najniższym koszcie dotarcia */
	w1= kolejka.front();
	pop_heap(kolejka.begin(), kolejka.end(), porownywacz<T, K>());
	kolejka.pop_back();

	/* Dodaj odpowiadającą mu krawędź do drzewa */
	mst->dodajOgniwo(krawedzie[w1->dajKlucz()]);

	/* Weź listę wszystkich jego krawędzi */
	incydencje= graf->dajKrawedzie(w1);
	l_krawedzi= incydencje->dajRozmiar();

	cout << "wzięto " << w1->dajKlucz() << '\n';

	/* Dla każdej krawędzi do niego przylegającej: */
	for(uint i= 0; i < l_krawedzi; i++){
	    k= incydencje->dajOgniwo(i)->dajWartosc();

	    /* Znajdź wierzchołek po drugiej stronie */
	    w2= graf->dajPrzeciwleglyWierzcholek(w1, k);
	    
	    /* Zaktualizuj koszt dotarcia do niego, jeśli jest mniejszy niż z innego wierzchołka */
	    /* i zapisz odpowiadającą tej ścieżce krawędź */
	    if(w2->dajWartosc() > k->dajWartosc()){
		w2->zmienWartosc(k->dajWartosc());
		krawedzie[w2->dajKlucz()]= k;
		cout << "zaktualizowano " << w2->dajKlucz() << " do " << w2->dajWartosc() << '\n';
	    }
	}

	/* Ponownie uporządkuj wierzchołki weług kosztu */
	make_heap(kolejka.begin(), kolejka.end(), porownywacz<T, K>());
    }

    /* Usuń pierwszą dodaną krawędź */
    mst->usunOgniwo(mst->dajOstatnie());

    /* Przywróć wierzchołkom ich początkowe wartości */
    for(uint i= 0; i < rozmiar; i++)
	graf->dajWierzcholek(i)->zmienWartosc(stare_wartosci[i]);
    
    delete[] krawedzie;
}

#endif
