#ifndef COLOUR_H
#define COLOUR_H

#include <raylib.h>

const unsigned int TOTAL_COLOURS = 10;
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
    C_DARK_EGGPLANT_PURPLE,
    C_BLACK
};
extern Color COLOURS[TOTAL_COLOURS];
extern void initializeColours();

#endif