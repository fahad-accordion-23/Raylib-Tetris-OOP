#include "BlockMaker.h"

Position BlockMaker::LShape[4][4] = {
    {Position{0, 0}, Position{0, 1}, Position{0, 2}, Position{1, 2}},
    {Position{0, 1}, Position{1, 1}, Position{2, 1}, Position{2, 0}},
    {Position{0, 0}, Position{1, 0}, Position{1, 1}, Position{1, 2}},
    {Position{0, 0}, Position{0, 1}, Position{1, 0}, Position{2, 0}} 
};

Position BlockMaker::JShape[4][4] = {
    {Position{0, 0}, Position{0, 1}, Position{0, 2}, Position{1, 0}},
    {Position{0, 0}, Position{1, 0}, Position{2, 0}, Position{2, 1}},
    {Position{0, 2}, Position{1, 0}, Position{1, 1}, Position{1, 2}},
    {Position{0, 0}, Position{0, 1}, Position{1, 1}, Position{2, 1}} 
};

Position BlockMaker::IShape[4][4] = {
    {Position{0, 0}, Position{0, 1}, Position{0, 2}, Position{0, 3}},
    {Position{0, 0}, Position{1, 0}, Position{2, 0}, Position{3, 0}},
    {Position{0, 0}, Position{0, 1}, Position{0, 2}, Position{0, 3}},
    {Position{0, 0}, Position{1, 0}, Position{2, 0}, Position{3, 0}} 
};

Position BlockMaker::TShape[4][4] = {
    {Position{0, 1}, Position{1, 0}, Position{1, 1}, Position{1, 2}},
    {Position{0, 0}, Position{1, 0}, Position{1, 1}, Position{2, 0}},
    {Position{0, 0}, Position{0, 1}, Position{0, 2}, Position{1, 1}},
    {Position{0, 1}, Position{1, 0}, Position{1, 1}, Position{2, 1}} 
};

Position BlockMaker::SShape[4][4] = {
    {Position{0, 1}, Position{0, 2}, Position{1, 0}, Position{1, 1}},
    {Position{0, 0}, Position{1, 0}, Position{1, 1}, Position{2, 1}},
    {Position{0, 1}, Position{0, 2}, Position{1, 0}, Position{1, 1}},
    {Position{0, 0}, Position{1, 0}, Position{1, 1}, Position{2, 1}} 
};

Position BlockMaker::ZShape[4][4] = {
    {Position{0, 0}, Position{0, 1}, Position{1, 1}, Position{1, 2}},
    {Position{0, 1}, Position{1, 0}, Position{1, 1}, Position{2, 0}},
    {Position{0, 0}, Position{0, 1}, Position{1, 1}, Position{1, 2}},
    {Position{0, 1}, Position{1, 0}, Position{1, 1}, Position{2, 0}} 
};

Position BlockMaker::OShape[4][4] = {
    {Position{0, 0}, Position{0, 1}, Position{1, 0}, Position{1, 1}},
    {Position{0, 0}, Position{0, 1}, Position{1, 0}, Position{1, 1}},
    {Position{0, 0}, Position{0, 1}, Position{1, 0}, Position{1, 1}},
    {Position{0, 0}, Position{0, 1}, Position{1, 0}, Position{1, 1}} 
};

BlockMaker::BlockMaker(uint cellSize)
    : cellSize(cellSize)
{
}

Block BlockMaker::createLBlock() {
    return Block({ 3, 0 }, 0, cellSize, COLOUR::C_ORANGE, LShape);
}

Block BlockMaker::createJBlock() {
    return Block({ 3, 0 }, 0, cellSize, COLOUR::C_BLUE, JShape);
}

Block BlockMaker::createIBlock() {
    return Block({ 3, 0 }, 0, cellSize, COLOUR::C_CYAN, IShape);
}

Block BlockMaker::createTBlock() {
    return Block({ 3, 0 }, 0, cellSize, COLOUR::C_PURPLE, TShape);
}

Block BlockMaker::createSBlock() {
    return Block({ 3, 0 }, 0, cellSize, COLOUR::C_GREEN, SShape);
}

Block BlockMaker::createZBlock() {
    return Block({ 3, 0 }, 0, cellSize, COLOUR::C_RED, ZShape);
}

Block BlockMaker::createOBlock() {
    return Block({ 4, 0 }, 0, cellSize, COLOUR::C_YELLOW, OShape);
}

Block BlockMaker::createRandomBlock() 
{
    int type = rand() % 7;
    switch (type) {
    case 0: return createLBlock();
    case 1: return createJBlock();
    case 2: return createIBlock();
    case 3: return createTBlock();
    case 4: return createSBlock();
    case 5: return createZBlock();
    case 6: return createOBlock();
    default: return createLBlock();
    }
}
