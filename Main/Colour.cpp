#include "Colour.h"

Color COLOURS[TOTAL_COLOURS];
void initializeColours()
{
    COLOURS[C_DARK_GREY] = { 26, 31, 40, 255 };
    COLOURS[C_GREEN] = { 47, 230, 23, 255 };   
    COLOURS[C_RED] = { 232, 18, 18, 255 };     
    COLOURS[C_ORANGE] = { 226, 116, 17, 255 }; 
    COLOURS[C_YELLOW] = { 237, 234, 4, 255 };  
    COLOURS[C_PURPLE] = { 166, 0, 247, 255 };  
    COLOURS[C_CYAN] = { 21, 204, 209, 255 };   
    COLOURS[C_BLUE] = { 13, 64, 216, 255 };
    COLOURS[C_DARK_EGGPLANT_PURPLE] = { 49, 0, 26, 255 };
    COLOURS[C_EGGPLANT_PURPLE] = { 77, 20, 41, 255 };
    COLOURS[C_PURPLE_PINK] = { 102, 0, 54, 255 };
    COLOURS[C_BLACK] = { 0, 0, 0, 255 };
}