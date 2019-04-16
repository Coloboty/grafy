#include <iostream>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "kruskal.hpp"

using namespace std;

void wypiszElementy(lista<int> &x);

int main(void){
    graf_macierz<int, int> test(5);
    mwierzcholek<int> *w1, *w2, *w3;
    mkrawedz<int, int> *k1, *k2, *k3, *k4;

    w1= test.dodajWierzcholek(21);
    w2= test.dodajWierzcholek(37);
    w3= test.dodajWierzcholek(2137);

    k1= test.dodajKrawedz(13, w1, w2);
    k2= test.dodajKrawedz(11, w2, w3);
    k3= test.dodajKrawedz(12, w1, w3);
    test.dodajKrawedz(17, w1, w2);
    mKruskal(&test);
    
    cout << "Koniec programu!\n";
    return 0;
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
