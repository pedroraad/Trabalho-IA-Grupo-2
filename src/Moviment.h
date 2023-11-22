#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <iostream>
#include <vector>
#include "Util.cpp"
#include "Board.cpp"

using namespace std;

class Moviment
{
private:
    Moviment *father;
    int boardOrder;
    int x;
    int y;
    Board *board;

public:
    Moviment(int x, int y, int boardOrder);
    ~Moviment();

    Moviment(int x, int y, Moviment *father);

    vector<Moviment *> getReachableMoviments();
    int getArrayPosition();
    void printPosition();
    void printReachableMoviments();

    void setFather(Moviment *mov);
    Moviment *getFather();

    void printSolution();
    void setBoard(Board *board);
};

#endif // MOVIMENT_H