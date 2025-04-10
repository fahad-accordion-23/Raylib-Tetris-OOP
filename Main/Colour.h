#ifndef COLOUR_H
#define COLOUR_H

#include <raylib.h>

const unsigned int TOTAL_COLOURS = 9;
enum COLOUR
{
    C_DARK_GREY,
    C_GREEN,
    C_RED,
    C_ORANGE,
    C_YELLOW,
    C_PURPLE,
    C_CYAN,
    C_BLUE,
    C_BLACK
};
extern Color COLOURS[TOTAL_COLOURS];
extern void initializeColours();

#endif