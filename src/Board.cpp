#include <iostream>
#include <vector>
using namespace std;

class Board
{
private:
    vector<int> board;

public:
    vector<bool> visited;

    Board(vector<int> board, vector<bool> visited)
    {
        this->board = board;
        this->visited = visited;
    }

    Board()
    {
        this->board.resize(64);
        this->visited.resize(64, false);
    };

    ~Board(){
        visited.resize(0);
    }

    vector<int> getBoard()
    {
        return this->board;
    }

    void setBoard(vector<int> board)
    {
        this->board = board;
    }

    bool hasAlreadyVisited(int position)
    {
        return visited[position];
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

        for (bool element : visited)
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

            if (counter % 8 == 0)
            {
                cout << endl;
            }

            counter++;
        }

        cout << "-----------------------------------------------" << endl;
    }
};
