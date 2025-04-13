#pragma once

#include <iostream>
#include <raylib.h>
#include "Position.h"
#include "Colour.h"

class ScoreBoard
{
private:
    // Interface positioning
    Rectangle foregroundRectangle, backgroundRectangle, nextRectangle;
    uint width, height;
    uint padding;

    // Text label
    Font font;
    uint size, spacing;
    Position scoreLabelOffset;

    // Score label
    Position scoreValueLabelOffset;
    uint score;

    // Next label
    Position nextLabelOffset;

public:
    ScoreBoard();
    ~ScoreBoard();

    void initialize(Position offset, uint width, uint height);
    void draw();
    void addScore(uint score);
    uint getScore();
    void reset();
};

