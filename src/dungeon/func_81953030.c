#include "common.h"

extern s32 D_800814A8[];
extern int D_800814A0[];
extern void func_80024654(void *, s16, s16, s32, s32);
extern s16 D_800249A4;
extern u16 D_800249A6[5];

/* Processes both modes and sets completion flags on countdown expiry or an override. */
void func_80024830(void *state)
{
  s32 object_addr;
  u16 countdown;
  u16 *counter_base = D_800249A6;
  object_addr = ((s32) state) - 0x20;
  func_80024654(object_addr, *((s16 *) (((u8 *) state) + 0x26)), *((s16 *) (((u8 *) state) + 0x30)), ((s32 *) D_800814A8[0])[0x18], (counter_base[0]++, 0));
  func_80024654(object_addr, *((s16 *) (((u8 *) state) + 0x26)), *((s16 *) (((u8 *) state) + 0x30)), ((s32 *) D_800814A8[0])[0x18], 1);
  countdown = (*((u16 *) (((u8 *) state) + 0x2C))) - 1;
  *((u16 *) (((u8 *) state) + 0x2C)) = countdown;
  if ((((s16) countdown) < 0) || (D_800249A4 != 0))
  {
    *((u16 *) (((u8 *) state) - 2)) = (*((u16 *) (((u8 *) state) - 2))) | 0x8000;
    D_800814A0[0] = D_800814A0[0] | 0x8000;
  }
}
