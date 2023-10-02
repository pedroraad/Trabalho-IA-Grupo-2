#include <iostream>
#include "include/Knight.h"

using namespace std;

void clearTerminal(){
    cout << "\033[2J\033[1;1H";
}

int main(){
    clearTerminal();
    Knight knight;
    short int option;
    while (true) {
        cout << "\nMENU =====================" << endl;
        cout << "1. Escolher estado inicial" << endl;
        cout << "2. Posição atual do cavalo" << endl;
        cout << "3. Backtracking" << endl;
        cout << "0. Sair" << endl;
        cout << "=========================" << endl;
        cout << "Opção: ";

        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100,'\n');
            clearTerminal();
            cout << "Opção inválida" << endl;
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