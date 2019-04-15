#include <iostream>
#include "lista.hpp"

using namespace std;

void wypiszElementy(lista<int> &x);

int main(void){
    lista<int> test;
    int tab[8]= {1, 2, 3, 4, 2, 1, 3, 7};
    /* ogniwo<int> *o; */
    cout << "Początek programu!\n";

    test.dodajHurtowo(tab, 8);
    
    wypiszElementy(test);
    cout << '\n';
    /* cout << test->operator[](2)->dajWartosc() << '\n'; */
    /* o= test[2]; */
    cout << test[6]->dajWartosc() << '\n';

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
