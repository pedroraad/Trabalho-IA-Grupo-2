#include <iostream>
#include "Knight.h"
#include "Algorithms.h"

using namespace std;

void clearTerminal(){
    cout << "\033[2J\033[1;1H";
}

int main(){
    breadthFirstSearch(0, 0, 5);    

    /*   
    clearTerminal();
    Knight knight;
    short int option;
    while (true) {
        cout << "\x1B[1m\nMENU =====================" << endl;
        cout << "1.\x1B[0m\x1B[3mEscolher estado inicial\x1B[0m \x1B[1m" << endl;
        cout << "2.\x1B[0m\x1B[3mPosição atual do cavalo\x1B[0m \x1B[1m" << endl;
        cout << "3.\x1B[0m\x1B[3mBacktracking\x1B[0m \x1B[1m" << endl;
        cout << "0.\x1B[0m\x1B[3mSair\x1B[0m \x1B[1m" << endl;
        cout << "=========================\x1B[0m" << endl;
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
            backtraking(knight.getX(), knight.getY());
        }
        else if (option == 0) {
            break;
        }else {
            clearTerminal();
            cout << "Opção inválida" << endl;
        }
    }

    */
}