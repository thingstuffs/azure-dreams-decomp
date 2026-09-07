#include "common.h"

#include "common.h"

extern void MoveImage(void *rect, s32 x, s32 y);

void func_8003AE28(s16 x, s16 y, s16 w, s16 h, s32 move_x, s32 move_y)
{
    s16 rect[4];

    rect[0] = x;
    rect[1] = y;
    rect[2] = w;
    rect[3] = h;
    MoveImage(rect, move_x, move_y);
}
