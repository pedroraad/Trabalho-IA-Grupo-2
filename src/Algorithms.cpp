#include "Algorithms.h"
#include <iostream>
#include <map>

using namespace std;

std::map<int, string> Xs = { {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"} };
std::map<int, string> Ys = { {0, "8"}, {1, "7"}, {2, "6"}, {3, "5"}, {4, "4"}, {5, "3"}, {6, "2"}, {7, "1"} };

static void printBoard(bool board[64]) {
    cout << "    A   B   C   D   E   F   G   H" << endl;
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " |" ;
        for (int j = 0; j < 8; j++) {
            cout << " " << (board[i+j*8] ? 'X' : ' ') << " |";
        }
        cout << " " << 8 - i << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << "    A   B   C   D   E   F   G   H" << endl;
}

static vector<int*> auxBacktraking(int x, int y, vector<int*> path, bool board[64]) {
    // printBoard(board);
    // char a;
    // cout << path.size() << endl;
    // cout << "position: " + Ys[x] + Xs[y] << endl;
    // if (path.size() > 45) {
    //     std::cin >> a;
    // }


    if (path.size() == 64) {
        printBoard(board);
        return path;
    }
    
    for (int i = -2; i <= 2; i++) {
        if (i == 0) {
            continue;
        }
        int j = 3 - abs(i);
        if (x + i >= 0 && x + i < 8) {
            if (y + j >= 0 && y + j < 8) {
                if (board[x + i + (y + j) * 8] == false) {
                    board[x + i + (y + j) * 8] = new bool[true];
                    path.push_back(new int[2] { x + i, y + j });
                    vector<int*> aux = auxBacktraking(x + i, y + j, path, board);
                    if (aux.size() != 0) return aux;
                    path.pop_back();
                    board[x + i + (y + j) * 8] = false;
                }
            } 
            if (y - j >= 0 && y - j < 8) {
                if (board[x + i + (y - j) * 8] == false) {
                    board[x + i + (y - j) * 8] = true;
                    path.push_back(new int[2] { x + i, y - j });
                    vector<int*> aux = auxBacktraking(x + i, y - j, path, board);
                    if (aux.size() != 0) return aux;
                    path.pop_back();
                    board[x + i + (y - j) * 8] = false;
                }
            } 
        }
    }
    
    return vector<int*>();
}

static void printBoard(char board[8][8]) {
    cout << "    A   B   C   D   E   F   G   H" << endl;
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++) {
            cout << " " << (board[i][j] == 'K' ? "\x1B[32m" : "") << board[i][j] << (board[i][j] == 'K' ? "\x1B[37m" : "") << " |";
        }
        cout << " " << 8 - i << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << "    A   B   C   D   E   F   G   H" << endl;
}

void backtraking(int x, int y) {
    bool board[64] = { false };
    board[x + y * 8] = true;
    vector<int*> path;
    path.push_back(new int[2] { x, y });

    path = auxBacktraking(x, y, path, board);

    char pBoard[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            pBoard[i][j] = ' ';
        }
    }    

    if (path.size() > 0){
        for (int i = 1; i < path.size(); i++) {
            pBoard[path[i - 1][0]][path[i - 1][1]] = ':';
            pBoard[path[i][0]][path[i][1]] = 'K';
            cout << "ITERATION " << i << endl;
            printBoard(pBoard);
            cout << endl;
        }
    } else {
        cout << "NAO ENCONTRADO" << endl;
    }

    

    cout << "[APERTE QUALQUER TECLA PRA CONTINUAR]" << endl;
    
    std::cin.get();
}