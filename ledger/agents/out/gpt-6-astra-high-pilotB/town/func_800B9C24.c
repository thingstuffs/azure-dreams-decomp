#include "common.h"

/* Clears a 128 by 128 array of signed 16-bit values. */
void func_800B7384(s16 *buffer) {
    s16 *cursor;
    s16 next_row;
    s16 next_column;
    s16 row;
    s16 column;

    cursor = buffer;
    row = 0;
    do {
        column = 0;
loop_2:
        *cursor = 0;
        next_column = column + 1;
        column = next_column;
        cursor += 1;
        if (next_column < 0x80) {
            goto loop_2;
        }
        next_row = row + 1;
        row = next_row;
    } while (next_row < 0x80);
}
