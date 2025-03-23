#pragma once
#include <raylib.h>

#ifdef DARK_GREY
#undef DARK_GREY
#endif // DARK_GREY

#ifdef GREEN
#undef GREEN
#endif // GREEN

#ifdef RED
#undef RED
#endif // RED

#ifdef ORANGE
#undef ORANGE
#endif // ORANGE

#ifdef YELLOW
#undef YELLOW
#endif // YELLOW

#ifdef PURPLE
#undef PURPLE
#endif // PURPLE

#ifdef CYAN
#undef CYAN
#endif // CYAN

#ifdef BLUE
#undef BLUE
#endif // BLUE

#ifdef BLACK
#undef BLACK
#endif BLACK

/* Order of colours stored */
enum COLOUR
{
    DARK_GREY,
    GREEN,
    RED,
    ORANGE,
    YELLOW,
    PURPLE,
    CYAN,
    BLUE,
    BLACK
};

/* Colour data */
extern const Color COLOURS[9];