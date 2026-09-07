#include "common.h"

extern void func_8004F67C(void);
typedef struct S_8004F9AC_L3
{
  char pad0[8];
  s16 val;
} S_8004F9AC_L3;
typedef struct S_8004F9AC_L2
{
  char pad0[4];
  S_8004F9AC_L3 *l3;
} S_8004F9AC_L2;
typedef struct S_8004F9AC_L1
{
  char pad0[0xC];
  S_8004F9AC_L2 *l2;
} S_8004F9AC_L1;
typedef struct S_8004F9AC_Obj
{
  void (*func)(void);
  S_8004F9AC_L1 *list[1];
  char pad1[0x18];
  s32 field_0x20;
  s32 count;
} S_8004F9AC_Obj;
void func_8004F9AC(S_8004F9AC_Obj *a0)
{
  s32 a3 = a0->field_0x20;
  s32 a2;
  s32 i;
  S_8004F9AC_L1 **p;
  if (a3 >= 0x21)
  {
    a3 = 0x20;
    a0->func = func_8004F67C;
  }
  do { i = 0; } while (0);
  if (a0->count > 0)
  {
    a2 = 0x18;
    p = (S_8004F9AC_L1 **) a0;
    do
    {
      (*(*(&p[1]))).l2->l3->val = a2;
      p++;
      i++;
      a2 += a3;
    }
    while (i < a0->count);
  }
  a0->field_0x20 = a3 + ((0x28 - a3) >> 3);
}
