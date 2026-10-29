#include "common.h"
#include "town/map.h"

/* Blit nonzero pixels using source header offsets and a 128-pixel destination stride. */
void blit_origin_u16_block(s32 dst_x, s32 dst_y, u16 *src, void *dst) {
    register s16 col;
    register s16 row;
    u16 height;
    u16 width;
    u16 y_offset;
    u16 offset_or_pixel;

    width = *src++;
    height = *src++;
    offset_or_pixel = *src++;
    y_offset = *src++;
    row = 0;
    dst_x -= offset_or_pixel;
    dst_y -= y_offset;
    row = 0;
    while ((row << 0x10) < (height << 0x10)) {
        col = 0;
        while (col < (s16) width) {
            offset_or_pixel = *src;
            if (offset_or_pixel != 0) {
                ((u16 *) dst)[((row + (s16) dst_y) << 7) + col + (s16) dst_x] = offset_or_pixel;
            }
            src++;
            col++;
        }
        row++;
    }
}
