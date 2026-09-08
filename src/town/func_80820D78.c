#include "common.h"

typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void func_800673A0(Rect *rect, s32 x, s32 width);
extern u8 D_800244B8[][12];

/* Draws a scrolling column of tiles, clipping at the top edge. */
void func_80023578(s16 column, s16 tile_index, s16 scroll_y)
{
    Rect rect;
    s32 dest_x;
    s16 base_index;
    s16 src_y;
    s32 row_y;
    s32 dest_y;
    s32 row;
    s32 tile;

    base_index = tile_index + 0xC;
    dest_x = (column * 0x10) + 0x180;
    row = -1;
    rect.w = 0x10;
    rect.h = 0x20;
    do {
        if ((row >= 0) || (scroll_y != 0)) {
            tile = D_800244B8[column][(base_index + row) % 12];
            row_y = ((2 - row) << 5) - scroll_y;
            dest_y = row_y + 0x80;
            rect.x = ((tile & 3) * 0x10) + 0x180;
            src_y = ((s32) tile >> 2) << 5;
            rect.y = src_y;
            if (row_y < 0) {
                dest_y = 0x80;
                rect.y = src_y - row_y;
                rect.h = row_y + 0x20;
            }
            func_800673A0(&rect, dest_x, dest_y);
        }
        row += 1;
    } while (row < 3);
}
