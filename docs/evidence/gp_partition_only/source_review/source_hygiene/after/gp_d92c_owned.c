#include "common.h"

typedef struct
{
  char pad0[8];
  int field8;
  char padC[4];
  int field10;
} S_8003D92C_80083160;
extern S_8003D92C_80083160 D_80083160;
extern u8 D_80082E6F[16];
extern u8 D_80080A84;
extern short D_80080ABC;
extern short D_80080ABE;
extern short D_80080A94;
extern short D_80080A98;
extern short D_80080A9C;
extern u8 D_80080A8A;
extern u8 D_80080A88;
extern u8 D_80080AA0;
extern int D_80082E60[4];
extern void func_8003F320(void);
extern int func_80053EF0(int);
extern void func_8003E758(void);
extern void func_80044618(int);
extern short SD_Call(int a0);
extern void func_80040AA0(int);
extern void func_80053DCC(short arg0);
extern void func_80053DF0(short);
extern void func_80053E14(short a0);
extern void func_8003D468(void);

/* Handles a held button combination and restores saved settings when it triggers. */
int func_8003D92C(void)
{
  int trigger_flags;
  int held_flags;
  int flags;
  int saved_setting;
  S_8003D92C_80083160 *input_state;
  input_state = &D_80083160;
  if (D_80082E6F[0] & 0x80)
  {
    return 0;
  }
  trigger_flags = input_state->field10;
  if (trigger_flags & 0x100)
  {
    if (!(input_state->field8 & 0x800))
    {
      D_80080ABE = 1;
    }
  }
  else if (trigger_flags & 0x800)
  {
    if (input_state->field8 & 0x100)
    {
      D_80080ABE = 1;
    }
    else
    {
      D_80080ABE = 0;
      D_80080ABC = 0;
      return 0;
    }
  }
  held_flags = input_state->field8;
  if (!(held_flags & 0x100))
  {
    D_80080ABE = 0;
    D_80080ABC = 0;
    return 0;
  }
  if (D_80080ABE != 0)
  {
    if (held_flags & 0x800)
    {
      D_80080ABC += D_80080A84;
      if (D_80080ABC >= 0x169)
      {
        D_80080ABC = 0x168;
      }
    }
    else
    {
      D_80080ABC = 0;
    }
  }
  if ((0x78 / D_80080A84) < D_80080ABC)
  {
    D_80080ABE = 0;
    D_80080ABC = 0;
    func_8003F320();
    while (func_80053EF0(4) == 0x100)
    {
      func_8003E758();
      func_80044618(2);
    }

    SD_Call(0x74);
    while (func_80053EF0(4) != 0)
    {
      func_8003E758();
      func_80044618(2);
    }

    func_8003F320();
    func_80040AA0(3);
    {
      saved_setting = D_80080A94;
      flags = D_80082E60[0];
      D_80080A8A = 0;
      D_80080A88 = 0;
      D_80080AA0 = 0;
      D_80082E60[0] = flags & ~2;
      func_80053DCC(saved_setting);
    }
    func_80053DF0(D_80080A98);
    func_80053E14(D_80080A9C);
    SD_Call(0x7F);
    func_8003D468();
    D_80080A84 = 2;
    return 1;
  }
  return 0;
}
short D_80080ABC = 0;
short D_80080ABE = 0;
