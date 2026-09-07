#include "common.h"

extern s32 D_800814A8[];
extern int D_800814A0[];
extern void func_80024654(void *, s16, s16, s32, s32);
extern s16 D_800249A4;
extern u16 D_800249A6[5];

void func_80024830(void *arg0)
{
  s32 temp_s1;
  u16 temp_v0;
  u16 *counter_base = D_800249A6;
  temp_s1 = ((s32) arg0) - 0x20;
  func_80024654(temp_s1, *((s16 *) (((u8 *) arg0) + 0x26)), *((s16 *) (((u8 *) arg0) + 0x30)), ((s32 *) D_800814A8[0])[0x18], (counter_base[0]++, 0));
  func_80024654(temp_s1, *((s16 *) (((u8 *) arg0) + 0x26)), *((s16 *) (((u8 *) arg0) + 0x30)), ((s32 *) D_800814A8[0])[0x18], 1);
  temp_v0 = (*((u16 *) (((u8 *) arg0) + 0x2C))) - 1;
  *((u16 *) (((u8 *) arg0) + 0x2C)) = temp_v0;
  if ((((s16) temp_v0) < 0) || (D_800249A4 != 0))
  {
    *((u16 *) (((u8 *) arg0) - 2)) = (*((u16 *) (((u8 *) arg0) - 2))) | 0x8000;
    D_800814A0[0] = D_800814A0[0] | 0x8000;
  }
}
