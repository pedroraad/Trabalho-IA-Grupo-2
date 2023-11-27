#include "Algorithms.h"
#include "Moviment.cpp"
#include <iostream>
#include <map>

using namespace std;

static void printBoard(bool board[64])
{
    cout << "    A   B   C   D   E   F   G   H" << endl;
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++)
        {
            cout << " " << (board[i + j * 8] ? 'X' : ' ') << " |";
        }
        cout << " " << 8 - i << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << "    A   B   C   D   E   F   G   H" << endl;
}

static void printBoard(char board[8][8], int previousX = -1, int previousY = -1)
{
    cout << "    A   B   C   D   E   F   G   H" << endl;
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << 8 - i << " |";
        for (int j = 0; j < 8; j++)
        {
            cout << " " << (board[i][j] == 'K' ? "\x1B[32m\x1B[1m" : (i == previousX && j == previousY ? "\x1B[31m" : "\x1B[94m")) << board[i][j] << "\x1B[0m"
                 << " |";
        }
        cout << " " << 8 - i << endl;
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << "    A   B   C   D   E   F   G   H" << endl;
}

static vector<int> createTable()
{
    int size = 64;

    vector<int> table;

    table.resize(64, 0);

    return table;
}

static void printTable(vector<int> table)
{
    int counter = 1;

    for (auto cell : table)
    {
        cout << "|" << cell << "|";

        if (counter % 8 == 0)
        {
            cout << endl;
        }

        counter++;
    }
}

void printResults(Moviment *winner, int iterations)
{
    cout << "Solução encontrada : " << endl;
    winner->printSolution();
    cout << "Estados explorados: " << iterations << endl;
}

void getResultPath(Moviment *mov)
{
    vector<int> result;

    result.resize(64);

    Moviment *aux = mov;

    while (aux != nullptr)
    {
        result.push_back(aux->getArrayPosition());

        aux = mov->getFather();
    }

    for (int i = 0; i < result.size(); i++)
    {
        cout << "| " << result.at(i) << "| ";
    }

    cout << endl;
}

void closedListToViz(list<Moviment *> closed)
{
    ofstream file("result.dot");
    stringstream stream;

    if (file.is_open())
    {

        stream << "graph G {\n";

        for (Moviment *mov : closed)
        {
            if (mov->getFather() != nullptr)
                stream << mov->getFather()->getPosition() << "--" << mov->getPosition() << ";\n";
        }

        stream << "\n}";
    }

    file << stream.str();
}

void lastNodeToViz(Moviment *start)
{
    ofstream file("result.dot");
    stringstream stream;

    if (file.is_open())
    {

        stream << "graph G {\n";

        Moviment *current = start;

        while (current != nullptr)
        {

            if (current->getFather() != nullptr)
                stream << current->getFather()->getPosition() << "--" << current->getPosition() << ";\n";
            current = current->getFather();
        }

        stream << "\n}";
    }

    file << stream.str();
}

void breadthFirstSearch(int x, int y, int order)
{

    bool success = false, failure = false;

    list<Moviment *> open;
    list<Moviment *> closed;

    Moviment *moviment = new Moviment(x, y, order);

    open.push_back(moviment);

    int iterations = 0;

    while (!(success || failure))
    {
        if (open.empty())
        {
            cout << "Fila vazia : falhou " << endl;
            failure = true;
        }
        else
        {
            Moviment *current = open.front();
            open.pop_front();

            current->board->visited[current->getArrayPosition()] = true;

            if (iterations == 20)
                closedListToViz(closed);

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
                printResults(current, iterations + 1);
            }
            else
            {

                for (Moviment *mov : current->getReachableMoviments())
                {
                    // Checa se o próxima celula da lista de alcançaveis ainda não foi visitado
                    if (!current->board->hasAlreadyVisited(mov->getArrayPosition()))
                    {
                        mov->board->setVisited(current->board->getVisited());
                        mov->setFather(current);

                        open.push_back(mov);
                    }
                }
            }

            closed.push_back(current);
        }

        iterations++;
    }
}

int getNumberOfVisitedCells(vector<bool> visited)
{
    int counter = 0;

    for (bool element : visited)
    {
        if (element)
            counter++;
    }

    return counter;
}

int iterations = 0;
list<Moviment *> closed;

bool solveBacktracking(Moviment *current, int order)
{
    current->board->visited[current->getArrayPosition()] = true;
    iterations++;

    closed.push_back(current);

    if (current->board->getNumberOfVisitedCells() == order * order)
    {

        printResults(current, iterations);
        return true;
    }

    vector<Moviment *> validMoviments = current->getReachableMoviments();

    for (Moviment *validMoviment : validMoviments)
    {
        validMoviment->setBoard(current->board);
        if (solveBacktracking(validMoviment, order))
        {
            return true;
        }
    }

    current->board->visited[current->getArrayPosition()] = false;
    return false;
}

void backtracking(int x, int y, int order)
{
    Moviment *start = new Moviment(x, y, order);
    iterations = 0;
    closed.resize(0);

    if (!solveBacktracking(start, order))
    {
        cout << "Não encontrado" << endl;
    }
}

void depthFirstSearch(int x, int y, int order)
{

    bool success = false, failure = false;

    list<Moviment *> open;
    list<Moviment *> closed;

    Moviment *moviment = new Moviment(x, y, order);
    open.push_front(moviment);

    int iterations = 0;

    while (!(success || failure))
    {
        if (open.empty())
        {
            cout << "Fila vazia : falhou " << endl;
            failure = true;
        }
        else
        {
            Moviment *current = open.front();
            open.pop_front();

            current->board->visited[current->getArrayPosition()] = true;

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
                printResults(current, iterations + 1);
            }

            if (iterations == 20)
                closedListToViz(closed);

            else
            {

                for (Moviment *mov : current->getReachableMoviments())
                {
                    // Checa se o próxima celula da lista de alcançaveis ainda não foi visitado
                    if (!current->board->hasAlreadyVisited(mov->getArrayPosition()))
                    {

                        mov->board->setVisited(current->board->getVisited());
                        mov->setFather(current);

                        open.push_front(mov);
                    }
                }
            }

            closed.push_back(current);
        }

        iterations++;
    }
}
