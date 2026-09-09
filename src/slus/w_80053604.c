#include "common.h"

#include "common.h"

typedef struct
{
  char pad0[2];
  s16 counter;
  s16 duration;
  s16 semiTransSel;
} S_80053604_Obj;
typedef struct
{
  u32 tag;
  char pad4[8];
} S_80053604_TPage;
typedef struct
{
  u32 tag;
  u32 rgbc;
  s16 x0;
  s16 y0;
  s16 x1;
  s16 y1;
  s16 x2;
  s16 y2;
  s16 x3;
  s16 y3;
} S_80053604_PolyF4;
typedef struct
{
  char pad0[0x70];
  u32 otHead;
  char pad1[0x8D0 - 0x74];
  void *nextPrim;
} S_80053604_RenderState;
typedef struct
{
  S_80053604_RenderState *renderState;
  char pad0[0x1C];
} S_80053604_Main;
extern S_80053604_Main D_80083160;
extern u16 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetPolyF4(S_80053604_PolyF4 *p);
extern void SetSemiTrans(S_80053604_PolyF4 *p, s32 abe);
extern void SetDrawMode(S_80053604_TPage *p, s32 tge, s32 abe, u16 tpage, s32 unk4);
/* Draws a full-screen additive or subtractive fade, advances its timer, and reports completion. */
s32 func_80053604(S_80053604_Obj *fade)
{
  u32 addr_mask;
  register u32 tag_mask;
  u32 color;
  S_80053604_TPage *tpage;
  S_80053604_PolyF4 *poly;
  S_80053604_Main *main_state;
  s32 blend_mode;
  s32 done;
  s32 elapsed;
  s16 duration;
  s32 scaled_elapsed;
  tpage = (S_80053604_TPage *) D_80083160.renderState->nextPrim;
  D_80083160.renderState->nextPrim = (void *) (((u8 *) tpage) + (sizeof(S_80053604_TPage)));
  done = 0;
  main_state = &D_80083160;
  poly = (S_80053604_PolyF4 *) D_80083160.renderState->nextPrim;
  D_80083160.renderState->nextPrim = (void *) (((u8 *) poly) + (sizeof(S_80053604_PolyF4)));
  blend_mode = 1;
  if (fade->semiTransSel == 0)
  {
    blend_mode = 2;
  }
  SetDrawMode(tpage, 0, 0, GetTPage(0, blend_mode, 0, 0) & 0xFFFF, 0);
  elapsed = fade->counter;
  duration = fade->duration;
  if (elapsed > duration)
  {
    done = 1;
  }
  if (elapsed >= duration)
  {
    color = 0xFFFFFF;
  }
  else
  {
    scaled_elapsed = elapsed << 8;
    color = scaled_elapsed / duration;
    color = color + ((color << 8) + (color << 16));
  }
  if (!done)
  {
    fade->counter = ((u16) fade->counter) + 1;
  }
  poly->rgbc = color;
  SetPolyF4(poly);
  SetSemiTrans(poly, 1);
  do {
      addr_mask = 0x00FFFFFF;
  } while (0);
  poly->x3 = 320;
  poly->x2 = 320;
  poly->x1 = 0;
  poly->x0 = 0;
  poly->y2 = 0;
  poly->y0 = 0;
  tag_mask = 0xFF000000;
  poly->y3 = 224;
  poly->y1 = 224;
  poly->tag = (poly->tag & tag_mask) | (main_state->renderState->otHead & addr_mask);
  main_state->renderState->otHead = (main_state->renderState->otHead & tag_mask) | (((u32) poly) & addr_mask);
  tpage->tag = (tpage->tag & tag_mask) | (main_state->renderState->otHead & addr_mask);
  main_state->renderState->otHead = (main_state->renderState->otHead & tag_mask) | (((u32) tpage) & addr_mask);
  return done;
}
