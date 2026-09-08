#include "common.h"
typedef struct 
{
  u16 unk0;
  u16 unk2;
  u16 unk4;
  u16 unk6;
  u16 unk8;
  u16 unkA;
  u16 unkC;
  u16 unkE;
} S_8005FA34_ent;
typedef struct 
{
  S_8005FA34_ent *ptr;
  u32 pad2[2];
} S_80079958;
typedef struct 
{
  u32 unk0;
  u8 pad4[4];
  u16 unk8;
  u16 unkA;
  u16 unkC;
  u16 unkE;
  u16 unk10;
  u16 unk12;
  u16 unk14;
  u16 unk16;
  u16 unk18;
  u16 unk1A;
  s32 unk1C;
  s32 unk20;
  s32 unk24;
  s32 unk28;
  s32 unk2C;
  s16 unk30;
  s16 unk32;
  s16 unk34;
  s16 unk36;
  s16 unk38;
  s16 unk3A;
  s16 unk3C;
} S_8005FA34;
extern S_80079958 D_80079958;
extern u16 D_80079520[256];
extern s32 D_80079980[3];
extern s32 func_8005F90C(s32 a0, s32 a1, s32 a2, s32 a3);
void func_8005FA34(S_8005FA34 *arg0)
{
  s32 idx;
  s32 i;
  S_8005FA34_ent *ent;
  S_8005FA34_ent *entp;
  register s32 off ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  u16 *p;
  u16 *p2;
  s32 va;
  s32 vb;
  s16 ca;
  s16 cb;
  u16 pitch;
  s32 res;
  s32 shift;
  s32 e;
  s32 h;
  idx = -1;
  for (i = 0; i < 0x18; i++)
  {
    if (arg0->unk0 & (1 << i))
    {
      idx = i;
      break;
    }
  }

  if (idx == (-1))
  {
    return;
  }
  ca = 0;
  off = idx * 16;
  ent = D_80079958.ptr;
  ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  h = idx * 2;
  e = idx * 8;
  entp = (S_8005FA34_ent *)(off + (u32)ent);
  va = entp->unk0;
  vb = entp->unk2;
  if (va & 0x8000)
  {
    switch (va & 0xF000)
    {
      case 0x8000:
        ca = 1;
        break;

      case 0x9000:
        ca = 2;
        break;

      case 0xA000:
        ca = 3;
        break;

      case 0xB000:
        ca = 4;
        break;

      case 0xC000:
        ca = 5;
        break;

      case 0xD000:
        ca = 6;
        break;

      case 0xE000:
        ca = 7;
        break;

      case 0xF000:
        ca = 7;
        break;

    }

    va &= 0xFFF;
  }
  cb = 0;
  if (vb & 0x8000)
  {
    switch (vb & 0xF000)
    {
      case 0x8000:
        cb = 1;
        break;

      case 0x9000:
        cb = 2;
        break;

      case 0xA000:
        cb = 3;
        break;

      case 0xB000:
        cb = 4;
        break;

      case 0xC000:
        cb = 5;
        break;

      case 0xD000:
        cb = 6;
        break;

      case 0xE000:
        cb = 7;
        break;

      case 0xF000:
        cb = 7;
        break;

    }

    vb &= 0xFFF;
  }
  {
    u32 x = 0x8000;
    u32 y = (u16) va;
    arg0->unk8 = (y < 0x4000U) ? va : (y - x);
  }
  {
    u32 x = 0x8000;
    u32 y = (u16) vb;
    arg0->unkA = (y < 0x4000U) ? vb : (y - x);
  }
  arg0->unkE = cb;
  p = (u16 *) D_80079958.ptr;
  arg0->unkC = ca;
  arg0->unk10 = p[h + 0x100];
  arg0->unk12 = p[h + 0x101];
  pitch = p[e + 2];
  arg0->unk14 = pitch;
  va = D_80079520[idx];
  res = func_8005F90C(va >> 8, va & 0xFF, pitch, vb);
  if (res >= 0)
  {
    arg0->unk16 = (u16) res;
  }
  else
  {
    arg0->unk16 = 0;
  }
  arg0->unk18 = D_80079520[idx];
  p2 = (u16 *) D_80079958.ptr;
  shift = D_80079980[0];
  arg0->unk1A = p2[e + 6];
  arg0->unk1C = ((s32) p2[e + 3]) << shift;
  arg0->unk20 = ((s32) p2[e + 7]) << shift;
  {
    u16 f8;
    u16 fA;

    f8 = p2[e + 4];
    fA = p2[e + 5];
    if (f8 & 0x8000)
    {
      arg0->unk24 = 5;
    }
    else
    {
      arg0->unk24 = 1;
    }
    if ((fA & 0xE000) == 0xC000)
    {
      arg0->unk28 = 7;
    }
    else if ((fA & 0xE000) == 0x8000)
    {
      arg0->unk28 = 5;
    }
    else if ((fA & 0xE000) == 0x4000)
    {
      arg0->unk28 = 3;
    }
    else
    {
      arg0->unk28 = 1;
    }
    if (fA & 0x20)
    {
      arg0->unk2C = 7;
    }
    else
    {
      arg0->unk2C = 3;
    }
    arg0->unk30 = (s16) ((f8 >> 8) & 0x3F);
    arg0->unk32 = (s16) ((f8 & 0xF0) >> 4);
    arg0->unk34 = (s16) ((fA >> 6) & 0x7F);
    arg0->unk36 = (s16) (fA & 0x1F);
    arg0->unk38 = (s16) (f8 & 0xF);
    arg0->unk3A = f8;
    arg0->unk3C = fA;
  }
}
