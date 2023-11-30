#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 8; // Tamanho do tabuleiro
int iterations = 0;

// Vetores de deslocamento para os movimentos do cavalo
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

// Função para verificar se a próxima posição é válida
bool isSafe(int x, int y, const std::vector<std::vector<int>>& board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Função para calcular o número de casas alcançáveis a partir de uma posição específica
int countMoves(int x, int y, const std::vector<std::vector<int>>& board) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (isSafe(nextX, nextY, board)) {
            ++count;
        }
    }
    return count;
}

// Função principal para o passeio do cavalo usando Warnsdorff's rule
bool knightTour(int x, int y, int movei, std::vector<std::vector<int>>& board) {
   iterations++;
    if (movei == N * N)
        return true;

    std::vector<std::pair<int, int>> nextMoves;

    // Encontrar todos os movimentos possíveis a partir da posição atual
    for (int i = 0; i < 8; ++i) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (isSafe(nextX, nextY, board)) {
            int moves = countMoves(nextX, nextY, board);
            nextMoves.emplace_back(std::make_pair(moves, i));
        }
    }

    // Ordenar os movimentos com base no número de movimentos possíveis
    std::sort(nextMoves.begin(), nextMoves.end());

    for (const auto& move : nextMoves) {
        int nextX = x + dx[move.second];
        int nextY = y + dy[move.second];
        board[nextX][nextY] = movei;

        if (knightTour(nextX, nextY, movei + 1, board)) {
            return true;
        }

        // Se o movimento atual não levar a uma solução, desfaça o movimento
        board[nextX][nextY] = -1;
    }

    // Não há solução a partir desta posição
    return false;
}

// Função de inicialização para resolver o problema do Knight's Tour
void solveKnightTour() {

    std::vector<std::vector<int>> board(N, std::vector<int>(N, -1));

    // Iniciar o passeio do cavalo a partir da posição (0, 0)
    board[5][5] = 0;

    if (knightTour(5, 5, 1, board)) {
        // Imprimir a solução
        for (const auto& row : board) {
            for (int move : row) {
                std::cout << move << "\t";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Não há solução para o problema do Knight's Tour a partir da posição (0, 0)." << std::endl;
    }

    cout << "It: " << iterations << endl;
}

int main() {
    solveKnightTour();

    return 0;
}