#include "common.h"

#include "common.h"

#ifdef NON_MATCHING
#define PIN_KEEP(v) ((void)0)
#else
#define PIN_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#endif
typedef struct S_800E3E48
{
  u8 pad00[0x14];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x8C - 0x20];
} S_800E3E48;
typedef struct S_800423C0_Src
{
  u8 pad0[3];
  u8 unk3;
} S_800423C0_Src;
typedef struct S_800423C0_Obj
{
  u8 pad00[0x12];
  u8 unk12;
  u8 pad13[0x14 - 0x13];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x45 - 0x20];
  u8 unk45;
} S_800423C0_Obj;
extern S_800E3E48 D_800E3E48[];
extern void func_80042710(void *dst, void *src);
extern s16 func_800A1BD0(void *a0, s32 a1);
void func_800423C0(S_800423C0_Obj *a0, s16 a1, S_800423C0_Src *a2)
{
  int new_var;
  S_800E3E48 *s0;
  s32 dir;
  register s32 mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  if (a2 != 0)
  {
    S_800423C0_Obj *call_arg;

    s0 = &D_800E3E48[a2->unk3 & 0x1F];
    func_80042710(a0, s0);
    call_arg = a0;
    PIN_KEEP(call_arg);
    mask = -8;
    a0->unk14 &= mask;
    a0->unk1C &= mask;
    a0->unk14 |= s0->unk14 & 7;
    a0->unk1C |= s0->unk1C & 7;
    dir = func_800A1BD0(call_arg, mask);
    if (dir >= 0)
    {
      register u8 *page ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
      u16 *other = (u16 *)0x80012094;
      s32 scaled;

      page = (u8 *)0x80010000;
      scaled = dir * 2;
      PIN_KEEP(page);
      page = (u8 *)((unsigned long)scaled + (unsigned long)page);
      if (dir == 0)
      {
        other = (u16 *)0x80012096;
      }
      dir = *(u16 *)(page + 0x2094);
      if (dir == *other)
      {
        new_var = dir + 1;
        *(u16 *)(page + 0x2094) = new_var & 7;
      }
      a0->unk45 = page[0x2094];
      a0->unk12 = page[0x2098];
    }
  }
  a0->unk1C |= 0x20000;
}
