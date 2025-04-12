#pragma once

#include <iostream>
#include <raylib.h>
#include "Position.h"
#include "Colour.h"

class ScoreBoard
{
private:
    // Interface positioning
    Rectangle foregroundRectangle, backgroundRectangle;
    uint width, height;
    uint padding;

    // Text label
    Font font;
    uint size, spacing;
    Position labelOffset;

    // Score label
    Position scoreOffset;
    uint score;

public:
    ScoreBoard();
    ~ScoreBoard();

    void initialize(Position offset, uint width, uint height);
    void draw();
    void addScore(uint score);
    uint getScore();
    void reset();
};

