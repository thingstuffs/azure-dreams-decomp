#include "common.h"

#include "engine/movie.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"

/* --- port/hal accessor shims (mechanical, no HAL dependency) --- */
#define PVAL(p)     ((u32)(p))

/*
 * Uploads pixel data to the specified VRAM rectangle.
 *
 * port body: port/hal/resident_gap2.c:632
 */
void upload_pixel_rectangle(s16 x, s16 y, s16 width, s16 height, const void *pixels)
{
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    LoadImage(&rect, pixels);
}
