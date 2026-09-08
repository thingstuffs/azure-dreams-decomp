#include "common.h"

#include "common.h"

extern void MoveImage(void *rect, s32 x, s32 y);

/* Moves a VRAM rectangle to the specified destination coordinates. */
void func_8003AE28(s16 x, s16 y, s16 width, s16 height, s32 move_x, s32 move_y)
{
    s16 rect[4];

    rect[0] = x;
    rect[1] = y;
    rect[2] = width;
    rect[3] = height;
    MoveImage(rect, move_x, move_y);
}
