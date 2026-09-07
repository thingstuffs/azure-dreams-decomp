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

/* Draws a two-byte-code string as font-tile blits: decodes each 2-byte
 * (Shift-JIS-ish) code into a tile index (special-casing full-width space,
 * a couple of contiguous kana ranges, and two extra punctuation codes),
 * StoreImage's the source tile out of the font sheet into a scratch VRAM
 * buffer, then LoadImage's it back in at the advancing (x, dest_y) pen
 * position and syncs the GPU. An unrecognized code just advances the pen
 * without drawing. */
void func_80052A90(u8 *arg0, s16 arg1, s16 arg2)
{
  RECT rect;
  u32 buf[0x20];
  register s32 var_s3 ASM_REG("$19"); /* draw-this-glyph flag */
  s32 temp_v1;
  register s32 var_a2 ASM_REG("$6");  /* tile index */
  s32 x;
  u8 *var_s0;
  s16 var_s1;
  s16 dest_y;
  s32 glyph_w;
  s32 glyph_h;
  s32 temp_a0;
  s32 hi;
  s32 flag;

  var_s0 = arg0;
  var_s1 = arg1;
  var_s3 = 1;
  __asm__ __volatile__("" : : "r"(var_s3));
  if ((*var_s0) != 0)
  {
    dest_y = arg2;
    glyph_w = 3;
    glyph_h = 0x10;
    do
    {
      __asm__ __volatile__("" : : : "memory");
      hi = var_s0[0];
      __asm__ __volatile__("" : : "r"(hi));
      temp_v1 = var_s0[1];
      temp_v1 |= hi << 8;
      var_a2 = temp_v1;
      temp_a0 = var_a2 & 0xFFFF;
      var_s0 += 2;
      if (temp_a0 == 0x8140)
      {
        var_a2 = 0;
        goto do_blit;
      }
      if (((u32) ((temp_v1 + 0x7DA0) & 0xFFFF)) < 0x1AU)
      {
        goto shared_map;
      }
      if (((u32) ((temp_v1 + 0x7D7F) & 0xFFFF)) < 0x1AU)
      {
        var_a2 = temp_v1 + 0x7DC0;
        goto do_blit;
      }
      if (((u32) ((temp_v1 + 0x7DB1) & 0xFFFF)) >= 0xAU)
      {
        goto checks_8144;
      }
      shared_map:
      var_a2 = temp_v1 + 0x7DC1;
      goto do_blit;
      checks_8144:
      if (temp_a0 == 0x8144)
      {
        goto set_E;
      }
      if (temp_a0 == 0x817C)
      {
        goto set_D;
      }
      var_s3 = 0;
      goto do_blit;
      set_E:
      var_a2 = 0xE;
      goto do_blit;
      set_D:
      var_a2 = 0xD;
      do_blit:
      flag = var_s3;
      __asm__ __volatile__("" : : "r"(flag));
      if (flag != 0)
      {
        register void *pbuf ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register RECT *prect ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        pbuf = buf;
        __asm__ __volatile__("" : : "r"(pbuf));
        prect = &rect;
        __asm__ __volatile__("" : : "r"(prect));
        var_a2 = var_a2 & 0xFFFF;
        temp_v1 = var_a2 & 7;
        x = temp_v1 << 1;
        x = x + temp_v1;
        rect.x = x + 0x340;
        rect.y = (s16) ((((u32) var_a2) >> 3) << 4);
        rect.w = glyph_w;
        rect.h = glyph_h;
        StoreImage(prect, pbuf);
        rect.x = var_s1;
        rect.y = dest_y;
        rect.w = glyph_w;
        rect.h = glyph_h;
        LoadImage(&rect, buf);
        DrawSync(0);
      }
      var_s1 += 3;
    }
    while ((*var_s0) != 0);
  }
}
