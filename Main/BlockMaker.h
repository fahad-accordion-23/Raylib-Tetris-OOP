#pragma once
#include "Block.h"

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

public:
    BlockMaker() = delete;
    BlockMaker(uint cellSize);
    Block createLBlock();
    Block createJBlock();
    Block createIBlock();
    Block createTBlock();
    Block createSBlock();
    Block createZBlock();
    Block createOBlock();
    Block createRandomBlock();
};

