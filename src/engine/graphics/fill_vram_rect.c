#include "common.h"

#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"

/* Fill a video-memory rectangle with the specified color. */
void fill_vram_rect(s16 x, s16 y, s16 width, s16 height, u8 red, u8 green, u8 blue)
{
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    ClearImage(&rect, red, green, blue);
}
