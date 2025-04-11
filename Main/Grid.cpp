#include "Grid.h"

Grid::Grid(uint windowWidth, uint windowHeight, Position position)
    : position(position)
{
    float w2h = (float)windowWidth / windowHeight;
    float c2r = (float)COLS / ROWS;

    if (w2h > c2r)
        cellSize = windowHeight / ROWS;
    else
        cellSize = windowWidth / COLS;

    initialize();
}

void Grid::setPosition(Position position)
{
    this->position = position;
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
    DrawRectangle(position.x, position.y, cellSize * COLS, cellSize * ROWS, COLOURS[C_BLACK]);
    for (uint j = 0; j < ROWS; j += 1)
        for (uint i = 0; i < COLS; i += 1)
        {
            COLOUR cellColour = grid[j][i];
            DrawRectangle(i * cellSize + 1 + position.x, j * cellSize + 1 + position.y, cellSize - 1, cellSize - 1, COLOURS[cellColour]);
        }
}
