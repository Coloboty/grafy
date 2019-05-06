#include <iostream>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"

using namespace std;

void wypiszElementy(lista<int> &x);

int main(void){
    shared_ptr< graf_lista<int, int> > test;
    uint rozmiar;
    lwierzcholek<int, int> *w1, *w2, *w3;
    lkrawedz<int, int> *k1, *k2;

    rozmiar= 10;
    test= make_shared< graf_lista<int, int> >(rozmiar);
    
    w1= test->dodajWierzcholek(21);
    w2= test->dodajWierzcholek(37);
    w3= test->dodajWierzcholek(911);
    k1= test->dodajKrawedz(2137, w1, w2);
    k2= test->dodajKrawedz(2138, w2, w3);

    
    
    cout << "Koniec programu!\n";
    return 0;
}
