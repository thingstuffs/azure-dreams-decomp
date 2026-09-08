#include "common.h"

/* Clears a 128 by 128 buffer of 16-bit values. */
void func_800B7384(s16 *buffer) {
    s16 *cell;
    s16 next_row;
    s16 next_col;
    s16 row;
    s16 col;

    cell = buffer;
    row = 0;
    do {
        col = 0;
clear_cell:
        *cell = 0;
        next_col = col + 1;
        col = next_col;
        cell += 1;
        if (next_col < 0x80) {
            goto clear_cell;
        }
        next_row = row + 1;
        row = next_row;
    } while (next_row < 0x80);
}
