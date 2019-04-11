#include <iostream>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"

using namespace std;

void wypiszElementy(lista<int> *x);

int main(void){
    graf_lista<int, int> *test= new(graf_lista<int, int>);
    ogniwo< wierzcholek<int>* > *w1, *w2;
    ogniwo< krawedz<int, int>* > *k1;
    
    w1= test->dodajWierzcholek(21);
    w2= test->dodajWierzcholek(37);
    k1= test->dodajKrawedz(2137, w1, w2);

    cout << test->dajWartosc(w1) << '\n';
    cout << test->dajWartosc(w2) << '\n';
    cout << test->dajWartosc(k1) << '\n';
    
    
    delete(test);
    cout << "Koniec programu!\n";
    return 0;
}

void wypiszElementy(lista<int> *x){
    ogniwo<int> *leb, *ogon;
    leb= x->dajGlowe();
    ogon= x->dajOgon();
    ogon= ogon->dajPoprzednik();

    while(leb != ogon){
	leb= leb->dajNastepnik();
	cout << leb->dajWartosc() << '\n';
    }
}
