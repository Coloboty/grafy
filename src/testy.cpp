#include <iostream>
#include <fstream>
#include <chrono>
#include "lista.hpp"
#include "grafy_lista.hpp"
#include "grafy_macierz.hpp"
#include "funkcje_pomocnicze.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include "testy.h"

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

template<typename G>
uint testK(G graf, uint gestosc){
    shared_ptr<drzewo<int, int>> mst;
    czas start, stop;
    uint czas_sredni= 0;
    const uint powtorzenia= POWTORZENIA;

    mst= make_shared< drzewo<int, int> >();
    for(uint i= 0; i < powtorzenia; i++){
	graf->losujGraf(gestosc);
	
	start= zegar::now();
	kruskal(graf, mst);
	stop= zegar::now();
	czas_sredni+= obliczCzas(start, stop, 'u');

	graf->czyscGraf();
	mst->czyscListe();
    }

    return czas_sredni/powtorzenia;
}

template<typename G>
uint testP(G graf, uint gestosc){
    shared_ptr<drzewo<int, int>> mst;
    czas start, stop;
    uint czas_sredni= 0;
    const uint powtorzenia= POWTORZENIA;

    mst= make_shared< drzewo<int, int> >();
    for(uint i= 0; i < powtorzenia; i++){
	graf->losujGraf(gestosc);
	
	start= zegar::now();
	prim(graf, mst);
	stop= zegar::now();
	czas_sredni+= obliczCzas(start, stop, 'u');

	graf->czyscGraf();
	mst->czyscListe();
    }

    return czas_sredni/powtorzenia;
}

void testujAutomatycznie(void){
    shared_ptr< graf_lista<int, int> > lgraf, lrek;
    shared_ptr< graf_macierz<int, int> > mgraf, mrek;
    uint czas;
    uint rozmiar[5], gestosc[4], wyniki[5][4];
    uint wybor;

    rozmiar[0]= 50;
    rozmiar[1]= 100;
    rozmiar[2]= 250;
    rozmiar[3]= 500;
    rozmiar[4]= 1000;

    gestosc[0]= 25;
    gestosc[1]= 50;
    gestosc[2]= 75;
    gestosc[3]= 100;

    /* lgraf= make_shared< graf_lista<int, int> >(1000); */
    /* cout << testK(lgraf, 100); */
    /* return; */

    cout << "Wybierz algorytm: " << endl;
    cout << "1. Kruskal" << endl;
    cout << "2. Prim" << endl;
    cin >> wybor;

    if(wybor == 1){
	cout << "Alg. Kruskala dla listy sąsiedztwa: " << endl;
	for(uint i=0; i < 5; i++){
	    lgraf= make_shared< graf_lista<int, int> >(rozmiar[i]);
	
	    for(uint j= 0; j < 4; j++){
		czas= testK(lgraf, gestosc[j]);
		cout << "Czas dla " << rozmiar[i] << " , " << gestosc[j] << "% " << czas << "us" << endl;
		wyniki[i][j]= czas;
	    }
	
	    lgraf.reset();
	}

	for(uint i= 0; i < 4; i++){
	    ofstream plik("wyniki/kruskal/lista/" + to_string(gestosc[i]) + ".txt");
	    for(uint j= 0; j < 5; j++)
		plik << wyniki[j][i] << '\n';

	    plik.close();
	}

	/* --------------------- */

	cout << "Alg. Kruskala dla macierzy sąsiedztwa: " << endl;
	for(uint i=0; i < 5; i++){
	    mgraf= make_shared< graf_macierz<int, int> >(rozmiar[i]);
	
	    for(uint j= 0; j < 4; j++){
		czas= testK(mgraf, gestosc[j]);
		cout << "Czas dla " << rozmiar[i] << " , " << gestosc[j] << "% " << czas << "us" << endl;
		wyniki[i][j]= czas;
	    }
	
	    mgraf.reset();
	}

	for(uint i= 0; i < 4; i++){
	    ofstream plik("wyniki/kruskal/macierz/" + to_string(gestosc[i]) + ".txt");
	    for(uint j= 0; j < 5; j++)
		plik << wyniki[j][i] << '\n';

	    plik.close();
	}
    }
    else if(wybor == 2){
	cout << "Alg. Prima dla listy sąsiedztwa: " << endl;
	for(uint i=0; i < 5; i++){
	    lgraf= make_shared< graf_lista<int, int> >(rozmiar[i]);
	
	    for(uint j= 0; j < 4; j++){
		czas= testP(lgraf, gestosc[j]);
		cout << "Czas dla " << rozmiar[i] << " , " << gestosc[j] << "% " << czas << "us" << endl;
		wyniki[i][j]= czas;
	    }
	
	    lgraf.reset();
	}

	for(uint i= 0; i < 4; i++){
	    ofstream plik("wyniki/prim/lista/" + to_string(gestosc[i]) + ".txt");
	    for(uint j= 0; j < 5; j++)
		plik << wyniki[j][i] << '\n';

	    plik.close();
	}

	/* --------------------- */

	cout << "Alg. Prima dla macierzy sąsiedztwa: " << endl;
	for(uint i=0; i < 5; i++){
	    mgraf= make_shared< graf_macierz<int, int> >(rozmiar[i]);
	
	    for(uint j= 0; j < 4; j++){
		czas= testP(mgraf, gestosc[j]);
		cout << "Czas dla " << rozmiar[i] << " , " << gestosc[j] << "% " << czas << "us" << endl;
		wyniki[i][j]= czas;
	    }
	
	    mgraf.reset();
	}

	for(uint i= 0; i < 4; i++){
	    ofstream plik("wyniki/prim/macierz/" + to_string(gestosc[i]) + ".txt");
	    for(uint j= 0; j < 5; j++)
		plik << wyniki[j][i] << '\n';

	    plik.close();
	}
    }
}
