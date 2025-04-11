#pragma once

#include "Colour.h"
#include "Position.h"
typedef unsigned int uint;

enum class Direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

class Block
{
protected:
    uint cellSize;
    uint rotationState;
    COLOUR colour;
    const Position (*shape)[4];
    Position position;

public:
    Block();
    Block(Position position, uint rotationState, uint cellSize, COLOUR colour, Position (*shape)[4]);
    void draw();
    void move(int columns, int rows);
    Position getPosition();
    const Position* getShape();
    void rotate(Direction dir);
    COLOUR getColour();
};