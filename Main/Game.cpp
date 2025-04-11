#include "Game.h"
#include <iostream>

// checks collision of the bottom of each of the 4 squares of the block with other cells and the bottom of the grid
bool Game::bottomCollision()
{
    Position pos;
    for (uint i = 0; i < 4; i += 1)
    {
        pos.x = currentBlock.getShape()[i].x + currentBlock.getPosition().x;
        pos.y = currentBlock.getShape()[i].y + currentBlock.getPosition().y;
        if (pos.y >= ROWS - 1 || grid.grid[pos.y + 1][pos.x] != C_DARK_GREY)
        {
            return true;
        }
    }
    return false;
}

bool Game::isBlockColliding()
{
    Position pos;
    for (uint i = 0; i < 4; i += 1)
    {
        pos.x = currentBlock.getShape()[i].x + currentBlock.getPosition().x;
        pos.y = currentBlock.getShape()[i].y + currentBlock.getPosition().y;
        if (pos.y < 0 || pos.y >= ROWS || pos.x >= COLS || pos.x < 0)
        {
            return true;
        }
        if (grid.grid[pos.y][pos.x] != C_DARK_GREY)
        {
            return true;
        }
    }
    return false;
}

void Game::handleEvents()
{
    TimePoint now = Clock::now();
    Milliseconds elapsedSinceLastDrop = duration_cast<Milliseconds>(now - lastDropTime);
    Milliseconds elapsedSinceLastMove = duration_cast<Milliseconds>(now - lastMoveTime);
    Milliseconds elapsedSinceLastRotate = duration_cast<Milliseconds>(now - lastRotateTime);

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
            elapsedSinceLastDrop = duration_cast<Milliseconds>(now - lastDropTime);
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

void Game::createRandomBlock()
{
    currentBlock = blockMaker.createRandomBlock();
}

void Game::moveBlock(Direction dir)
{
    bool isBottomColliding = bottomCollision();
    if (isBottomColliding)
    {
        if (!hasBottomCollided)
        {
            lastTouchDownTime = Clock::now();
            hasBottomCollided = true;
        }

        Milliseconds beenTouchingFor = duration_cast<Milliseconds>(Clock::now() - lastTouchDownTime);
        if (beenTouchingFor >= lockDelay)
        {
            for (uint i = 0; i < 4; i += 1)
            {
                Position pos = currentBlock.getShape()[i];
                grid.grid[pos.y + currentBlock.getPosition().y][pos.x + currentBlock.getPosition().x] = currentBlock.getColour();
            }
            createRandomBlock();
            hasBottomCollided = false;
        }
    }
    else
        hasBottomCollided = false;

    if (dir == Direction::LEFT)
        currentBlock.move(-1, 0);
    else if (dir == Direction::RIGHT)
        currentBlock.move(+1, 0);
    else if (dir == Direction::UP)
        currentBlock.move(0, -1);
    else if (dir == Direction::DOWN && !isBottomColliding)
        currentBlock.move(0, +1);

    bool isCollidng = isBlockColliding();
    if (isCollidng)
    {
        if (dir == Direction::LEFT)
            currentBlock.move(+1, 0);
        else if (dir == Direction::RIGHT)
            currentBlock.move(-1, 0);
        else if (dir == Direction::UP)
            currentBlock.move(0, +1);
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

Game::Game()
    : grid(WIDTH, HEIGHT), blockMaker(grid.getCellSize()), softDropDelay(300),
    hardDropDelay(100), moveDelay(150), rotateDelay(200), lockDelay(500),
    hasBottomCollided(false)
{
    std::srand(Clock::now().time_since_epoch().count());
    InitWindow(WIDTH, HEIGHT, "Raylib Tetris");
    SetTargetFPS(FPS);
    initializeColours();
    createRandomBlock();

    lastDropTime = Clock::now() - hardDropDelay;
    lastMoveTime = Clock::now() - moveDelay;
    lastRotateTime = Clock::now() - rotateDelay;
}

void Game::run()
{
    TimePoint start;
    Milliseconds elapsed;
    uint frames = 0;

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

        elapsed = duration_cast<Milliseconds>(Clock::now() - start);
        if (elapsed >= Milliseconds(1000))
        {
            std::cout << frames << " frames per second" << std::endl;
            start = Clock::now();
            frames = 0;
        }
    }

    CloseWindow();
}