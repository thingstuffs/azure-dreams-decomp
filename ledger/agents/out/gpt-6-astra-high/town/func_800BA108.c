#include "common.h"

extern u16 D_80162004[];

/* Copies a width-and-height-prefixed block to the destination grid, skipping zero entries. */
void func_800B7868(s16 dst_x, s16 dst_y, u16 *src) {
    s16 next_row;
    s16 next_col;
    s16 row;
    s16 col;
    u16 height;
    u16 width;
    u16 entry;

    width = *src++;
    height = *src++;
    row = 0;
    while ((row << 0x10) < (height << 0x10)) {
        col = 0;
        while (col < (s16) width) {
            entry = *src;
            if (entry != 0) {
                D_80162004[((row + dst_y) << 7) + col + dst_x] = entry;
            }
            next_col = col + 1;
            col = next_col;
            src++;
        }
        next_row = row + 1;
        row = next_row;
    }
}
