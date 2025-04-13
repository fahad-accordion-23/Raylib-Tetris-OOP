#pragma once

#include <raylib.h>
#include <cstdlib>
#include <chrono>
#include "Colour.h"
#include "Grid.h"
#include "BlockMaker.h"
#include "ScoreBoard.h"

typedef unsigned int uint;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;
typedef std::chrono::milliseconds MS;
using std::chrono::duration_cast;

constexpr uint
WIDTH = 450,
HEIGHT = 900,
PADDING = 20,
WINDOW_WIDTH = WIDTH * 1.75f + PADDING + PADDING,
WINDOW_HEIGHT = HEIGHT + PADDING + PADDING,
FPS = 60;

enum
{
    CURRENT,
    NEXT_1,
    NEXT_2,
    NEXT_3
};

class Game
{
private:
    Grid grid;
    BlockMaker blockMaker;
    Block blocks[4];
    TimePoint lastDropTime, lastMoveTime, lastRotateTime, lastTouchDownTime;
    MS softDropDelay, hardDropDelay, moveDelay, rotateDelay, lockDelay;
    ScoreBoard scoreBoard;
    bool hasBottomCollided;
    bool gameOver;

    bool bottomCollision();
    bool isBlockColliding();
    void createBlock();
    void moveBlock(Direction dir);
    bool blockLockCheck();
    void lockBlock();
    void rotateBlock(Direction dir);
    void handleEvents();
    uint clearLines();

public:
    Game();
    void run();
};

