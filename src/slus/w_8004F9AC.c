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
/* Assign evenly spaced list values and increase spacing, switching callbacks at the limit. */
void func_8004F9AC(S_8004F9AC_Obj *obj)
{
  s32 spacing = obj->field_0x20;
  s32 value;
  s32 index;
  S_8004F9AC_L1 **entry;
  if (spacing >= 0x21)
  {
    spacing = 0x20;
    obj->func = func_8004F67C;
  }
  do { index = 0; } while (0);
  if (obj->count > 0)
  {
    value = 0x18;
    entry = (S_8004F9AC_L1 **) obj;
    do
    {
      (*(*(&entry[1]))).l2->l3->val = value;
      entry++;
      index++;
      value += spacing;
    }
    while (index < obj->count);
  }
  obj->field_0x20 = spacing + ((0x28 - spacing) >> 3);
}
