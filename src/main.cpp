#include <iostream>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "kruskal.hpp"

using namespace std;

void wypiszElementy(lista<int> &x);
shared_ptr< graf_macierz<int, int> > losowyGraf(uint rozmiar, uint gestosc);

int main(void){
    shared_ptr< graf_macierz<int, int> > test;
    mwierzcholek<int> *w;
    uint rozmiar= 10;

    /*
    test= make_shared< graf_macierz<int, int> >(10);
   
    w= test->dodajWierzcholek(2137);
    test->dodajKrawedz(10, test->dodajWierzcholek(21), w);
    test->dodajKrawedz(10, test->dodajWierzcholek(37), w);
    test->dodajKrawedz(10,
		       test->dajWierzcholki()->dajOgniwo(1)->dajWartosc(),
		       test->dajWierzcholki()->dajOgniwo(2)->dajWartosc());
    */
    test= losowyGraf(rozmiar, 20);
    cout << "graf ma " << test->dajWierzcholki()->dajRozmiar() << " wierzcholkow i " <<
	test->dajKrawedzie()->dajRozmiar() << " krawedzi.\n";

    for(uint i= 0; i < rozmiar; i++){
	w= test->dajWierzcholki()->dajOgniwo(i)->dajWartosc();
	cout << "wierzcholek " << i << " ma " <<
	    test->dajIncydentneKrawedzie(w)->dajRozmiar() <<
	    " krawedzi\n";
    }
    /* mKruskal(test); */
    
    cout << "Koniec programu!\n";
    return 0;
}

shared_ptr< graf_macierz<int, int> > losowyGraf(uint rozmiar, uint gestosc){
    shared_ptr< graf_macierz<int, int> > graf= make_shared< graf_macierz<int, int> >(rozmiar);
    mwierzcholek<int> *obecny, *poprzedni;
    uint max_krawedzi= (rozmiar*(rozmiar-1))/2;
    /* uint cel_krawedzi= (gestosc*max_krawedzi)/100; */
    /* Nie ma sensu generować grafów mniejszych niż 10 */
    if(rozmiar < 10)
	return nullptr;
    
    /* Minimalna gęstość grafu spójnego to (2/n) */
    if(gestosc < (2*100)/rozmiar)
	return nullptr;

    srand( time(NULL) );

    /* Stwórz wszystkie wierzchołki */
    for(uint i= 0; i < rozmiar; i++){
        graf->dodajWierzcholek(rand() % 1000);
	/* poprzedni= graf->dodajWierzcholek(rand() % 1000); */
        /* obecny= graf->dodajWierzcholek(rand() % 1000); */
	/* graf->dodajKrawedz(rand() % 1000, poprzedni, obecny); */
    }

    /* Zrób z nich graf zupełny */
    for(uint i= 0; graf->dajKrawedzie()->dajRozmiar() < max_krawedzi; i++){
	poprzedni= graf->dajWierzcholki()->dajOgniwo(i)->dajWartosc();
	for(uint j= i+1; j <= rozmiar-1; j++){
	    obecny= graf->dajWierzcholki()->dajOgniwo(i+1)->dajWartosc();
	    graf->dodajKrawedz(rand() % 1000, poprzedni, obecny);
	}
    }
    

    /* cout << "funkcja sie wykonala\n"; */
    return graf;
}

void wypiszElementy(lista<int> &x){
    ogniwo<int> *leb, *ogon;
    leb= x.dajGlowe();
    ogon= x.dajOgon();
    ogon= ogon->dajPoprzednik();

    while(leb != ogon){
	leb= leb->dajNastepnik();
	cout << leb->dajWartosc() << '\n';
    }
}
