#include "Game.h"

Game::Game()
    : grid(WIDTH, HEIGHT), blockMaker(grid.getCellSize())
{
    std::srand(time(NULL));
    InitWindow(WIDTH, HEIGHT, "Raylib Tetris");
    SetTargetFPS(FPS);
    initializeColours();
}

void Game::run()
{
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(COLOURS[C_BLACK]);
        grid.draw();

        EndDrawing();
    }

    CloseWindow();
}