#include <iostream>
#include "Knight.h"
#include "Algorithms.h"
#include "Performance.h"

using namespace std;

void clearTerminal()
{
    cout << "\033[2J\033[1;1H";
}

int main()
{
    greedySearch(0,0,6);

    return 0;


    Performance perfomance;
    Knight knight;
    clearTerminal();
    short int option;
    while (true)
    {
        int order;

        cout << "\x1B[1m\nMENU =====================" << endl;
        cout << "1.\x1B[0m\x1B[3mEscolher estado inicial\x1B[0m \x1B[1m" << endl;
        cout << "2.\x1B[0m\x1B[3mPosição atual do cavalo\x1B[0m \x1B[1m" << endl;
        cout << "3.\x1B[0m\x1B[3mBacktracking\x1B[0m \x1B[1m" << endl;
        cout << "4.\x1B[0m\x1B[3mBusca em Largura\x1B[0m \x1B[1m" << endl;
        cout << "5.\x1B[0m\x1B[3mBusca em profundidade\x1B[0m \x1B[1m" << endl;
        cout << "0.\x1B[0m\x1B[3mSair\x1B[0m \x1B[1m" << endl;
        cout << "=========================\x1B[0m" << endl;
        cout << "Opção: ";

        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            clearTerminal();
            cout << "Opção inválida" << endl;
            continue;
        }

        clearTerminal();
        if (option == 1)
        {
            knight.setPosition();
        }
        else if (option == 2)
        {
            knight.printPosition();
        }
        else if (option == 3)
        {
            cout << "Digite a ordem do tabuleiro: " << endl;
            cin >> order;

            perfomance.start();
            backtracking(knight.getX(), knight.getY(), order);
            perfomance.end();
        }

        else if (option == 4)
        {
            cout << "Digite a ordem do tabuleiro: " << endl;
            cin >> order;

            perfomance.start();
            breadthFirstSearch(knight.getX(), knight.getY(), order);
            perfomance.end();
        }

        else if (option == 5)
        {
            cout << "Digite a ordem do tabuleiro: " << endl;
            cin >> order;

            perfomance.start();
            depthFirstSearch(knight.getX(), knight.getY(), order);
            perfomance.end();
        }
        else if (option == 0)
        {
            break;
        }
        else
        {
            clearTerminal();
            cout << "Opção inválida" << endl;
        }
    }
}