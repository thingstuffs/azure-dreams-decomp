#include "common.h"

extern s16 D_80162004[];

/* Clears all entries in the 128-by-128 table. */
void func_800B7314(void) {
    s16 row;
    s16 column;

    row = 0;
    do {
        column = 0;
        do {
            D_80162004[(row * 128) + column] = 0;
            column++;
        } while (column < 128);
        row++;
    } while (row < 128);
}
