#include "common.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "sdk/libgpu.h"

typedef struct {
    s16 x, y, w, h;
} S_8004846C_RECT;

/* Reads a 16x1 VRAM tile and redraws it at tile index minus 0x80. */
s32 copy_processed_vram_tile_backward(s32 tile_index)
{
    S_8004846C_RECT rect;
    s32 pixels[8];

    rect.x = (tile_index & 0x3F) << 4;
    rect.y = tile_index >> 6;
    rect.w = 0x10;
    rect.h = 1;
    StoreImage(&rect, pixels);
    DrawSync(0);
    mark_palette_colors_with_high_bit((s32)pixels, 1, 0);
    upload_vram_row_and_cache((s32)pixels, tile_index - 0x80, 1, 2);
    return DrawSync(0);
}
