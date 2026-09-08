#include "common.h"


#ifdef NON_MATCHING
#define ASM_REG(reg)
#define ASM_KEEP(var)   ((void)0)
#else
#define ASM_REG(reg)    asm(reg)
#define ASM_KEEP(var)   __asm__ __volatile__("" : "+r"(var))
#endif
typedef struct 
{
  u32 tag;
  s32 unk4;
  s16 unk8;
  u16 unkA;
  u8 unkC;
  u8 unkD;
  u16 unkE;
  s16 unk10;
  s16 unk12;
} S_80053858_prim;
typedef struct 
{
  char pad0[0x70];
  u32 unk70;
  char pad74[0x8D0 - 0x74];
  u8 *unk8D0;
} S_80053858_ctx;
typedef struct 
{
  S_80053858_ctx *unk0;
  char pad4[0x1D8];
} S_80083160_t;
typedef struct 
{
  char pad0[4];
  u8 *unk4;
  char pad8[8];
  s32 unk10;
  s16 unk14;
  u16 unk16;
  s16 unk18;
  u16 unk1A;
  u16 unk1C;
} S_80053858_rec;
extern S_80083160_t D_80083160;
extern void func_8004E21C(u8 *, u8);
extern s32 SetSprt(S_80053858_prim *);
extern void SetSemiTrans(S_80053858_prim *, s32);
extern s32 GetTPage(s32, s16, s32, s32);
extern void SetDrawMode(S_80053858_prim *, s32, s32, s32, s32);
/* Builds character sprites and draw modes for a linked list of text records. */
s32 func_80053858(S_80053858_rec *first_text)
{
  S_80053858_rec *text_record = first_text;
  S_80083160_t *render_state = &D_80083160;
  S_80053858_rec *text;
  int texture_page;
  register S_80053858_rec *next_node ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
  int link_mask = 0xFFFFFF;
  do
  {
    s32 char_index = 0;
    register s32 cursor_x ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    text = text_record;
    cursor_x = text->unk14;
    if (text->unk4[0] != 0)
    {
      do
      {
        u8 glyph_rect[4];
        S_80053858_prim *sprite;
        func_8004E21C(glyph_rect, text->unk4[char_index]);
        sprite = (S_80053858_prim *) render_state->unk0->unk8D0;
        render_state->unk0->unk8D0 = ((u8 *) sprite) + 0x14;
        sprite->unk8 = cursor_x;
        sprite->unkA = text->unk16;
        sprite->unkE = text->unk1A;
        sprite->unk4 = text->unk10;
        sprite->unkC = glyph_rect[0];
        sprite->unkD = glyph_rect[1];
        sprite->unk10 = glyph_rect[2];
        sprite->unk12 = glyph_rect[3];
        cursor_x = cursor_x + glyph_rect[2];
        SetSprt(sprite);
        if (text->unk1C & 1)
        {
          SetSemiTrans(sprite, 1);
        }
        if (!(text->unk1C & 2))
        {
          sprite->tag = (sprite->tag & 0xFF000000) | (render_state->unk0->unk70 & link_mask);
          render_state->unk0->unk70 = (render_state->unk0->unk70 & 0xFF000000) | (((u32) sprite) & link_mask);
        }
        char_index++;
      }
      while (text->unk4[char_index] != 0);
    }
    {
      S_80053858_prim *draw_mode = (S_80053858_prim *) render_state->unk0->unk8D0;
      render_state->unk0->unk8D0 = ((u8 *) draw_mode) + 0xC;
      SetDrawMode(draw_mode, 0, 0, texture_page = GetTPage(0, text->unk18, 0x3C0, 0) & 0xFFFF, 0);
      draw_mode->tag = (draw_mode->tag & 0xFF000000) | (render_state->unk0->unk70 & link_mask);
      render_state->unk0->unk70 = (render_state->unk0->unk70 & 0xFF000000) | (((u32) draw_mode) & link_mask);
    }
    next_node = *((S_80053858_rec **) (((char *) text_record) - 8));
    text_record = (S_80053858_rec *) (((char *) next_node) + 0x20);
  }
  while (next_node != 0);
  ASM_KEEP(next_node);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
 do { return 0; } while (0);
}
