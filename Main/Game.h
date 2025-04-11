#pragma once

#include <raylib.h>
#include <cstdlib>
#include <chrono>
#include "Colour.h"
#include "Grid.h"
#include "BlockMaker.h"

typedef unsigned int uint;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;
typedef std::chrono::milliseconds MS;
using std::chrono::duration_cast;

constexpr uint
WIDTH = 450,
HEIGHT = 900,
FPS = 60;

class Game
{
private:
    Grid grid;
    BlockMaker blockMaker;
    Block currentBlock;
    TimePoint lastDropTime, lastMoveTime, lastRotateTime, lastTouchDownTime;
    MS softDropDelay, hardDropDelay, moveDelay, rotateDelay, lockDelay;
    bool hasBottomCollided;
    bool gameOver;

    bool bottomCollision();
    bool isBlockColliding();
    void createRandomBlock();
    void moveBlock(Direction dir);
    bool blockLockCheck();
    void lockBlock();
    void rotateBlock(Direction dir);
    void handleEvents();
    bool clearLines();

public:
    Game();
    void run();
};

