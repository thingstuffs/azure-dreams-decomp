#include "common.h"

#include "common.h"

typedef struct
{
    s16 x;
    s16 y;
    s16 w;
    s16 h;
}
RECT;

extern void StoreImage(RECT *rect, void *p);
extern void LoadImage(RECT *rect, void *p);
extern void DrawSync(s32 mode);

/* Draws a two-byte character string by copying font tiles to successive screen positions. */
void func_80052A90(u8 *text, s16 start_x, s16 start_y)
{
    RECT rect;
    u32 tile_buf[0x20];
    s32 draw_enabled;
    s32 glyph_code;
    u16 tile_index;  /* tile index */
    u8 *cursor;
    s16 pen_x;
    s16 dest_y;
    s32 code_u16;
    s16 lead_byte;
    s16 draw_tile;

    cursor = text;
    pen_x = start_x;
    dest_y = start_y;
    draw_enabled = 1;
    if ((*cursor) != 0) {
        do {
            lead_byte = cursor[0];
            lead_byte <<= 8;
            glyph_code = cursor[1];
            glyph_code |= (u16)lead_byte;
            tile_index = glyph_code;
            code_u16 = tile_index & 0xFFFF;
            cursor += 2;
            if (code_u16 == 0x8140) {
                tile_index = 0;
            } else if (((u32)((glyph_code + 0x7DA0) & 0xFFFF)) < 0x1AU) {
                tile_index = glyph_code + 0x7DC1;
            } else if (((u32)((glyph_code + 0x7D7F) & 0xFFFF)) < 0x1AU) {
                tile_index = glyph_code + 0x7DC0;
            } else if (((u32)((glyph_code + 0x7DB1) & 0xFFFF)) < 0xAU) {
                tile_index = glyph_code + 0x7DC1;
            } else {
                switch (code_u16) {
                default: draw_enabled = 0; break;
                case 0x8144: tile_index = 0xE; break;
                case 0x817C: tile_index = 0xD; break;
                }
            }
            draw_tile = draw_enabled;
            if (draw_tile != 0) {
                u16 t = tile_index;
                rect.x = (t % 8) * 3 + 0x340;
                rect.y = (t / 8) * 16;
                rect.w = 3;
                rect.h = 0x10;
                StoreImage(&rect, tile_buf);
                rect.x = pen_x;
                rect.y = dest_y;
                rect.w = 3;
                rect.h = 0x10;
                LoadImage(&rect, tile_buf);
                DrawSync(0);
            }
            pen_x += 3;
        }
        while ((*cursor) != 0);
    }
}
