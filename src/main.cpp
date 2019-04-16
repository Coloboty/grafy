#include <iostream>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"

using namespace std;

void wypiszElementy(lista<int> &x);

int main(void){
    graf_macierz<int, int> test(5);
    
    mwierzcholek<int> *w1, *w2, *w3;
    mkrawedz<int, int> *k1, *k2;
    lista < mwierzcholek<int>* > *l;
    
    w1= test.dodajWierzcholek(21);
    w2= test.dodajWierzcholek(37);
    w3= test.dodajWierzcholek(911);
    k1= test.dodajKrawedz(2137, w1, w2);
    k2= test.dodajKrawedz(2138, w2, w3);

    /* cout << test.dajKoncowyWierzcholek1(k1)->dajWartosc() << '\n'; */
    /* cout << test.dajKoncowyWierzcholek2(k1)->dajWartosc() << '\n'; */
    cout << test.czySasiedzi(w1, w2) << '\n';
    cout << test.czySasiedzi(w2, w3) << '\n';
    cout << test.czySasiedzi(w1, w3) << '\n';
    cout << '\n';

    l= test.dajWierzcholki();
    cout << (*l)[0]->dajWartosc()->dajWartosc() << '\n';
    cout << (*l)[1]->dajWartosc()->dajWartosc() << '\n';
    cout << (*l)[2]->dajWartosc()->dajWartosc() << '\n';
    
    
    /* cout << '\n'; */
    /* test.drukujMacierz(); */
    
    
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
