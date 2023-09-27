#include <iostream>
#include "include/Knight.h"

using namespace std;

void clearTerminal(){
    cout << "\033[2J\033[1;1H";
}

int main(){
    Knight knight;
    int option = 1;
    do {
        cout << "\nMENU =====================" << endl;
        cout << "1. Escolher estado inicial" << endl;
        cout << "2. Print knight position" << endl;
        cout << "0. Exit" << endl;
        cout << "=========================" << endl;
        cout << "Option: ";
        cin >> option;
        clearTerminal();
        if (option == 1) {
            cout << "\nPosição atual do cavalo: " << endl << "x -> " << knight.getX() << endl << "y -> " << knight.getY() << endl << endl;
            int x, y;
            try
            {
                cout << "Novo x: ";
                cin >> x;
                knight.setX(x);
                cout << "Novo y: ";
                cin >> y;
                knight.setY(y);
            }
            catch(const std::exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (option == 2) {
            cout << "Posição do cavalo: " << knight.getX() << ", " << knight.getY() << endl;
        }
    } while (option != 0);
}