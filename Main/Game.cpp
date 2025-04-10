#include "Game.h"
#include <iostream>

bool Game::isBlockColliding()
{
    Position pos[4];
    for (uint i = 0; i < 4; i += 1)
    {
        pos[i].x = currentBlock.getShape()[i].x + currentBlock.getPosition().x;
        pos[i].y = currentBlock.getShape()[i].y + currentBlock.getPosition().y;

        if (pos[i].y < 0 || pos[i].y >= ROWS || pos[i].x >= COLS || pos[i].x < 0)
        {
            return true;
        }
        else if (grid.grid[pos[i].y][pos[i].x] != C_DARK_GREY)
        {
            return true;
        }
    }

    return false;
}

Game::Game()
    : grid(WIDTH, HEIGHT), blockMaker(grid.getCellSize()), softDropDelay(300), hardDropDelay(100), moveDelay(150), rotateDelay(200)
{
    std::srand(time(NULL));
    InitWindow(WIDTH, HEIGHT, "Raylib Tetris");
    SetTargetFPS(FPS);
    initializeColours();
    createRandomBlock();

    lastDropTime = Clock::now() - hardDropDelay;
    lastMoveTime = Clock::now() - moveDelay;
    lastRotateTime = Clock::now() - rotateDelay;
}

void Game::handleEvents()
{
    TimePoint now = Clock::now();
    Milliseconds elapsedSinceLastDrop = std::chrono::duration_cast<Milliseconds>(now - lastDropTime);
    Milliseconds elapsedSinceLastMove = std::chrono::duration_cast<Milliseconds>(now - lastMoveTime);
    Milliseconds elapsedSinceLastRotate = std::chrono::duration_cast<Milliseconds>(now - lastRotateTime);

    if (IsKeyDown(KEY_LEFT))
    {
        if (elapsedSinceLastMove >= moveDelay)
        {
            moveBlock(Direction::LEFT);
            lastMoveTime = now;
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        if (elapsedSinceLastMove >= moveDelay)
        {
            moveBlock(Direction::RIGHT);
            lastMoveTime = now;
        }
    }

    if (IsKeyDown(KEY_UP))
    {
        if (elapsedSinceLastRotate >= rotateDelay)
        {
            rotateBlock(Direction::LEFT);
            lastRotateTime = now;
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        if (elapsedSinceLastRotate >= rotateDelay)
        {
            rotateBlock(Direction::RIGHT);
            lastRotateTime = now;
        }
    }

    if (IsKeyDown(KEY_SPACE))
    {
        while (elapsedSinceLastDrop >= hardDropDelay)
        {
            moveBlock(Direction::DOWN);
            lastDropTime = now;
            elapsedSinceLastDrop = std::chrono::duration_cast<Milliseconds>(now - lastDropTime);
        }
    }
    else
    {
        if (elapsedSinceLastDrop >= softDropDelay)
        {
            moveBlock(Direction::DOWN);
            lastDropTime = now;
        }
    }
}

void Game::run()
{
    TimePoint start;
    Milliseconds elapsed;
    int frames = 0;

    start = Clock::now();
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(COLOURS[C_BLACK]);
        grid.draw();
        handleEvents();
        currentBlock.draw();

        EndDrawing();
        frames++;

        elapsed = std::chrono::duration_cast<Milliseconds>(Clock::now() - start);
        if (elapsed >= Milliseconds(1000))
        {
            std::cout << frames << " frames per second" << std::endl;
            start = Clock::now();
            frames = 0;
        }
    }

    CloseWindow();
}

void Game::createRandomBlock()
{
    currentBlock = blockMaker.createLBlock();
}

void Game::moveBlock(Direction dir)
{
    bool isColliding = false;

    if (dir == Direction::LEFT)
        currentBlock.move(-1, 0);
    else if (dir == Direction::RIGHT)
        currentBlock.move(+1, 0);
    else if (dir == Direction::UP)
        currentBlock.move(0, -1);
    else if (dir == Direction::DOWN)
        currentBlock.move(0, +1);

    if (isBlockColliding())
    {
        if (dir == Direction::LEFT)
            currentBlock.move(+1, 0);
        else if (dir == Direction::RIGHT)
            currentBlock.move(-1, 0);
        else if (dir == Direction::UP)
            currentBlock.move(0, +1);
        else if (dir == Direction::DOWN)
            currentBlock.move(0, -1);
    }
}

void Game::rotateBlock(Direction dir)
{
    if (dir == Direction::LEFT)
        currentBlock.rotate(Direction::LEFT);
    else if (dir == Direction::RIGHT)
        currentBlock.rotate(Direction::RIGHT);

    if (isBlockColliding())
    {
        if (dir == Direction::LEFT)
            currentBlock.rotate(Direction::RIGHT);
        else if (dir == Direction::RIGHT)
            currentBlock.rotate(Direction::LEFT);
    }
}
