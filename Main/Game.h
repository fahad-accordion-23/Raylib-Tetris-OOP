#pragma once

#include <raylib.h>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include "Colour.h"
#include "Grid.h"
#include "BlockMaker.h"

typedef unsigned int uint;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;
typedef std::chrono::milliseconds Milliseconds;

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
    TimePoint lastDropTime, lastMoveTime, lastRotateTime;
    Milliseconds softDropDelay, hardDropDelay, moveDelay, rotateDelay;

    bool isBlockColliding();
public:
    Game();

    void handleEvents();
    void run();
    void createRandomBlock();
    void moveBlock(Direction dir);
    void rotateBlock(Direction dir);
};

