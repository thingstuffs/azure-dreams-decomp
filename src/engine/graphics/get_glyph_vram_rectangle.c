#include "common.h"

#include "common.h"

extern s32 glyph_vram_column_steps[];
extern s32 glyph_vram_row_steps[];
extern s32 map_fullwidth_character_to_glyph_byte(s32 code);
extern void get_glyph_vram_rectangle(s32 value, s16 *rect);
extern void MoveImage(void *rect, s32 x, s32 y);

/* Copies an image to a table-spaced VRAM position when its destination X is in range. */
void move_glyph_to_grid_position(u8 *image_code, s16 grid_x, s16 grid_y, s32 spacing, s16 base_x, s16 base_y)
{
    s16 rect[4];
    s32 dest_x;

    dest_x = base_x + grid_x * glyph_vram_column_steps[spacing & 0xFF];
    if ((u32)(dest_x - 0x140) < 0x2C0) {
        get_glyph_vram_rectangle(map_fullwidth_character_to_glyph_byte(image_code[1] | (image_code[0] << 8)) & 0xFF, rect);
        MoveImage(rect, dest_x, base_y + grid_y * glyph_vram_row_steps[spacing & 0xFF]);
    }
}
