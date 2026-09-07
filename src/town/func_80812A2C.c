#include "common.h"

typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern u8 D_8053019C[][12];
extern void func_8006E91C(Rect *, s32, s32);

void func_80812A2C(s16 arg0, s16 arg1, s16 arg2)
{
    Rect rect;
    s32 i;
    s32 edge;
    s32 draw_x;
    s32 draw_width;
    s16 wrapped;
    s32 cell;

    wrapped = arg1 + 12;
    draw_x = (arg0 << 4) + 384;

    rect.w = 16;
    rect.h = 32;

    for (i = -1; i < 3; i++) {
        if (i >= 0 || arg2 != 0) {
            cell = D_8053019C[arg0][(wrapped + i) % 12];
            rect.x = ((cell & 3) << 4) + 384;
            rect.y = (cell >> 2) << 5;
            edge = ((2 - i) << 5) - arg2;
            draw_width = edge + 128;
            if (edge < 0) {
                rect.y -= edge;
                rect.h = edge + 32;
                draw_width = 128;
            }
            func_8006E91C(&rect, draw_x, draw_width);
        }
    }
}
