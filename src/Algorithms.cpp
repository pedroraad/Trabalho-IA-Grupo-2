#include "Algorithms.h"
#include "Moviment.cpp"
#include <iostream>
#include <map>

using namespace std;

void printList(list<Moviment *> myList)
{
    for (Moviment *value : myList)
    {
        std::cout << value->getWeight() << " ";
    }
    std::cout << std::endl;
}

void printVector(vector<Moviment *> myList)
{

    for (Moviment *value : myList)
        cout << value->getReachableMoviments().size() << ",";

    cout << endl;
}

void printResults(Moviment *winner, int iterations, string resultFilename)
{
    cout << "Solução encontrada : " << endl;
    winner->printSolution(resultFilename);
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

            current->board->setPositionVisited(current->getArrayPosition());

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
                printResults(current, iterations + 1, "resultBFS");
            }
            else
            {
                for (Moviment *mov : current->getReachableMoviments())
                    open.push_back(mov);
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
    current->board->setPositionVisited(current->getArrayPosition());
    iterations++;

    closed.push_back(current);

    if (current->board->getNumberOfVisitedCells() == order * order)
    {
        printResults(current, iterations, "resultbacktracking");
        return true;
    }

    vector<Moviment *> validMoviments = current->getReachableMoviments();

    for (Moviment *validMoviment : validMoviments)
    {

        if (solveBacktracking(validMoviment, order))
            return true;
    }

    current->board->setPositionVisited(current->getArrayPosition(), false);
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

bool compareMoviments(Moviment *a, Moviment *b)
{
    return b->getReachableMoviments().size() > a->getReachableMoviments().size();
}

void sortOpenList(list<Moviment *> &open)
{
    open.sort(compareMoviments);
}

void sortOpenList(vector<Moviment *> &open)
{
    sort(open.begin(), open.end(), compareMoviments);
}

bool compareWeight(Moviment *a, Moviment *b)
{
    return a->getWeight() > b->getWeight();
}

void sortOpenListByWeight(list<Moviment *> &open, int iterations)
{
    open.sort(compareWeight);
}

bool solveGreedySearch(Moviment *current, int order)
{

    current->board->setPositionVisited(current->getArrayPosition());
    iterations++;

    closed.push_back(current);

    if (current->board->getNumberOfVisitedCells() == order * order)
    {

        printResults(current, iterations, "resultGreedy");
        return true;
    }

    vector<Moviment *> validMoviments = current->getReachableMoviments();

    sortOpenList(validMoviments);

    for (Moviment *validMoviment : validMoviments)
    {
        if (solveGreedySearch(validMoviment, order))
            return true;
    }

    current->board->setPositionVisited(current->getArrayPosition(), false);
    return false;
}

void greedySearch(int x, int y, int order)
{

    iterations = 0;

    Moviment *moviment = new Moviment(x, y, order);
    solveGreedySearch(moviment, order);
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

            current->board->setPositionVisited(current->getArrayPosition());

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
                printResults(current, iterations + 1, "resultDFS");
            }
            else
            {
                for (Moviment *mov : current->getReachableMoviments())
                    open.push_front(mov);
            }

            closed.push_back(current);
        }

        iterations++;
    }
}

bool compareAStar(Moviment *a, Moviment *b)
{

    return b->getAstarWeight() > a->getAstarWeight();
}

void sortAStarOpenList(list<Moviment *> &open, int iterations)
{
    open.sort(compareAStar);
}

void orderedSearch(int x, int y, int order)
{
    bool success = false, failure = false;

    list<Moviment *> open;

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
            sortOpenListByWeight(open, iterations);

            Moviment *current = open.front();
            open.pop_front();

            current->board->setPositionVisited(current->getArrayPosition());

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
                printResults(current, iterations + 1, "resultOrdered");
            }
            else
            {

                for (Moviment *mov : current->getReachableMoviments())
                    open.push_front(mov);
            }
        }

        iterations++;
    }
}

void aStarSearch(int x, int y, int order)
{
    bool success = false, failure = false;

    list<Moviment *> open;
    list<Moviment *> closed;

    Moviment *moviment = new Moviment(x, y, order);
    open.push_front(moviment);

    int iterations = 0;

    while (!(success || failure))
    {
        iterations++;

        if (open.empty())
        {
            cout << "Fila vazia : falhou " << endl;
            failure = true;
        }
        else
        {

            sortAStarOpenList(open, iterations);

            Moviment *current = open.front();
            open.pop_front();

            current->board->setPositionVisited(current->getArrayPosition());

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
                printResults(current, iterations + 1, "aStar");
            }
            else
            {
                for (Moviment *mov : current->getReachableMoviments())
                    open.push_front(mov);
            }

            closed.push_back(current);
        }
    }
}
