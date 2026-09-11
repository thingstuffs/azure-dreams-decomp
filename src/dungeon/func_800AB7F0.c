#include "common.h"


extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
typedef s32 M2C_UNK;
extern u8 D_80083498[];
extern u8 D_800DDC40[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_8004DA74();
s32 func_8004E298();
M2C_UNK func_8004E5A0();
s32 func_80069E98();
void *func_800B119C();
void *func_800B12F4();
M2C_UNK func_800B1320();
M2C_UNK func_800B135C();
extern M2C_UNK D_80077FEC;
extern M2C_UNK D_800B0D34;
extern s32 D_800DEFF8[];
extern M2C_UNK D_800B06F0;
/* Creates an entity panel with numeric labels, centered text, and a shaded background. */
void *func_800B0F50(void *owner)
{
  s8 text_buf[16];
  s32 prim_index;
  s32 prim_flags;
  s32 count_or_color;
  register s32 green_color ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register s32 blue_color ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 color_or_addr;
  register s32 vertex_color ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  s32 text_width;
  register s32 text_addr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register s32 red_color ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  u16 text_id;
  void *owner_pos;
  void *panel_pos;
  void *digits;
  void *prim;
  void *panel_data;
  s32 *color_ptr;
  void *entity;
  void *panel;
  void *transform;
  entity = owner;
  panel = func_8003FD64(0x12, D_80083498);
  if (panel != 0)
  {
    color_or_addr = 0x808080;
    transform = *((void **) (((s8 *) panel) + 0xC));
    panel_pos = *((void **) (((s8 *) panel) + 8));
    *((s16 *) (((s8 *) transform) + 0x1C)) = 0x1000;
    *((s16 *) (((s8 *) transform) + 0x1E)) = 0x1000;
    *((s32 *) (((s8 *) transform) + 0xC)) = color_or_addr;
    *((u16 *) (((s8 *) transform) + 0x18)) = 0xFC00;
    owner_pos = *((void **) (((s8 *) entity) + (-0x18)));
    *((u16 *) (((s8 *) panel_pos) + 2)) = (u16) (*((u16 *) (((s8 *) owner_pos) + 2)));
    *((u16 *) (((s8 *) panel_pos) + 6)) = (u16) (*((u16 *) (((s8 *) owner_pos) + 6)));
    *((s16 *) (((s8 *) panel_pos) + 0xA)) = (s16) ((*((u16 *) (((s8 *) owner_pos) + 0xA))) - (D_800DDC40[*((u8 *) (((s8 *) entity) + 0x13))] + 0x50));
    *((M2C_UNK **) (((s8 *) panel) + 0x10)) = &D_800B0D34;
    func_8004491C(panel, &D_800B06F0, owner_pos, panel_pos);
    panel_data = panel + 0x20;
    *((void **) (((s8 *) panel_data) + 0x14)) = entity;
    *((void **) (((s8 *) panel) + 0x20)) = (void *) (panel + 0x70);
    *((void **) (((s8 *) panel_data) + 4)) = (void *) (panel + 0x58);
    *((M2C_UNK **) (((s8 *) panel) + 0x70)) = &D_80077FEC;
    *((s32 *) (((s8 *) panel) + 0x58)) = color_or_addr;
    prim = func_800B12F4();
    *((void **) (((s8 *) panel_data) + 0x28)) = prim;
    if (prim != 0)
    {
      count_or_color = 3;
      ASM_KEEP_NV(count_or_color);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
      {
        s32 text_style;
        text_style = 9;
        text_buf[2] = text_style;
        text_buf[0] = text_style;
        text_style = 0x38;
        digits = &text_buf[4];
        text_buf[3] = text_style;
        text_buf[1] = text_style;
      }
      func_8004E5A0(*((u8 *) (((s8 *) entity) + 0x28)), count_or_color, digits);
      *((s32 *) (((s8 *) panel) + 0x74)) = func_8004E298(prim, text_buf, 0);
      func_800B1320(prim, 8, ((s32) (0 - (((s32) ((*((u8 *) (((s8 *) prim) + 3))) << 0x18)) >> 8))) >> 0x10);
      func_800B135C(prim, 8);
      prim += 0x24;
      *((s32 *) (((s8 *) panel) + 0x5C)) = color_or_addr;
      func_8004E5A0(*((u8 *) (((s8 *) entity) + 0x25)), 3, digits);
      *((s32 *) (((s8 *) panel) + 0x78)) = func_8004E298(prim, text_buf, 0);
      func_800B1320(prim, 8, (s32) ((s16) ((0 - ((s8) (*((u8 *) (((s8 *) prim) + 3))))) + 8)));
      func_800B135C(prim, 8);
      prim += 0x24;
      *((s32 *) (((s8 *) panel) + 0x60)) = color_or_addr;
      text_id = *((u16 *) (((s8 *) entity) + 0x46));
      color_or_addr = (s32) (panel + 0x64);
      if (text_id & 0x8000)
      {
        *((s32 *) (((s8 *) panel) + 0x7C)) = func_8004DA74(prim, D_800DEFF8[text_id & 0x3FFF] + 1, 0);
        text_addr = D_800DEFF8[(*((u16 *) (((s8 *) entity) + 0x46))) & 0x3FFF];
        do { prim_index = 4; } while (0);
        goto position_text;
      }
      else
      {
        s32 *text_table = D_800DEFF8;
        *((s32 *) (((s8 *) panel) + 0x7C)) = func_8004DA74(prim, text_table[4] + 1, 0);
        text_addr = text_table[4];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        prim_index = 4;
        position_text:
        text_width = func_80069E98(text_addr + 1);

        do {
            text_width *= 4;
            func_800B1320(prim, (s16) ((((s32) (0x20 - text_width)) >> 1) + 0x80), (s32) ((s16) ((0 - ((s8) (*((u8 *) (((s8 *) prim) + 3))))) + 0x11)));
        } while (0);
        func_800B135C(prim, 8);
        prim += 0x30;
      }
      ASM_KEEP(color_or_addr);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
      *((s32 *) color_or_addr) = 0x808080;
      *((void **) (((s8 *) ((prim_index * 4) + panel_data)) + 0x50)) = prim;
      *((u8 *) (((s8 *) prim) + 1)) = 0x38U;
      *((s8 *) (((s8 *) prim) + 2)) = -2;
      *((s8 *) (((s8 *) prim) + 3)) = -2;
      *((s8 *) (((s8 *) prim) + 9)) = 0;
      *((s8 *) (((s8 *) prim) + 8)) = 0;
      *((s8 *) (((s8 *) prim) + 0xB)) = 0x24;
      *((s8 *) (((s8 *) prim) + 0xA)) = 0x24;
      prim_flags = 0xC0;
      *((u8 *) (((s8 *) prim) + 0)) = prim_flags;
      count_or_color = 0x202020;
      blue_color = 0x402020;
      green_color = 0x204020;
      red_color = 0x200000;
      *((s32 *) (((s8 *) panel_data) + 0x18)) = count_or_color;
      ASM_KEEP_NV(count_or_color);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
      vertex_color = count_or_color;
      ASM_KEEP_NV(vertex_color);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      ASM_KEEP_NV(red_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
      red_color |= 0x2040;
      *((s32 *) (((s8 *) panel_data) + 0x1C)) = blue_color;
      *((s32 *) (((s8 *) panel_data) + 0x20)) = green_color;
      *((s32 *) (((s8 *) panel_data) + 0x24)) = red_color;
      *((s32 *) (((s8 *) prim) + 4)) = vertex_color;
      vertex_color = *((s32 *) (((s8 *) panel_data) + 0x1C));
      *((s32 *) (((s8 *) prim) + 0xC)) = vertex_color;
      vertex_color = *((s32 *) (((s8 *) panel_data) + 0x20));
      prim_index++;
      *((s32 *) (((s8 *) prim) + 0x10)) = vertex_color;
      red_color = *((s32 *) (((s8 *) panel_data) + 0x24));
      *((u8 *) (((s8 *) prim) + 1)) = (u8) ((*((u8 *) (((s8 *) prim) + 1))) | 2);
      *((s32 *) (((s8 *) prim) + 0x14)) = red_color;
      prim += 0x18;
      *((void **) (((s8 *) ((prim_index * 4) + panel_data)) + 0x50)) = prim;
      *((u8 *) (((s8 *) prim) + 1)) = 0x81;
      *((s16 *) (((s8 *) prim) + 4)) = 0x40;
      *((s16 *) (((s8 *) prim) + 6)) = 0;
      *((u8 *) (((s8 *) prim) + 0)) = prim_flags;
    }
  }
  return panel;
}
