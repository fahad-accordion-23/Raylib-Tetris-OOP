#include "Game.h"
#include <iostream>

/* checks collision of the bottom of each of the 4 squares of the block 
 * with other cells and the bottom of the grid
 */
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
    MS elapsedSinceLastDrop = duration_cast<MS>(now - lastDropTime);
    MS elapsedSinceLastMove = duration_cast<MS>(now - lastMoveTime);
    MS elapsedSinceLastRotate = duration_cast<MS>(now - lastRotateTime);

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
            elapsedSinceLastDrop = duration_cast<MS>(now - lastDropTime);
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

uint Game::clearLines()
{
    uint cleared = 0;
    bool completeRows[20] = { 0 };
    for (int j = ROWS - 1; j >= 0; j -= 1)
    {
        completeRows[j] = true;
        for (uint i = 0; i < COLS; i += 1)
        {
            if (grid.grid[j][i] == C_DARK_GREY)
            {
                completeRows[j] = false;
                break;
            }
        }

        if (completeRows[j])
            cleared += 1;
    }

    for (int j = ROWS - 1, n = ROWS - 2; n >= 0 && j >= 0; )
    {
        if (completeRows[j])
        {
            if (completeRows[n])
                n -= 1;
            else
            {
                for (uint i = 0; i < COLS; i += 1)
                    grid.grid[j][i] = grid.grid[n][i];
                j -= 1;
                completeRows[n] = true;
            }
        }
        else
        {
            j -= 1;
            n -= 1;
        }
    }

    return cleared;
}

void Game::createRandomBlock()
{
    currentBlock = blockMaker.createRandomBlock();
}

void Game::moveBlock(Direction dir)
{
    if (dir == Direction::LEFT)
        currentBlock.move(-1, 0);
    else if (dir == Direction::RIGHT)
        currentBlock.move(+1, 0);
    else if (dir == Direction::UP)
        currentBlock.move(0, -1);
    else if (dir == Direction::DOWN && !bottomCollision())
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

bool Game::blockLockCheck()
{
    if (bottomCollision())
    {
        if (!hasBottomCollided)
        {
            lastTouchDownTime = Clock::now();
            hasBottomCollided = true;
        }

        MS beenTouchingFor = duration_cast<MS>(Clock::now() - lastTouchDownTime);
        if (beenTouchingFor >= lockDelay)
        {
            return true;
        }
    }
    else
        return false;
}

void Game::lockBlock()
{
    for (uint i = 0; i < 4; i += 1)
    {
        Position pos = currentBlock.getShape()[i];
        pos.y += currentBlock.getPosition().y;
        pos.x += currentBlock.getPosition().x;
        grid.grid[pos.y][pos.x] = currentBlock.getColour();
    }
    hasBottomCollided = false;
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
    : grid(WIDTH, HEIGHT, { PADDING, PADDING }), blockMaker(grid.getCellSize(), { PADDING, PADDING }), 
    softDropDelay(300), hardDropDelay(100), moveDelay(150), rotateDelay(200), 
    lockDelay(500), hasBottomCollided(false)
{
    std::srand(Clock::now().time_since_epoch().count());
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib Tetris");
    SetTargetFPS(FPS);
    initializeColours();
    createRandomBlock();

    scoreBoard.initialize(
        { PADDING + WIDTH + PADDING, PADDING },
        WINDOW_WIDTH - PADDING - WIDTH - PADDING - PADDING,
        WINDOW_HEIGHT - PADDING - PADDING
    );

    lastDropTime = Clock::now() - hardDropDelay;
    lastMoveTime = Clock::now() - moveDelay;
    lastRotateTime = Clock::now() - rotateDelay;
}

void Game::run()
{
    TimePoint start;
    MS elapsed;
    uint frames = 0;

    start = Clock::now();
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(COLOURS[C_DARK_EGGPLANT_PURPLE]);
        scoreBoard.addScore(clearLines() * 100);
        grid.draw();
        scoreBoard.draw();
        if (!gameOver)
        {
            handleEvents();
            if (blockLockCheck())
            {
                lockBlock();
                createRandomBlock();
                if (isBlockColliding())
                {
                    gameOver = true;
                    lockBlock();
                }
            }
            currentBlock.draw();
        }

        EndDrawing();
        frames++;

        elapsed = duration_cast<MS>(Clock::now() - start);
        if (elapsed >= MS(1000))
        {
            std::cout << frames << " frames per second" << std::endl;
            start = Clock::now();
            frames = 0;
        }
    }

    CloseWindow();
}