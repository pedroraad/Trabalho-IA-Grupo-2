#include <iostream>
#include <vector>
using namespace std;

class Board
{
private:
    int boardSize;
    int order;

public:
    vector<bool> visited;

    Board(vector<bool> visited, int order)
    {
        this->visited = visited;
        this->order = order;
        this->boardSize = order * order;
    }

    Board(int order)
    {
        this->boardSize = order * order;
        this->order = order;
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

    vector<bool> clone(const std::vector<bool> &original)
    {

        return std::vector<bool>(original.begin(), original.end());
    }
};
