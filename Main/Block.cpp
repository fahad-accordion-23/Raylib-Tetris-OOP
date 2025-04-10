#include "Block.h"

Block::Block()
    : position({0, 0}), cellSize(0), rotationState(0), colour(COLOUR::C_BLACK), shape(nullptr)
{
}

Block::Block(Position position, uint rotationState, uint cellSize, COLOUR colour, Position (*shape)[4])
    : position(position), cellSize(cellSize), rotationState(rotationState), colour(colour), shape(shape)
{
}

void Block::draw()
{
    for (uint i = 0; i < 4; i += 1)
    {
        uint x = shape[rotationState][i].x + position.x;
        uint y = shape[rotationState][i].y + position.y;
        DrawRectangle(x * cellSize + 1, y * cellSize + 1, cellSize - 1, cellSize - 1, COLOURS[colour]);
    }
}
void Block::move(int columns, int rows)
{
    position.x += columns;
    position.y += rows;
}

Position Block::getPosition()
{
    return position;
}

Position* Block::getShape()
{
    return shape[rotationState];
}

void Block::rotate(Direction dir)
{
    if (dir == LEFT)
    {
        rotationState -= 1;
        rotationState %= 4;
    }
    else if (dir == RIGHT)
    {
        rotationState += 1;
        rotationState %= 4;
    }
    else
        return;
}