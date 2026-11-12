#include "common.h"
#include "engine/text.h"
#include "slus.h"
#include "sdk/libgpu_types.h"

/* Converts the selected rectangle to VRAM coordinates and dimensions. */
void get_glyph_vram_rectangle(s32 rect_id, RECT *vram_rect)
{
    u8 source_rect[4];

    decode_glyph_id_to_byte_rectangle(rect_id & 0xFF, source_rect);
    vram_rect->x = (source_rect[0] >> 2) + 0x3C0;
    vram_rect->y = source_rect[1] + 0x100;
    vram_rect->w = source_rect[2] >> 2;
    vram_rect->h = source_rect[3];
}
