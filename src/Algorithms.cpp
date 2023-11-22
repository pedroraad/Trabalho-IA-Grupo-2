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

void breadthFirstSearch(int x, int y)
{
    const int order = 5;
    bool success = false, failure = false;

    list<Moviment *> open;
    list<Moviment *> closed;

    Moviment *moviment = new Moviment(x, y, order);

    open.push_back(moviment);

    int max = 0;
    int currentState = 0;

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
                cout << "Solução encontrada : " << endl;
                current->printSolution();
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
        }

        iterations++;
    }
}

void depthFirstSearch(int x, int y)
{
    const int order = 4;
    bool success = false, failure = false;

    list<Moviment *> open;
    list<Moviment *> closed;

    Moviment *moviment = new Moviment(x, y, order);

    open.push_front(moviment);

    int max = 0;
    int currentState = 0;

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

            int repetidos = 0;

            if (current->board->getNumberOfVisitedCells() > max)
            {
                max = current->board->getNumberOfVisitedCells();

                cout << "Maxium : " << max << endl;

                current->printReachableMoviments();
                current->board->printVisited();
            }

            // current->board->printVisited();

            if (current->board->getNumberOfVisitedCells() == order * order)
            {
                success = true;
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

                        bool hasInOpenList = false;

                        open.push_front(mov);
                    }
                }
            }
        }

        iterations++;
    }
}
