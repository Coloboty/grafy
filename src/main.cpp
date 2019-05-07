#include <iostream>
#include <chrono>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "funkcje_pomocnicze.hpp"
#include "kruskal.hpp"
#include "prim.hpp"

using namespace std;

template<typename G>
void testowyGraf(G graf){
    graf->dodajKrawedz(3, 0, 1);
    graf->dodajKrawedz(4, 0, 5);
    graf->dodajKrawedz(7, 1, 6);
    graf->dodajKrawedz(2, 1, 2);
    graf->dodajKrawedz(3, 2, 3);
    graf->dodajKrawedz(8, 2, 6);
    graf->dodajKrawedz(5, 3, 6);
    graf->dodajKrawedz(12, 6, 5);
    graf->dodajKrawedz(11, 6, 4);

    graf->dodajKrawedz(10, 0, 6);
}

template<typename T, typename K, typename G>
void wypisz(G graf, shared_ptr< drzewo<T, K> > d ){
    shared_ptr< lista< krawedz<T, K>* > > in;
    uint r, rr;

    rr= graf->dajRozmiar();
    for(uint i= 0; i < rr; i++){
	in= graf->dajKrawedzie(i);
	r= in->dajRozmiar();
	cout << "\nkrawędzie przyległe do w" << i << '\n';
	for(uint j= 0; j < r; j++){
	    cout << in->dajOgniwo(j)->dajWartosc()->dajW1()->dajKlucz() << " --- " << in->dajOgniwo(j)->dajWartosc()->dajW2()->dajKlucz() << '\n';
	}
	cout << '\n';
    }
}

void testujRecznie(void){
    shared_ptr< graf_lista<int, int> > lgraf, lrek;
    shared_ptr< graf_macierz<int, int> > mgraf, mrek;
    shared_ptr<drzewo<int, int>> mst;
    uint wybor;
    uint rozmiar, gestosc;
    czas start, stop;

    mst= make_shared< drzewo<int, int> >();

    cout << '\n';
    cout << "Wybierz wielkość grafu:" << '\n';
    cout << "1: 50" << '\n';
    cout << "2: 100" << '\n';
    cout << "3: 250" << '\n';
    cout << "4: 500" << '\n';
    cout << "5: 1000" << '\n';
    cout << "Wybór: ";
    cin >> wybor;

    switch(wybor){
    case 1:
	rozmiar= 50;
	break;
    case 2:
	rozmiar= 100;
	break;
    case 3:
	rozmiar= 250;
	break;
    case 4:
	rozmiar= 500;
	break;
    case 5:
	rozmiar= 1000;
	break;

    default:
	cout << "Nie rozumiem!" << '\n';
	return;
	break;
    }
    
    cout << '\n';
    cout << "Wybierz gęstość grafu:" << '\n';
    cout << "1: 25%" << '\n';
    cout << "2: 50%" << '\n';
    cout << "3: 75%" << '\n';
    cout << "4: 100%" << '\n';
    cout << "Wybór: ";
    cin >> wybor;

    switch(wybor){
    case 1:
	gestosc= 25;
	break;
    case 2:
	gestosc= 50;
	break;
    case 3:
	gestosc= 75;
	break;
    case 4:
	gestosc= 100;
	break;

    default:
	cout << "Nie rozumiem!" << '\n';
	return;
	break;
    }
    
    cout << '\n';
    cout << "Wybierz rodzaj reprezentacji grafu:" << '\n';
    cout << "1: Macierz sąsiedztwa" << '\n';
    cout << "2: Lista sąsiedztwa" << '\n';
    cout << "Wybór: ";
    cin >> wybor;
    
    switch(wybor){
    case 1:
	mgraf= make_shared< graf_macierz<int, int> >(rozmiar);
	mrek= make_shared< graf_macierz<int, int> >(rozmiar);
	mgraf->losujGraf(gestosc);
	break;
    case 2:
	lgraf= make_shared< graf_lista<int, int> >(rozmiar);
	lrek= make_shared< graf_lista<int, int> >(rozmiar);
	lgraf->losujGraf(gestosc);
	break;

    default:
	cout << "Nie rozumiem!" << '\n';
	return;
	break;
    }

    cout << '\n';
    cout << "Wybierz algorytm wyznaczania drzewa:" << '\n';
    cout << "1: Algorytm Kruskala" << '\n';
    cout << "2: Algorytm Prima" << '\n';
    cout << "Wybór: ";
    cin >> wybor;
    
    switch(wybor){
    case 1:
	if(mgraf == nullptr){
	    start= zegar::now();
	    kruskal(lgraf, mst);
	    stop= zegar::now();
	    rekonstruujGraf(lrek, lgraf, mst);
	}
	else{
	    start= zegar::now();
	    kruskal(mgraf, mst);
	    stop= zegar::now();
	    rekonstruujGraf(mrek, mgraf, mst);
	}

	cout << "Wykonano alg. Kruskala w " << obliczCzas(start, stop, 'm') << " ms\n";
	break;
    case 2:
	if(mgraf == nullptr){
	    start= zegar::now();
	    prim(lgraf, mst);
	    stop= zegar::now();
	    rekonstruujGraf(lrek, lgraf, mst);
	}
	else{
	    start= zegar::now();
	    prim(mgraf, mst);
	    stop= zegar::now();
	    rekonstruujGraf(mrek, mgraf, mst);
	}

	cout << "Wykonano alg. Prima w " << obliczCzas(start, stop, 'm') << " ms\n";
	break;

    default:
	cout << "Nie rozumiem!" << '\n';
	return;
	break;
    }
    
    cout << "dla grafu o wielkości " << rozmiar << " i " << ((rozmiar*(rozmiar-1))/2)*100/gestosc << " krawedziach\n";
}

int main(void){
    czas start, stop;
    uint wybor;

    cout << "Wybierz opcje:" << '\n';
    cout << "1: Testowanie ręczne" << '\n';
    cout << "2: Testowanie automatyczne" << '\n';
    cout << "Wybór: ";
    cin >> wybor;

    switch(wybor){
    case 1:
	cout << "Wybrano test. ręczne" << '\n';
	cout << '\n';
	testujRecznie();
	break;
    case 2:
	cout << "Wybrano test. automatyczne" << '\n';
	cout << '\n';
	break;

    default:
	cout << "Nie rozumiem!" << '\n';
	return 0;
	break;
    }
    
    
    cout << "Koniec programu!\n";
    
    return 0;
}
