#include "common.h"

struct S_8006CE80
{
  u16 field_0;
  u16 field_2;
  void *field_4;
  u32 field_8;
};
extern struct S_8006CE80 D_8006CE80[];
struct S_80082E60
{
  char pad0[8];
  union 
  {
    u8 b;
    u16 h;
  } field_8;
  u8 field_A;
  s8 field_B;
  s8 field_C;
  s8 field_D;
  s8 field_E;
};
extern struct S_80082E60 D_80082E60;
extern s8 D_80080A88[12];
extern void func_80043568(void);
extern void func_80053DA8(s32 arg0);
extern void func_800542BC(void);
void func_80040AA0(s16 arg0)
{
  u16 idx = ((u16) arg0) & 0xFFFF;
  struct S_8006CE80 *entry = &D_8006CE80[idx];
  s32 oldA;
  if (D_80082E60.field_8.h == 3)
  {
    return;
  }
  if ((idx == 6) && (D_80082E60.field_A == 2))
  {
    func_80043568();
  }
  D_80082E60.field_E = 1;
  oldA = D_80082E60.field_A;
  D_80082E60.field_8.h = arg0;
  if (oldA != entry->field_0)
  {
    if ((((u16) arg0) & 0xFFFF) == 5)
    {
      func_80053DA8(0x72);
    }
#ifdef NON_MATCHING
    D_80080A88[0] = 0;
#else
    *(s8 *)0x80080A88 = 0;
#endif
  }
  if (D_80080A88[0] == 0)
  {
    func_80053DA8(0xCF);
    func_800542BC();
  }
}
