#ifndef KNIGHT_H_INCLUDED
#define KNIGHT_H_INCLUDED

class Knight {
private:
    int x, y;

public:

    Knight(int x = 0, int y = 0);
    ~Knight();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setPosition();
    void printPosition();
};

#endif