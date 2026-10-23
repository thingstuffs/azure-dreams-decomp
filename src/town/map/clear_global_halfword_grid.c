#include "common.h"

extern s16 town_tile_grid[];

/* Clears all entries in the 128-by-128 table. */
void clear_global_halfword_grid_128(void) {
    s16 row;
    s16 column;

    row = 0;
    do {
        column = 0;
        do {
            town_tile_grid[(row * 128) + column] = 0;
            column++;
        } while (column < 128);
        row++;
    } while (row < 128);
}
