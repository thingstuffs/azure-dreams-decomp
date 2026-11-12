#include "common.h"

#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"

/* Moves a VRAM rectangle to the specified destination coordinates. */
void move_vram_rect(s16 x, s16 y, s16 width, s16 height, s32 move_x, s32 move_y)
{
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    MoveImage(&rect, move_x, move_y);
}
