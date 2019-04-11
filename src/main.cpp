#include <iostream>
#include "lista.h"

using namespace std;

void wypiszElementy(lista<int> x);

int main(void){
    lista<int> test;

    cout << "Początek programu!\n";

    test.dodajZa(12, test.dajGlowe());
    test.dodajPrzed(13, test.dajOgon());
    test.dodajPrzed(14, test.dajOgon());
    test.dodajPrzed(21, test.dajOgon());
    test.dodajPrzed(37, test.dajOgon());
    
    
    wypiszElementy(test);

    cout << "Koniec programu!\n";
    return 0;
}

void wypiszElementy(lista<int> x){
    ogniwo<int> *leb, *ogon;
    leb= x.dajGlowe();
    ogon= x.dajOgon();
    ogon= ogon->dajPoprzednik();

    while(leb != ogon){
	leb= leb->dajNastepnik();
	cout << leb->dajWartosc() << '\n';
    }
}
