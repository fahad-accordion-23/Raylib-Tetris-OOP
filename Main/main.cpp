#include <raylib.h>
#include <cstdlib>
#include <time.h>
#include "Colour.h"
#include "Grid.h"
#include "BlockMaker.h"

typedef unsigned int uint;

constexpr uint
WIDTH = 450,
HEIGHT = 900,
FPS = 60;    

int main()
{
    std::srand(time(NULL));
    // Window init
    InitWindow(WIDTH, HEIGHT, "Raylib Tetris");
    SetTargetFPS(FPS);

    // Objects init
    initializeColours();
    Grid grid = Grid(WIDTH, HEIGHT);
    BlockMaker bmaker(grid.getCellSize());
    Block myBlock = bmaker.createRandomBlock();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(COLOURS[C_BLACK]);
        grid.draw();
        myBlock.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}