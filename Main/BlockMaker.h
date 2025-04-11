#pragma once
#include "Block.h"
#include <cstdlib>

class BlockMaker
{
private:
    static Position LShape[4][4];
    static Position JShape[4][4];
    static Position IShape[4][4];
    static Position TShape[4][4];
    static Position SShape[4][4];
    static Position ZShape[4][4];
    static Position OShape[4][4];
    uint cellSize;
    Position offset;

public:
    BlockMaker() = delete;
    BlockMaker(uint cellSize, Position offset = { 0, 0 });
    Block createLBlock();
    Block createJBlock();
    Block createIBlock();
    Block createTBlock();
    Block createSBlock();
    Block createZBlock();
    Block createOBlock();
    Block createRandomBlock();
};

