#include "common.h"

#include "common.h"

#ifdef __mips__
#define PIN_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#define PIN_BARRIER(v) __asm__ __volatile__("" : : "r"(v))
#define PIN_BARRIER2(a, b) __asm__ __volatile__("" : : "r"(a), "r"(b))
#else
#define PIN_KEEP(v) ((void)0)
#define PIN_BARRIER(v) ((void)0)
#define PIN_BARRIER2(a, b) ((void)0)
#endif
typedef struct
{
  u8 a;
  u8 b;
  u8 c;
} Slot1_80042710;
typedef struct
{
  s8 a;
  s8 b;
} Slot2_80042710;
typedef union
{
  u32 raw;
  struct
  {
    u8 b0;
    u8 tag;
    u8 b2;
    u8 b3;
  } f;
} Grp48_80042710;
typedef struct
{
  u8 f00;
  u8 f01;
  u8 f02;
  u8 f03;
  u8 f04;
  u8 f05;
  u16 f06;
  Slot1_80042710 slots1[3];
  u8 f11;
  u8 f12;
  u8 f13;
  u32 f14;
  u32 f18;
  u32 f1c;
  u16 f20;
  u16 f22;
  u16 f24;
  u8 f26;
  u8 f27;
  u8 f28;
  u16 f2a;
  Slot2_80042710 slots2[4];
  u8 name[13];
  u8 pad41[2];
  u8 f43;
  u8 f44;
  u8 f45;
  Grp48_80042710 grp48;
  void *f4c;
  u32 pad50;
  u32 f54;
} S_80042710;
extern void func_80041E70(S_80042710 *a0);
void func_80042710(S_80042710 *a0, S_80042710 *a1)
{
  register S_80042710 *src ASM_REG("$10") = a1;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
  register s32 i ASM_REG("$6");   /* MATCH pin: slus-diff */
  u8 first;
  PIN_KEEP(src);
  first = src->f00;
  PIN_BARRIER(first);
  {
  register S_80042710 *dest ASM_REG("$9") = a0;   /* MATCH pin: slus-diff */
  PIN_KEEP(dest);
  dest->f00 = first;
  dest->f01 = src->f01;
  dest->f02 = src->f02;
  dest->f03 = src->f03;
  dest->f04 = src->f04;
  dest->f05 = src->f05;
  dest->f06 = src->f06;
  i = 2;
  {
    register u8 *sp ASM_REG("$4") = (u8 *)src + 6;   /* MATCH pin: slus-diff */
    register u8 *dp ASM_REG("$3") = (u8 *)dest + 6;   /* MATCH pin: slus-diff */
    do
    {
      dp[8] = sp[8];
      dp[10] = sp[10];
      sp -= 3;
      dp -= 3;
      i--;
    }
    while (i >= 0);
  }
  dest->f11 = src->f11;
  dest->f12 = src->f12;
  dest->f13 = src->f13;
  dest->f14 = (dest->f14 | src->f14) & 0xFFEFFFFF;
  dest->f18 = src->f18;
  dest->f1c = (dest->f1c | src->f1c) & 0xEFF6FEFF;
  dest->f20 = src->f20;
  dest->f22 = src->f22;
  dest->f24 = src->f24;
  dest->f26 = src->f26;
  dest->f27 = src->f27;
  dest->f28 = src->f28;
  dest->f2a = src->f2a;
  i = 3;
  {
    register s8 *sp2 ASM_REG("$8") = (s8 *)src + 6;   /* MATCH pin: slus-diff */
    register s8 *dp2 ASM_REG("$7") = (s8 *)dest + 6;   /* MATCH pin: slus-diff */
    register s32 x ASM_REG("$2");   /* MATCH pin: slus-diff */
    register s32 y;
    do
    {
      x = sp2[44];
      y = sp2[45];
      PIN_BARRIER2(x, y);
      dp2[44] = x;
      dp2[45] = y;
      PIN_BARRIER2(x, y);
      sp2 -= 2;
      i--;
      dp2 -= 2;
    }
    while (i >= 0);
  }
  i = 12;
  do
  {
    dest->name[i] = src->name[i];
    i--;
  }
  while (i >= 0);
  dest->f43 = src->f43;
  dest->f44 = src->f44;
  if (dest->grp48.f.tag == 0)
  {
    dest->grp48 = src->grp48;
  }
  if (src->grp48.f.tag == 0xF)
  {
    dest->grp48 = src->grp48;
    if (src->f4c != 0)
    {
      dest->f4c = &dest->grp48;
    }
  }
  dest->f45 = src->f45;
  {
    u32 final_value = src->f54;
    PIN_BARRIER(final_value);
    {
      S_80042710 *call_arg = dest;
      PIN_KEEP(call_arg);
      dest->f54 = final_value;
      func_80041E70(call_arg);
    }
  }
  }
}
