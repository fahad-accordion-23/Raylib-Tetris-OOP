#include "Grid.h"

Grid::Grid(uint windowWidth, uint windowHeight)
{
    float w2h = (float)windowWidth / windowHeight;
    float c2r = (float)COLS / ROWS;

    if (w2h > c2r)
        cellSize = windowHeight / ROWS;
    else
        cellSize = windowWidth / COLS;

    initialize();
}

void Grid::initialize()
{
    for (uint j = 0; j < ROWS; j += 1)
        for (uint i = 0; i < COLS; i += 1)
            grid[j][i] = COLOUR::C_DARK_GREY;
}

uint Grid::getCellSize()
{
    return cellSize;
}

void Grid::draw()
{
    for (uint j = 0; j < ROWS; j += 1)
        for (uint i = 0; i < COLS; i += 1)
        {
            COLOUR cellColour = grid[j][i];
            DrawRectangle(i * cellSize + 1, j * cellSize + 1, cellSize - 1, cellSize - 1, COLOURS[cellColour]);
        }
}
