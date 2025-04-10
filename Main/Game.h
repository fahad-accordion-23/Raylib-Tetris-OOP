#pragma once

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

class Game
{
private:
    Grid grid;
    BlockMaker blockMaker;
    Block block;

public:
    Game();

    void run();

};

