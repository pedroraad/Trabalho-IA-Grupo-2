#ifndef KNIGHT_H_INCLUDED
#define KNIGHT_H_INCLUDED

class Knight {
private:
    int x, y;

public:

    Knight(int x = 4, int y = 7);
    ~Knight();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void move();
};

#endif