#include <iostream>
#include <vector>
using namespace std;

class Moviment
{
private:
    Moviment* father;
    int x;
    int y;

public:
    Moviment(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->father = nullptr;
    }

    Moviment(int x, int y, Moviment* father)
    {
        this->x = x;
        this->y = y;
        this->father = father;
    }

    vector<Moviment*> getReachableMoviments()
    {
        vector<Moviment*> possibleMoviments;

        // 2 casas para cima
        if (this->y - 2 >= 0)
        {
            int newYPos = this->y - 2;

            // 1 casa para direita
            if (this->x + 1 <= 7)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x + 1));
            }

            // 1 casa para esquerda
            if (this->x - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x - 1));
            }
        }

        // 2 casas para baixo
        if (this->y + 2 <= 7)
        {
            int newYPos = this->y + 2;

            // 1 casa para direita
            if (this->x + 1 <= 7)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x + 1));
            }

            // 1 casa para esquerda
            if (this->x - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(newYPos, this->x - 1));
            }
        }

        // 2 casas para direita
        if (this->x + 2 <= 7)
        {
            int newXPos = this->x + 2;

            // 1 casa para baixo
            if (this->y + 1 <= 7)
            {
                possibleMoviments.push_back(new Moviment(this->y + 1, newXPos));
            }

            // 1 casa para cima
            if (this->y - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(this->y - 1, newXPos));
            }
        }

        // 2 casas para esquerda
        if (this->x - 2 >= 0)
        {
            int newXPos = this->x + 2;

            // 1 casa para baixo
            if (this->y + 1 <= 7)
            {
                possibleMoviments.push_back(new Moviment(this->y + 1, newXPos));
            }

            // 1 casa para cima
            if (this->y - 1 >= 0)
            {
                possibleMoviments.push_back(new Moviment(this->y - 1, newXPos));
            }
        }

        return possibleMoviments;
    }

    int getArrayPosition()
    {
        return y * 8 + x;
    }

    void printPosition(){
        cout << y << x << endl;
    }

    void setFather(Moviment *mov){
        this->father = father;
    }

    Moviment* getFather(){
        return this->father;
    }
};
