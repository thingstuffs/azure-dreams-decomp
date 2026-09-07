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
s32 func_80053604(S_80053604_Obj *obj)
{
  register u32 mask_lo ASM_REG("$4");
  register u32 mask_hi;
  register u32 color ASM_REG("$5");
  S_80053604_TPage *tpage;
  S_80053604_PolyF4 *poly;
  S_80053604_Main *g;
  s32 abr;
  s32 done;
  register s32 a ASM_REG("$4");
  s16 b;
  register s32 scaled ASM_REG("$2");
  tpage = (S_80053604_TPage *) D_80083160.renderState->nextPrim;
  D_80083160.renderState->nextPrim = (void *) (((u8 *) tpage) + (sizeof(S_80053604_TPage)));
  done = 0;
  g = &D_80083160;
  poly = (S_80053604_PolyF4 *) D_80083160.renderState->nextPrim;
  D_80083160.renderState->nextPrim = (void *) (((u8 *) poly) + (sizeof(S_80053604_PolyF4)));
  abr = 1;
  if (obj->semiTransSel == 0)
  {
    abr = 2;
  }
  SetDrawMode(tpage, 0, 0, GetTPage(0, abr, 0, 0) & 0xFFFF, 0);
  a = obj->counter;
  b = obj->duration;
  if (a > b)
  {
    done = 1;
  }
  if (a >= b)
  {
    color = 0xFFFFFF;
  }
  else
  {
    scaled = a << 8;
    color = scaled / b;
    color = color + ((color << 8) + (color << 16));
  }
  if (!done)
  {
    obj->counter = ((u16) obj->counter) + 1;
  }
  poly->rgbc = color;
  SetPolyF4(poly);
  SetSemiTrans(poly, 1);
  mask_lo = 0x00FFFFFF;
  poly->x3 = 320;
  poly->x2 = 320;
  poly->x1 = 0;
  poly->x0 = 0;
  poly->y2 = 0;
  poly->y0 = 0;
  mask_hi = 0xFF000000;
  poly->y3 = 224;
  poly->y1 = 224;
  poly->tag = (poly->tag & mask_hi) | (g->renderState->otHead & mask_lo);
  g->renderState->otHead = (g->renderState->otHead & mask_hi) | (((u32) poly) & mask_lo);
  tpage->tag = (tpage->tag & mask_hi) | (g->renderState->otHead & mask_lo);
  g->renderState->otHead = (g->renderState->otHead & mask_hi) | (((u32) tpage) & mask_lo);
  return done;
}
