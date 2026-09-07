#include "common.h"

extern s32 D_800814A0_loop __attribute__((section(".data")));
extern s32 D_800814A0_tail __attribute__((section(".data")));
__asm__(".set D_800814A0_loop, 0x800814A0\n.set D_800814A0_tail, 0x800814A0");
typedef struct A0
{
  u16 pad0[3];
  u16 unk6;
  u8 pad8[0x14];
  int unk1C;
} A0;
typedef struct FrameB
{
  s16 unk0;
  u16 unk2;
  u16 unk4;
  s16 unk6;
  u8 pad8[8];
} FrameB;
typedef struct AnimSub
{
  s16 pad0[3];
  s16 unk6;
  s16 pad8;
  s16 unkA;
  u16 unkC;
  s16 unkE;
  s16 unk10;
} AnimSub;
typedef struct Ent
{
  u16 pad[0xF];
  u16 flags;
  AnimSub anim;
} Ent;
typedef struct S_8005313C
{
  A0 *unk0;
  s16 state;
  u16 counter;
  s16 unk8;
  s16 unkA;
  FrameB *unkC;
  Ent *unk10[16];
} S_8005313C;
extern void func_80052C10(s16, FrameB *);
void func_8005313C(S_8005313C *arg0)
{
  s16 *new_var;
  u16 tmp;
  s16 idx;
  Ent *ent;
  Ent *anim_ent;
  AnimSub *anim;
  FrameB *old;
  s16 nxt;
  int i;
  s32 mask;
  tmp = arg0->counter + 1;
  arg0->counter = tmp;
  switch (arg0->state)
  {
    case 0:
      if (arg0->unkA != 0)
    {
      arg0->unkA = 0;
      arg0->counter = 0;
      arg0->state = arg0->state + 1;
    }
      break;

    case 1:
      if (arg0->unkC->unk0 == ((s16) tmp))
    {
      do
      {
        idx = (arg0->unk8 + 1) % 16;
        arg0->unk8 = idx;
        anim_ent = arg0->unk10[idx];
        anim = &anim_ent->anim;
        if (anim->unk6 == 0)
        {
          anim->unk6 = 1;
          anim->unkA = arg0->unkC->unk2 - 0x180;
          anim->unk10 = arg0->unkC->unk2 - 0x180;
          anim->unkC = arg0->unkC->unk4;
          anim->unkE = (arg0->unkC->unk6 * 12) + 12;
          func_80052C10(arg0->unk8, arg0->unkC);
        }
        old = arg0->unkC;
        arg0->unkC = old + 1;
        nxt = old[1].unk0;
        if (nxt == 0)
        {
          arg0->counter = 0;
          arg0->state = (*(new_var = &arg0->state)) + 1;
          return;
        }
      }
      while (nxt == ((s16) arg0->counter));
    }
      break;

    case 2:
      if (((s16) tmp) >= 0x190)
    {
      arg0->unk0->unk1C = 0;
      arg0->unk0->unk6 = arg0->unk0->unk6 + 1;
      for (i = 0; i < 0x10; i++)
      {
        ent = arg0->unk10[i];
        mask = D_800814A0_loop | 0x8000;
        D_800814A0_loop = mask;
        ent->flags |= 0x8000;
      }

      *((u16 *) (((u8 *) arg0) - 2)) |= 0x8000;
      D_800814A0_tail = mask;
    }
      break;

  }

}
