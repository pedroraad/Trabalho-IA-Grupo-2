#include <iostream>
#include <vector>
#include "Board.cpp"

using namespace std;

class Moviment
{
private:
    Moviment *father;

    int boardOrder;
    int x;
    int y;

public:
    Board *board;

    Moviment(int x, int y, int boardOrder)
    {
        this->x = x;
        this->y = y;
        this->father = nullptr;

        this->boardOrder = boardOrder;

        this->board = new Board(boardOrder);
    }

    ~Moviment()
    {
        delete board;
    }

    Moviment(int x, int y, Moviment *father)
    {
        this->x = x;
        this->y = y;
        this->father = father;

        this->board = new Board(this->boardOrder);
    }

    vector<Moviment *> getReachableMoviments()
    {
        vector<Moviment *> possibleMoviments;

        // 2 casas para cima
        if (this->y - 2 >= 0)
        {
            int newYPos = this->y - 2;

            // 1 casa para direita
            if (this->x + 1 <= boardOrder - 1)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x + 1, this->boardOrder));
            }

            // 1 casa para esquerda
            if (this->x - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x - 1, this->boardOrder));
            }
        }

        // 2 casas para baixo
        if (this->y + 2 <= boardOrder - 1)
        {
            int newYPos = this->y + 2;

            // 1 casa para direita
            if (this->x + 1 <= boardOrder - 1)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x + 1, this->boardOrder));
            }

            // 1 casa para esquerda
            if (this->x - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x - 1, this->boardOrder));
            }
        }

        // 2 casas para direita
        if (this->x + 2 <= boardOrder - 1)
        {
            int newXPos = this->x + 2;

            // 1 casa para baixo
            if (this->y + 1 <= boardOrder - 1)
            {
                possibleMoviments.push_back(new Moviment(this->y + 1, newXPos, this->boardOrder));
            }

            // 1 casa para cima
            if (this->y - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(this->y - 1, newXPos, this->boardOrder));
            }
        }

        // 2 casas para esquerda
        if (this->x - 2 >= 0)
        {
            int newXPos = this->x + 2;

            // 1 casa para baixo
            if (this->y + 1 <= boardOrder - 1)
            {
                possibleMoviments.push_back(new Moviment(this->y + 1, newXPos, this->boardOrder));
            }

            // 1 casa para cima
            if (this->y - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(this->y - 1, newXPos, this->boardOrder));
            }
        }

        return possibleMoviments;
    }

    int getArrayPosition()
    {
        return y * 8 + x;
    }

    void printPosition()
    {
        cout << y << x << endl;
    }

    void printReachableMoviments()
    {
        vector<Moviment *> reachable = getReachableMoviments();

        for (auto mov : reachable)
        {
            mov->printPosition();
        }
    }

    void setFather(Moviment *mov)
    {
        this->father = father;
    }

    Moviment *getFather()
    {
        return this->father;
    }

    void setBoard(Board *board)
    {
        this->board = board;
    }
};
