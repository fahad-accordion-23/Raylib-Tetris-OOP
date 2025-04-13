#include "ScoreBoard.h"

void ScoreBoard::initialize(Position offset, uint width, uint height)
{
    // board
    padding = width * 0.10f;
    backgroundRectangle = Rectangle(offset.x, offset.y, width, height);
    foregroundRectangle = Rectangle(
        offset.x + padding, 
        offset.y + padding, 
        width - padding - padding, 
        height * 0.25f - padding
    );
    nextRectangle = Rectangle(
        foregroundRectangle.x,
        foregroundRectangle.y + foregroundRectangle.height + padding,
        foregroundRectangle.width,
        height * 0.75f - padding - padding
    );

    // score text label
    font = LoadFont("fonts/mecha.png");
    size = 50;
    spacing = 5;
    scoreLabelOffset = Position(
        foregroundRectangle.x + (foregroundRectangle.width - MeasureTextEx(font, "SCORE", size, spacing).x) / 2.0f,
        foregroundRectangle.y + padding
    );

    // score value 
    scoreValueLabelOffset = Position(
        0,
        foregroundRectangle.y + padding * 1.5f + MeasureTextEx(font, "SCORE", size, spacing).y
    );

    // next
    nextLabelOffset = Position(
        nextRectangle.x + (nextRectangle.width - MeasureTextEx(font, "NEXT", size, spacing).x) / 2.0f,
        nextRectangle.y + padding
    );
}

ScoreBoard::ScoreBoard()  
   : backgroundRectangle{0, 0, 0, 0},  
    foregroundRectangle{0, 0, 0, 0},  
    width(0),  
    height(0),  
    padding(0),  
    font{0},  
    size(0),  
    spacing(0),  
    scoreLabelOffset{0, 0},  
    scoreValueLabelOffset{0, 0},  
    score(0)  
{  
}

ScoreBoard::~ScoreBoard()
{
    UnloadFont(font);
}

void ScoreBoard::draw()
{
    DrawRectangleRounded(backgroundRectangle, 0.3, 6, COLOURS[C_EGGPLANT_PURPLE]);
    DrawRectangleRounded(foregroundRectangle, 0.3, 6, COLOURS[C_PURPLE_PINK]);
    DrawRectangleRounded(nextRectangle, 0.3, 6, COLOURS[C_PURPLE_PINK]);

    DrawTextEx(font, "SCORE", Vector2(scoreLabelOffset.x, scoreLabelOffset.y), size, spacing, COLOURS[C_GREEN]);
    DrawTextEx(font, "NEXT", Vector2(nextLabelOffset.x, nextLabelOffset.y), size, spacing, COLOURS[C_GREEN]);

    // score value label
    char valueText[10];
    sprintf_s(valueText, "%d", score);
    scoreValueLabelOffset.x = foregroundRectangle.x + (foregroundRectangle.width - MeasureTextEx(font, valueText, size, spacing).x) / 2.0f;
    DrawTextEx(font, valueText, Vector2(scoreValueLabelOffset.x, scoreValueLabelOffset.y), size, spacing, COLOURS[C_GREEN]);
}

void ScoreBoard::addScore(uint score)
{
    this->score += score;
}

uint ScoreBoard::getScore()
{
    return score;
}

void ScoreBoard::reset()
{
    score = 0;
}

