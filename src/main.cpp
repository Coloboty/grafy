#include <iostream>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"

using namespace std;

void wypiszElementy(lista<int> &x);

int main(void){
    /* graf_lista<int, int> test; */
    /* graf_macierz<int, int> test; */
    /* wierzcholek<int, int> *w1, *w2, *w3; */
    /* krawedz<int, int> *k1, *k2; */
    
    /*
    w1= test.dodajWierzcholek(21);
    w2= test.dodajWierzcholek(37);
    w3= test.dodajWierzcholek(911);
    k1= test.dodajKrawedz(2137, w1, w2);
    k2= test.dodajKrawedz(2138, w2, w3);

    //test.usunWierzcholek(w3);
    cout << test.czySasiedzi(w2, w3) << '\n';
    test.usunKrawedz(k2);
    cout << test.czySasiedzi(w2, w3) << '\n';
    */
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
