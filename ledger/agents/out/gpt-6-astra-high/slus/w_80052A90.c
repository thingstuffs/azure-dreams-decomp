#include "common.h"

#include "common.h"

typedef struct
{
  s16 x;
  s16 y;
  s16 w;
  s16 h;
} RECT;

extern void StoreImage(RECT *rect, void *p);
extern void LoadImage(RECT *rect, void *p);
extern void DrawSync(s32 mode);

/* Draws a two-byte character string by copying font tiles to successive screen positions. */
void func_80052A90(u8 *text, s16 start_x, s16 start_y)
{
  RECT rect;
  u32 tile_buf[0x20];
  register s32 draw_enabled ASM_REG("$19"); /* draw-this-glyph draw_tile */
  s32 glyph_code;
  s32 tile_col;
  register s32 tile_index ASM_REG("$6");  /* tile index */
  s32 tile_x;
  u8 *cursor;
  s16 pen_x;
  s16 dest_y;
  s32 glyph_w;
  s32 glyph_h;
  s32 code_u16;
  s32 lead_byte;
  s32 draw_tile;

  cursor = text;
  pen_x = start_x;
  draw_enabled = 1;
  __asm__ __volatile__("" : : "r"(draw_enabled));
  if ((*cursor) != 0)
  {
    dest_y = start_y;
    glyph_w = 3;
    glyph_h = 0x10;
    do
    {
      __asm__ __volatile__("" : : : "memory");
      lead_byte = cursor[0];
      __asm__ __volatile__("" : : "r"(lead_byte));
      glyph_code = cursor[1];
      glyph_code |= lead_byte << 8;
      tile_index = glyph_code;
      code_u16 = tile_index & 0xFFFF;
      cursor += 2;
      if (code_u16 == 0x8140)
      {
        tile_index = 0;
        goto do_blit;
      }
      if (((u32) ((glyph_code + 0x7DA0) & 0xFFFF)) < 0x1AU)
      {
        goto shared_map;
      }
      if (((u32) ((glyph_code + 0x7D7F) & 0xFFFF)) < 0x1AU)
      {
        tile_index = glyph_code + 0x7DC0;
        goto do_blit;
      }
      if (((u32) ((glyph_code + 0x7DB1) & 0xFFFF)) >= 0xAU)
      {
        goto check_punctuation;
      }
      shared_map:
      tile_index = glyph_code + 0x7DC1;
      goto do_blit;
      check_punctuation:
      if (code_u16 == 0x8144)
      {
        goto set_period;
      }
      if (code_u16 == 0x817C)
      {
        goto set_minus;
      }
      draw_enabled = 0;
      goto do_blit;
      set_period:
      tile_index = 0xE;
      goto do_blit;
      set_minus:
      tile_index = 0xD;
      do_blit:
      draw_tile = draw_enabled;
      __asm__ __volatile__("" : : "r"(draw_tile));
      if (draw_tile != 0)
      {
        register void *tile_data ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register RECT *tile_rect ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        tile_data = tile_buf;
        __asm__ __volatile__("" : : "r"(tile_data));
        tile_rect = &rect;
        __asm__ __volatile__("" : : "r"(tile_rect));
        tile_index = tile_index & 0xFFFF;
        tile_col = tile_index & 7;
        tile_x = tile_col << 1;
        tile_x = tile_x + tile_col;
        rect.x = tile_x + 0x340;
        rect.y = (s16) ((((u32) tile_index) >> 3) << 4);
        rect.w = glyph_w;
        rect.h = glyph_h;
        StoreImage(tile_rect, tile_data);
        rect.x = pen_x;
        rect.y = dest_y;
        rect.w = glyph_w;
        rect.h = glyph_h;
        LoadImage(&rect, tile_buf);
        DrawSync(0);
      }
      pen_x += 3;
    }
    while ((*cursor) != 0);
  }
}
