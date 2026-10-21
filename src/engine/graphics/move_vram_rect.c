#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"

/* Moves a VRAM rectangle to the specified destination coordinates. */
void move_vram_rect(s16 x, s16 y, s16 width, s16 height, s32 move_x, s32 move_y)
{
    s16 rect[4];

    rect[0] = x;
    rect[1] = y;
    rect[2] = width;
    rect[3] = height;
    MoveImage(rect, move_x, move_y);
}
