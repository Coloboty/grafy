#include <iostream>
#include "testy.h"

using namespace std;

int main(void){
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
	testujAutomatycznie();
	break;

    default:
	cout << "Nie rozumiem!" << '\n';
	return 0;
	break;
    }
    
    
    cout << "Koniec programu!\n";
    
    return 0;
}
