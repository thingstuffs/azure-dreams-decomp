#include "common.h"

typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern u8 D_8053019C[][12];
extern void func_8006E91C(Rect *, s32, s32);

/* Draws a wrapped tile column with vertical scrolling and top-edge clipping. */
void func_80812A2C(s16 column, s16 row, s16 scroll_y)
{
    Rect rect;
    s32 row_offset;
    s32 top_offset;
    s32 draw_x;
    s32 draw_y;
    s16 row_base;
    s32 tile_id;

    row_base = row + 12;
    draw_x = (column << 4) + 384;

    rect.w = 16;
    rect.h = 32;

    for (row_offset = -1; row_offset < 3; row_offset++) {
        if (row_offset >= 0 || scroll_y != 0) {
            tile_id = D_8053019C[column][(row_base + row_offset) % 12];
            rect.x = ((tile_id & 3) << 4) + 384;
            rect.y = (tile_id >> 2) << 5;
            top_offset = ((2 - row_offset) << 5) - scroll_y;
            draw_y = top_offset + 128;
            if (top_offset < 0) {
                rect.y -= top_offset;
                rect.h = top_offset + 32;
                draw_y = 128;
            }
            func_8006E91C(&rect, draw_x, draw_y);
        }
    }
}
