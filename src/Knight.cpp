#include "Knight.h"
#include <stdexcept>

using namespace std;

/**
 * Cria um objeto Cavalo
 * 
 * @param x Posição inicial x do cavalo
 * @param y Posição inicial y do cavalo
 * 
 * @return Objeto Cavalo
*/
Knight::Knight(int x, int y) : x(x), y(y) {}

Knight::~Knight() {}

/**
 * Retorna a posição x do cavalo
 * 
 * @return Posição x do cavalo
*/
int Knight::getX() {
    return x;
}

/**
 * Retorna a posição y do cavalo
 * 
 * @return Posição y do cavalo
*/
int Knight::getY() {
    return y;
}

/**
 * Sets the value of 'x' within a valid range.
 *
 * @param x the value to be set
 *
 * @throws const char* if the position is invalid
 */
void Knight::setX(int x) {
    if (x < 8 && x >= 0) {
        this->x = x;
    } else {
        throw runtime_error("Posição inválida");
    }
}

/**
 * Sets the value of 'y' within a valid range.
 *
 * @param y the value to be set
 *
 * @throws const char* if the position is invalid
 */
void Knight::setY(int y) {
    if (y < 8 && y >= 0) {
        this->y = y;
    } else {
        throw runtime_error("Posição inválida");
    }
}

/**
 * Tenta mexer o cavalo na seguinte ordem:
 * - 2 direita e 1 cima
 * - 1 direita e 2 cima
 * - 2 esquerda e 1 cima
 * - 1 esquerda e 2 cima
 * - 2 direita e 1 baixo
 * - 1 direita e 2 baixo
 * - 2 esquerda e 1 baixo
 * - 1 esquerda e 2 baixo
*/
void Knight::move() {
    if (x + 2 < 8 && y + 1 < 8) {
        x += 2;
        y += 1;
    }
    else if (x + 1 < 8 && y + 2 < 8) {
        x += 1;
        y += 2;
    }
    else if (x - 2 >= 0 && y + 1 < 8) {
        x -= 2;
        y += 1;
    }
    else if (x - 1 >= 0 && y + 2 < 8) {
        x -= 1;
        y += 2;
    }
    else if (x + 2 < 8 && y - 1 >= 0) {
        x += 2;
        y -= 1;
    }
    else if (x + 1 < 8 && y - 2 >= 0) {
        x += 1;
        y -= 2;
    }
    else if (x - 2 >= 0 && y - 1 >= 0) {
        x -= 2;
        y -= 1;
    }
    else if (x - 1 >= 0 && y - 2 >= 0) {
        x -= 1;
        y -= 2;
    }
}
