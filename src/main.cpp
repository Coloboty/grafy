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

    test= make_shared< graf_macierz<int, int> >(rozmiar);
    test= losowyGraf(rozmiar, 20);
    
    cout << "graf ma " << test->dajWierzcholki()->dajRozmiar() << " wierzcholkow i " <<
	test->dajKrawedzie()->dajRozmiar() << " krawedzi.\n";

    for(uint i= 0; i < rozmiar; i++){
	w= test->dajWierzcholki()->dajOgniwo(i)->dajWartosc();
	cout << "wierzcholek " << i << " ma " <<
	    test->dajIncydentneKrawedzie(w)->dajRozmiar() <<
	    " krawedzi\n";
    }

    test->drukujMacierz();
    cout << '\n';
    cout << test->dajWierzcholki()->dajOgniwo(1)->dajWartosc()->dajKlucz() << '\n';
    
    /* test->usunWierzcholek(test->dajWierzcholki()->dajOgniwo(1)->dajWartosc()); */
    /* cout << "\n\n\n\n"; */
    /* test->drukujMacierz(); */
    
/* mKruskal(test); */
    
    cout << "Koniec programu!\n";
    return 0;
}

shared_ptr< graf_macierz<int, int> > losowyGraf(uint rozmiar, uint gestosc){
    shared_ptr< graf_macierz<int, int> > graf= make_shared< graf_macierz<int, int> >(rozmiar);
    mwierzcholek<int> *obecny, *poprzedni;
    mkrawedz<int, int> *krawedz;
    shared_ptr< lista< mkrawedz<int, int>* > > lista;
    uint max_krawedzi= (rozmiar*(rozmiar-1))/2;
    uint cel_krawedzi= (gestosc*max_krawedzi)/100;
    /* Nie ma sensu generować grafów mniejszych niż 10 */
    /* if(rozmiar < 10) */
	/* return nullptr; */
    
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

    cout << "Stworzono wierzcholki\n";
    cout << "Maksymalna liczba krawedzi to " << max_krawedzi << '\n';
    cout << "Stworzono wierzcholki\n";

    /* Zrób z nich graf zupełny */
    for(uint i= 0; graf->dajKrawedzie()->dajRozmiar() < max_krawedzi; i++){
	poprzedni= graf->dajWierzcholki()->dajOgniwo(i)->dajWartosc();
	for(uint j= i+1; j <= rozmiar-1; j++){
	    obecny= graf->dajWierzcholki()->dajOgniwo(j)->dajWartosc();
	    graf->dodajKrawedz((rand() % 1000)+1000, poprzedni, obecny);
	}
    }

    cout << "Stworzono graf zupełny\n";
    cout << "Docelowo ma być " << cel_krawedzi << " krawędzi\n";

    while(graf->dajKrawedzie()->dajRozmiar() > cel_krawedzi){
	obecny= graf->dajWierzcholki()->dajOgniwo(rand()%(rozmiar-1))->dajWartosc();
	lista= graf->dajIncydentneKrawedzie(obecny);
	/* graf->dajIncydentneKrawedzie(obecny)->dajRozmiar(); */
	if(lista->dajRozmiar() > 1){
	    krawedz= lista->dajOgniwo(rand()%(lista->dajRozmiar()-1))->dajWartosc();
	    poprzedni= graf->dajPrzeciwleglyWierzcholek(obecny, krawedz);
	    if(graf->dajIncydentneKrawedzie(poprzedni)->dajRozmiar() > 1)
		graf->usunKrawedz(krawedz);
	}
	
	/* if(i >= rozmiar) */
	    /* i= 0; */
    }

    cout << "Usunięto krawędzie\n";
    
    

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
