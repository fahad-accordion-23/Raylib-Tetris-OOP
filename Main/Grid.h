#pragma once

#include "Colour.h"
#include "Position.h"

typedef unsigned int uint;

const uint ROWS = 20;
const uint COLS = 10;

class Grid
{
private:
    uint cellSize;
    Position position;

public:
    COLOUR grid[ROWS][COLS];

    Grid(uint windowWidth, uint windowHeight, Position position);
    void setPosition(Position position);
    void initialize();
    uint getCellSize();
    void draw();
};

