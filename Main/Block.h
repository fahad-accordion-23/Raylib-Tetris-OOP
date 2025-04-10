#pragma once

#include "Colour.h"
#include "Position.h"
typedef unsigned int uint;

enum Direction
{
    LEFT = -1,
    RIGHT = 1
};

class Block
{
protected:
    uint cellSize;
    uint rotationState;
    COLOUR colour;
    Position (*shape)[4];
    Position position;

public:
    Block();
    Block(Position position, uint rotationState, uint cellSize, COLOUR colour, Position (*shape)[4]);
    void draw();
    void move(int rows, int columns);
    Position getPosition();
    Position* getShape();
    void rotate(Direction dir);
};