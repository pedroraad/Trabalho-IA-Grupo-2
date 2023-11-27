#include "Algorithms.h"
#include "Moviment.cpp"
#include <iostream>
#include <map>

using namespace std;

std::map<int, string> Xs = {{0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}};
std::map<int, string> Ys = {{0, "8"}, {1, "7"}, {2, "6"}, {3, "5"}, {4, "4"}, {5, "3"}, {6, "2"}, {7, "1"}};

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

static vector<int *> auxBacktraking(int x, int y, vector<int *> path, bool board[64])
{
    // printBoard(board);
    // char a;
    // cout << path.size() << endl;
    // cout << "position: " + Ys[x] + Xs[y] << endl;
    // if (path.size() > 45) {
    //     std::cin >> a;
    // }

    if (path.size() == 64)
    {
        return path;
    }

    for (int i = -2; i <= 2; i++)
    {
        if (i == 0)
        {
            continue;
        }
        int j = 3 - abs(i);
        if (x + i >= 0 && x + i < 8)
        {
            if (y + j >= 0 && y + j < 8)
            {
                if (board[x + i + (y + j) * 8] == false)
                {
                    board[x + i + (y + j) * 8] = new bool[true];
                    path.push_back(new int[2]{x + i, y + j});
                    vector<int *> aux = auxBacktraking(x + i, y + j, path, board);
                    if (aux.size() != 0)
                        return aux;
                    path.pop_back();
                    board[x + i + (y + j) * 8] = false;
                }
            }
            if (y - j >= 0 && y - j < 8)
            {
                if (board[x + i + (y - j) * 8] == false)
                {
                    board[x + i + (y - j) * 8] = true;
                    path.push_back(new int[2]{x + i, y - j});
                    vector<int *> aux = auxBacktraking(x + i, y - j, path, board);
                    if (aux.size() != 0)
                        return aux;
                    path.pop_back();
                    board[x + i + (y - j) * 8] = false;
                }
            }
        }
    }

    return vector<int *>();
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

void backtraking(int x, int y)
{
    bool board[64] = {false};
    board[x + y * 8] = true;
    vector<int *> path;
    path.push_back(new int[2]{x, y});

    path = auxBacktraking(x, y, path, board);

    char pBoard[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            pBoard[i][j] = ' ';
        }
    }

    if (path.size() > 0)
    {
        for (int i = 0; i < path.size(); i++)
        {
            if (i > 0)
            {
                pBoard[path[i - 1][0]][path[i - 1][1]] = '#';
            }
            pBoard[path[i][0]][path[i][1]] = 'K';
            cout << "ITERATION " << i << endl;
            if (i == 0)
            {
                printBoard(pBoard);
            }
            else
            {
                printBoard(pBoard, path[i - 1][0], path[i - 1][1]);
            }
            cout << endl;
        }
    }
    else
    {
        cout << "NAO ENCONTRADO" << endl;
    }
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

// void greedySearch(int x, int y, int order)
// {

//     bool success = false, failure = false;

//     list<Moviment *> open;

//     vector<bool> visited;
//     visited.resize(64, false);

//     Moviment *moviment = new Moviment(x, y, order);

//     open.push_back(moviment);

//     int iterations = 0;

//     while (!(success || failure))
//     {
//         if (open.empty())
//         {
//             cout << "Fila vazia : falhou " << endl;
//             failure = true;
//         }
//         else
//         {
//             Moviment *current = open.front();
//             open.pop_front();

//             visited[current->getArrayPosition()] = true;

//             int visitedCells = getNumberOfVisitedCells(visited);

//             cout << "Visitadas " << visitedCells << endl;

//             if (visitedCells == order * order)
//             {
//                 success = true;
//                 printResults(current, iterations + 1);
//             }

//             else
//             {
//                 int minNumberOfMoviments = 0;
//                 Moviment *minMoviment = new Moviment(0, 0, order);

//                 for (Moviment *mov : current->getReachableMoviments())
//                 {
//                     // Checa se o próxima celula da lista de alcançaveis ainda não foi visitado
//                     if (!visited[mov->getArrayPosition()])
//                     {
//                         mov->board->setVisited(visited);
//                         mov->setFather(current);

//                         int validMoviments = 0;

//                         for (Moviment *childMov : mov->getReachableMoviments())
//                         {
//                             bool isVisited = visited[childMov->getArrayPosition()];

//                             if (!isVisited)
//                                 validMoviments++;

//                             if (validMoviments < minNumberOfMoviments)
//                             {
//                                 minNumberOfMoviments = validMoviments;
//                                 minMoviment = childMov;
//                             }
//                         }
//                     }
//                 }

//                 open.push_back(minMoviment);
//             }
//         }

//         iterations++;
//     }
// }

// void backtracking(int x, int y, int order)
// {
//     bool success = false;
//     bool failure = false;
//     Moviment *current = new Moviment(x, y, order);

//     while (!(success || failure))
//     {

//         current->board->visited[current->getArrayPosition()] = true;

//         if (current->board->getNumberOfVisitedCells() == order * order)
//             success = true;

//         vector<Moviment *> validMoviments = current->getReachableMoviments();

//         if (validMoviments.size() > 0)
//         {
//             Moviment *next = validMoviments[0];
//             next->setBoard(current->board);
//             current = next;
//         }
//         else
//         {
//             if (current->getFather() != nullptr)
//             {
//                 current->board->visited[current->getArrayPosition()] = false;
//                 Moviment *next = current->getFather();

//                 current = next;
//             }

//             else
//                 failure = true;
//         }
//     }

//     if (success)
//         current->printSolution();

//     else
//         cout << "Solução não encontrada" << endl;
// }

bool solveBacktracking(Moviment *current, int order)
{
    current->board->visited[current->getArrayPosition()] = true;

    if (current->board->getNumberOfVisitedCells() == order * order)
    {
        current->printSolution();
        return true;
    }

    //cout << "Solucionando... " << current->board->getNumberOfVisitedCells() << endl;

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

    if (solveBacktracking(start, order))
    {
        cout << "Encontrado" << endl;
    }
    else
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
