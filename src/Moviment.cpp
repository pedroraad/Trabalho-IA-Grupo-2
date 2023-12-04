#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Util.cpp"
#include "Board.cpp"

using namespace std;

class Moviment
{
private:
    Moviment *father;

    int boardOrder;
    int weight;
    int x;
    int y;

public:
    int numberOfReachablePositions;
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
        delete father;
    }

    Moviment(int x, int y, Moviment *father)
    {
        this->x = x;
        this->y = y;
        this->father = father;

        this->board = new Board(this->boardOrder);
    }

    double getAstarWeight(){
        return this->getPathWeight() + this->getWeight();
    }

    vector<Moviment *> getReachableMoviments()
    {
        vector<Moviment *> possibleMoviments;

        auto addIfValid = [&](int x, int y)
        {
            if (x >= 0 && x < boardOrder && y >= 0 && y < boardOrder)
            {
                Moviment *newMove = new Moviment(x, y, boardOrder);

                if (!this->board->visited[newMove->getArrayPosition()])
                {
                    // Verifica se o movimento já está na lista
                    auto it = std::find_if(possibleMoviments.begin(), possibleMoviments.end(),
                                           [newMove](Moviment *existingMove)
                                           {
                                               return existingMove->x == newMove->x &&
                                                      existingMove->y == newMove->y;
                                           });

                    if (it == possibleMoviments.end())
                    {
                        newMove->setFather(this);
                        newMove->board->setVisited(this->board->visited);
                        newMove->board->updateVisitedPositions(this->board->getNumberOfVisitedCells());

                        possibleMoviments.push_back(newMove);
                    }
                    else
                    {
                        delete newMove;
                    }
                }
            }
        };

        // 2 casas para cima 1 casa para direita
        addIfValid(this->x + 1, y - 2);
        // 2 casas para cima 1 casa para esquerda
        addIfValid(this->x - 1, y - 2);

        // 2 casas para baixo  1 casa para direita
        addIfValid(x + 1, y + 2);
        // 2 casas para baixo 1 casa para esquerda
        addIfValid(x - 1, y + 2);

        // 2 casas para direita 1 casa para baixo
        addIfValid(x + 2, y + 1);
        // 2 casas para direita 1 casa para cima
        addIfValid(x + 2, y - 1);

        // 2 casas para esquerda 1 casa para baixo
        addIfValid(x - 2, y + 1);
        // 2 casas para esquerda 1 casa para cima
        addIfValid(x - 2, y - 1);

        this->numberOfReachablePositions = possibleMoviments.size();

        return possibleMoviments;
    }

    int getArrayPosition()
    {
        return y * boardOrder + x;
    }

    string getPosition()
    {
        return to_string(y) + to_string(x);
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
        this->father = mov;
    }

    Moviment *getFather()
    {
        return this->father;
    }

    void printSolution(string resultFilename)
    {
        Util util;

        Moviment *aux = this;
        int posCounter = (boardOrder * boardOrder) - 1;

        vector<int> table;
        table.resize(boardOrder * boardOrder, -1);

        int auxCounter = 0;

        while (aux != nullptr)
        {
            table[aux->getArrayPosition()] = posCounter;

            aux = aux->getFather();
            posCounter--;
        }

        int counter = 1;

        cout << "---------------------------------------------" << endl;

        for (auto cell : table)
        {
            cout << "| " << cell << " |";

            if (counter % boardOrder == 0)
            {
                cout << endl;
            }

            counter++;
        }

        cout << "-----------------------------------------------" << endl;

        util.createJsonFileResult(table, resultFilename + ".json", boardOrder);
    }

    int getPathWeight()
    {

        Moviment *aux = this;

        int totalWeight = 0;

        while (aux != nullptr)
        {
            totalWeight += aux->getWeight();
            aux = aux->getFather();
        }

        return totalWeight;
    }

    int getWeight()
    {
        double weight = this->board->getNumberOfVisitedCells();

        
        if(this->father != nullptr)
            weight += father->getWeight();

        return weight;
    }

    void setBoard(Board *board)
    {
        this->board = board;
    }
};
