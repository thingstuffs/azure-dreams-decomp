#include "common.h"

extern void func_8004E264(void *a0, s32 a1);
extern u8 *func_8004E280(u8 *a0, s32 *a1);
extern void func_8004E188(void *a0, u8 a1);

/* Builds positioned glyph records from text and embedded formatting commands. */
void *func_8004E298(u8 *glyph_buf, u8 *text, s32 style)
{
  u8 *text_cursor;
  u8 *glyph;
  u8 *first_glyph;
  u8 *width_ptr;
  s32 x;
  s32 y;
  s32 spacing;
  s32 x_offset;
  s32 text_byte;
  s32 char_code;
  glyph = glyph_buf;
  text_cursor = text;
  x = 0;
  y = 0;
  first_glyph = glyph;
  do
  {
    spacing = 0;
  }
  while (0);
  text_byte = *text_cursor;
  if (text_byte != 0)
  {
    width_ptr = glyph_buf + 0xA;
    char_code = text_byte & 0xFF;
    do
    {
      if (char_code == 0x20)
      {
        text_cursor += 1;
        {
          s32 space_x = x + 8;
          x = space_x + spacing;
        }
      }
      else if (char_code == 0xA)
      {
        text_cursor += 1;
        x = 0;
        y = y + 8;
      }
      else if (char_code == 0x9)
      {
        text_cursor += 1;
        if ((*text_cursor) == 0x73)
        {
          text_cursor += 1;
          spacing = (*text_cursor) - 0x30;
        }
        else
        {
          x += ((*text_cursor) - 0x30) * (spacing + 8);
        }
        text_cursor += 1;
      }
      else if (char_code == 0x8)
      {
        text_cursor = func_8004E280(text_cursor + 1, &style);
      }
      else if (char_code == 0xC)
      {
        u8 *next_text;
        next_text = func_8004E280(text_cursor + 1, &x_offset);
        x += x_offset;
        text_cursor = next_text;
      }
      else
      {
        s8 draw_code;
        s32 glyph_width;
        *glyph = 0;
        draw_code = 0x2C;
        if (style & 0x80)
        {
          draw_code = 0x2E;
        }
        width_ptr[-8] = (u8) (x - 0x80);
        width_ptr[-9] = (u8) draw_code;
        width_ptr[-7] = (u8) (y - 0x80);
        *((s16 *) (width_ptr - 6)) = (s16) (((style & 0x300) >> 3) | 0xF);
        func_8004E264(glyph, style);
        func_8004E188(glyph, *text_cursor);
        text_cursor += 1;
        glyph_width = width_ptr[0];
        width_ptr += 0xC;
        glyph += 0xC;
        x += glyph_width + spacing;
      }
      text_byte = *text_cursor;
      char_code = text_byte & 0xFF;
    }
    while (text_byte != 0);
  }
  if (glyph != first_glyph)
  {
    glyph[-0xC] = glyph[-0xC] | 0x80;
  }
  else
  {
    first_glyph = 0;
  }
  return first_glyph;
}
