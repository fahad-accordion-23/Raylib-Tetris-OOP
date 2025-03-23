#pragma once

#include "Colour.h"

typedef unsigned int uint;

const uint ROWS = 20;
const uint COLS = 10;

class Grid
{
private:
    uint cellSize;

public:
    COLOUR grid[ROWS][COLS];

    Grid(uint windowWidth, uint windowHeight);
    void initialize();
    uint getCellSize();
    void draw();
};

