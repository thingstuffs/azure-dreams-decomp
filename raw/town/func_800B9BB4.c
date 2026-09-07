#include "common.h"

extern s16 D_80162004[];

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

/* MECHANISM: Frameless leaf with two signed-16-bit induction variables.
   A flat s16 table makes the row stride and element scaling explicit,
   while nested do-while loops preserve the retail increment/test CFG. */
