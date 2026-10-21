#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"

/* Fill a video-memory rectangle with the specified color. */
void fill_vram_rect(s16 x, s16 y, s16 width, s16 height, u8 red, u8 green, u8 blue)
{
    s16 rect[4];

    rect[0] = x;
    rect[1] = y;
    rect[2] = width;
    rect[3] = height;
    ClearImage(rect, red, green, blue);
}
