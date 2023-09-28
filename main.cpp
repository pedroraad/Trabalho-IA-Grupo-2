#include <iostream>
#include "include/Knight.h"

using namespace std;

void clearTerminal(){
    cout << "\033[2J\033[1;1H";
}

int main(){
    clearTerminal();
    Knight knight;
    int option = 1;
    while (true) {
        cout << "\nMENU =====================" << endl;
        cout << "1. Escolher estado inicial" << endl;
        cout << "2. Posição atual do cavalo" << endl;
        cout << "3. Backtracking" << endl;
        cout << "0. Exit" << endl;
        cout << "=========================" << endl;
        cout << "Option: ";
        try
        {
            cin >> option;
        }
        catch(const std::exception& e)
        {
            clearTerminal();
            std::cerr << e.what() << '\n';
            continue;
        }
        clearTerminal();
        if (option == 1) {
            knight.setPosition();
        }
        else if (option == 2) {
            knight.printPosition();
        }
        else if (option == 3) {
            clearTerminal();
            cout << "Ainda não implementado" << endl;
        }
        else if (option == 0) {
            break;
        }else {
            clearTerminal();
            cout << "Opção inválida" << endl;
        }
    }
}