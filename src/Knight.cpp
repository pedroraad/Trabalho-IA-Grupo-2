#include "Knight.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

/**
 * Cria um objeto Cavalo.
 * 
 * @param x Posição inicial x do cavalo.
 * @param y Posição inicial y do cavalo.
 * 
 * @return Objeto Cavalo
*/
Knight::Knight(int x, int y) : x(x), y(y) {}

Knight::~Knight() {}

/**
 * Retorna a posição x do cavalo.
 * 
 * @return Posição x do cavalo.
*/
int Knight::getX() {
    return x;
}

/**
 * Retorna a posição y do cavalo.
 * 
 * @return Posição y do cavalo.
*/
int Knight::getY() {
    return y;
}

/**
 * Configura a posição x do cavalo em um intervalo de 0 a 7.
 *
 * @param x valor a ser configurado
 *
 * @throws Exception se o valor for inválido
 */
void Knight::setX(int x) {
    if (x < 8 && x >= 0) {
        this->x = x;
    } else {
        throw runtime_error("Posição inválida");
    }
}

/**
 * Configura a posição y do cavalo em um intervalo de 0 a 7.
 *
 * @param y valor a ser configurado
 *
 * @throws Exception se o valor for inválido
 */
void Knight::setY(int y) {
    if (y < 8 && y >= 0) {
        this->y = y;
    } else {
        throw runtime_error("Posição inválida");
    }
}
/**
 * Função feita para ser usada no menu. Configura a posição do cavalo.
 */
void Knight::setPosition() {
    this->printPosition();
    int x, y;
    try
    {
        cout << "Novo x: ";
        cin >> x;
        cout << "Novo y: ";
        cin >> y;
        this->setX(x);
        this->setY(y);
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }
}


void Knight::printPosition() {
    string underlines(19, '_');
    string hyphens(19, '-');

    cout << "Posição do cavalo: " << endl;
    cout << " " + underlines << endl;
    cout << "|" << setw(10) << "Eixo x |" << setw(10) << "Eixo y |" << endl;
    cout << "|" << setw(10) << to_string(this->getX()) + " |" << setw(10) << to_string(this->getY()) + " |" << endl;
    cout << " " + hyphens << endl;
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
