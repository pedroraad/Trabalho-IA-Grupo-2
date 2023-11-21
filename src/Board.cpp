#include <iostream>
#include <vector>
using namespace std;

class Board
{
private:
    const int order = 8;
    int boardSize;

public:
    vector<bool> visited;

    Board(vector<bool> visited)
    {
        this->visited = visited;
        this->boardSize = order * order;
    }

    Board()
    {
        this->boardSize = order * order;
        this->visited.resize(this->boardSize, false);
    };

    ~Board()
    {
        this->visited.resize(0);
    }

    bool hasAlreadyVisited(int position)
    {
        return this->visited[position];
    }

    void setPositionVisited(int position)
    {
        this->visited[position] = true;
    }

    void setVisited(vector<bool> visited)
    {
        this->visited = visited;
    }

    vector<bool> getVisited()
    {
        return this->visited;
    }

    int getNumberOfVisitedCells()
    {
        int counter = 0;

        for (bool element : this->visited)
        {
            if (element)
                counter++;
        }

        return counter;
    }

    void printVisited()
    {
        int counter = 1;

        cout << "---------------------------------------------" << endl;

        for (auto cell : this->visited)
        {
            cout << "|" << cell << "|";

            if (counter % order == 0)
            {
                cout << endl;
            }

            counter++;
        }

        cout << "-----------------------------------------------" << endl;
    }
};
