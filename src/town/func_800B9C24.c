#include "common.h"

/* Clear a 128 by 128 grid of signed halfwords. */
void func_800B7384(s16 *grid) {
    s16 *cell;
    s16 next_row;
    s16 next_column;
    s16 row;
    s16 column;

    cell = grid;
    row = 0;
    do {
        column = 0;
loop_2:
        *cell = 0;
        next_column = column + 1;
        column = next_column;
        cell += 1;
        if (next_column < 0x80) {
            goto loop_2;
        }
        next_row = row + 1;
        row = next_row;
    } while (next_row < 0x80);
}
