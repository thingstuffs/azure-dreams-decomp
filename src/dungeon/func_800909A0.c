#include "common.h"
#include "m2c_compat.h"
extern s32 D_800E296C[3];

extern s32 D_800832B4[3];
struct S_8003E2D8;
typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern u16 D_800DCE60[];
extern u16 D_800120A2[5];
extern s16 D_800DD264[];
extern s16 D_800DCE66[5];
extern u8 D_80080A84[16];
s32 func_80033BC0();
s32 func_80096190();
s32 func_80096200();
s32 func_8009635C();
s32 func_800A2BDC();
M2C_UNK func_800DC888();
extern u16 D_800120A0[5];
extern s16 D_800DD26C[];
s32 func_8004D7A8(s32 arg0);
s32 func_8004D294(s32 arg0, void *arg1, s32 arg2);
s32 func_80096100(void *arg0)
{
  S_8003E2D8 *base;
  short stopped;
  short result;
  s32 changed;
  u16 value;
  u16 input_flags;
  stopped = 0;
  result = 0;
  changed = 0;
  base = &D_80083160;
  if (D_800E296C[0] & 0x40000)
  {
    stopped = 1;
  }
  else
  {
    input_flags = *(u16 *) 0x80013714;
    if (((input_flags & 0xC) || (input_flags & 1)) || (((u8 *) arg0)[0x9A] == 0x19))
    {
      stopped = 1;
    }
    else
      if ((func_800A2BDC(0) << 16) == 0)
    {
      result = 1;
    }
    else
    {
      stopped = 1;
    }
  }
  if (stopped == 0)
  {
    if (D_800832B4[0] == 0)
    {
      if (((*((s32 *) (((s8 *) base) + 8))) & 0x10) == 0)
      {
        if ((*((s32 *) (((s8 *) base) + 8))) & 8)
        {
          changed = 1;
          D_800DCE60[2] = D_800DCE60[2] - 0x200;
        }
        else
          if ((*((s32 *) (((s8 *) base) + 8))) & 4)
        {
          changed = 1;
          D_800DCE60[2] = D_800DCE60[2] + 0x200;
        }
      }
      if ((*((s32 *) (((s8 *) base) + 8))) & 0x10)
      {
        if ((*((s32 *) (((s8 *) base) + 0x10))) & 1)
        {
          changed = 1;
          value = (u16) ((D_800120A2[0] + 1) & 3);
          D_800120A2[0] = value;
          D_800DCE60[0] = (u16) D_800DD264[(u16) value];
        }
      }
      if (changed != 0)
      {
        D_800832B4[0] = 0;
        func_8004D7A8(1);
        func_8004D294(0, D_800DCE60, 1);
      }
    }
    if ((*((s32 *) (((s8 *) base) + 8))) & 0x10)
    {
      if ((*((s32 *) (((s8 *) base) + 0x10))) & 4)
      {
        value = (s16) ((D_800120A0[0] + 1) & 3);
        D_800120A0[0] = value;
        D_800E296C[0] |= 0x40;
        D_800DCE66[0] = D_800DD26C[(u16) value];
      }
    }
    if ((*((s32 *) (((s8 *) base) + 8))) & 0x10)
    {
      if ((*((s32 *) (((s8 *) base) + 0x10))) & 2)
      {
        func_800DC888();
      }
    }
    if (func_80033BC0(0xA2) != 0)
    {
      if ((*((s32 *) (((s8 *) base) + 0x10))) & 0xC0000)
      {
        D_80080A84[0] = 1;
      }
      else
        if ((*((s32 *) (((s8 *) base) + 8))) & 0x30000)
      {
        D_80080A84[0] = 2;
      }
    }
  }
  return result;
}
