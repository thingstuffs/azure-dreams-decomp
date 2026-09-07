#include "common.h"

#if defined(__mips__) && !defined(NON_MATCHING)
#define SCHED_KEEP(v) __asm__ __volatile__("" : : "r"(v))
#define SPLIT_BASE(v) __asm__("" : "=r"(v) : "0"(v))
#else
#define SCHED_KEEP(v) ((void)0)
#define SPLIT_BASE(v) ((void)0)
#endif
typedef struct S_80083120
{
  s16 field_0;
  s16 field_2;
  s16 field_4;
  s16 field_6;
} S_80083120;
extern S_80083120 D_80083120[8];
extern s16 func_80053428(S_80083120 *a0);
extern s16 func_80053604(S_80083120 *a0);
void func_8003F6F4(void)
{
  s32 i;
  u32 start;
  S_80083120 *base;
  S_80083120 *p;
  s16 raw;
  s32 v;

  i = 7;
  start = 7;
  base = D_80083120;
  SPLIT_BASE(base);
  p = &base[start];
loop:
  raw = p->field_0;
  v = (raw < 0) ? -raw : raw;
  if (v == 5)
  {
    goto case5;
  }
  if (v == 6)
  {
    goto case6;
  }
  p--;
  goto next;
case5:
  if (func_80053428(p) != 0)
  {
    p->field_0 = 0;
  }
  goto handled;
case6:
  if (func_80053604(p) != 0)
  {
    p->field_0 = 0;
  }
handled:
  SCHED_KEEP(p);
  p--;
next:
  SCHED_KEEP(p);
  SCHED_KEEP(i);
  i--;
  if (i >= 0)
  {
    goto loop;
  }
}
