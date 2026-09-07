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
s32 func_80053858(S_80053858_rec *arg0)
{
  S_80053858_rec *cur = arg0;
  S_80083160_t *base = &D_80083160;
  S_80053858_rec *r;
  int new_var2;
  register S_80053858_rec *next ASM_REG("$4");
  register int new_var ASM_REG("$19") = 0xFFFFFF;
  do
  {
    s32 i = 0;
    register s32 acc ASM_REG("$20");
    r = cur;
    acc = r->unk14;
    if (r->unk4[0] != 0)
    {
      do
      {
        u8 buf[4];
        S_80053858_prim *p;
        func_8004E21C(buf, r->unk4[i]);
        p = (S_80053858_prim *) base->unk0->unk8D0;
        base->unk0->unk8D0 = ((u8 *) p) + 0x14;
        p->unk8 = acc;
        p->unkA = r->unk16;
        p->unkE = r->unk1A;
        p->unk4 = r->unk10;
        p->unkC = buf[0];
        p->unkD = buf[1];
        p->unk10 = buf[2];
        p->unk12 = buf[3];
        acc = acc + buf[2];
        SetSprt(p);
        if (r->unk1C & 1)
        {
          SetSemiTrans(p, 1);
        }
        if (!(r->unk1C & 2))
        {
          p->tag = (p->tag & 0xFF000000) | (base->unk0->unk70 & new_var);
          base->unk0->unk70 = (base->unk0->unk70 & 0xFF000000) | (((u32) p) & new_var);
        }
        i++;
      }
      while (r->unk4[i] != 0);
    }
    {
      S_80053858_prim *p2 = (S_80053858_prim *) base->unk0->unk8D0;
      base->unk0->unk8D0 = ((u8 *) p2) + 0xC;
      SetDrawMode(p2, 0, 0, new_var2 = GetTPage(0, r->unk18, 0x3C0, 0) & 0xFFFF, 0);
      p2->tag = (p2->tag & 0xFF000000) | (base->unk0->unk70 & new_var);
      base->unk0->unk70 = (base->unk0->unk70 & 0xFF000000) | (((u32) p2) & new_var);
    }
    next = *((S_80053858_rec **) (((char *) cur) - 8));
    cur = (S_80053858_rec *) (((char *) next) + 0x20);
  }
  while (next != 0);
  ASM_KEEP(next);
 do { return 0; } while (0);
}
