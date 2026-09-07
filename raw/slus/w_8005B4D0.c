#include "common.h"
typedef struct S_80086A40
{
  s16 unk0;
  s16 unk2;
  u8 *unk4;
  u8 pad08[0x10 - 0x08];
  s32 unk10;
  u8 pad14[0x18 - 0x14];
  u8 unk18;
  u8 pad19[0x1B - 0x19];
  u8 unk1B;
} S_80086A40;
typedef struct S_80085458
{
  s16 unk00;
  u8 pad02[0x04 - 0x02];
  s16 unk04;
  s16 unk06;
  s16 unk08;
  s16 unk0A;
  u8 pad0C[0x10 - 0x0C];
  s16 unk10;
  s16 unk12;
  u8 unk14;
  u8 unk15;
  u8 unk16;
  u8 unk17;
  s16 unk18;
  u16 unk1A;
  u8 pad1C[0x20 - 0x1C];
  u8 unk20;
  u8 unk21;
  u8 unk22;
  u8 unk23;
  u8 pad24[0x5C - 0x24];
  s16 unk5C;
  u8 pad5E[0x60 - 0x5E];
  s32 unk60;
  s32 unk64;
  u8 pad68[0x78 - 0x68];
} S_80085458;
typedef struct S_8005B4D0_hdr
{
  u8 unk00;
  u8 unk01;
  u8 pad02[0x04 - 0x02];
  u8 unk04;
  u8 pad05[0x10 - 0x05];
} S_8005B4D0_hdr;
typedef struct S_8005B4D0_data
{
  u8 pad00[0x01 - 0x00];
  u8 unk01;
  u8 unk02;
  u8 unk03;
  u8 unk04;
  u8 unk05;
  u8 unk06;
  u8 unk07;
  u8 pad08[0x0C - 0x08];
  u8 unk0C;
  u8 unk0D;
  u8 pad0E[0x10 - 0x0E];
  u16 unk10;
  u16 unk12;
  u8 pad14[0x16 - 0x14];
  s16 unk16;
  u8 pad18[0x20 - 0x18];
} S_8005B4D0_data;
typedef struct S_8005B4D0_req
{
  s32 f00;
  s32 f04;
  s16 f08;
  s16 f0a;
  s16 f0c;
  s16 f0e;
  u8 pad10[0x16 - 0x10];
  s16 f16;
  s16 f18;
  u8 pad1a[0x1C - 0x1A];
  s32 f1c;
  s32 f20;
  s32 f24;
  u8 pad28[0x3A - 0x28];
  s16 f3a;
  s16 f3c;
  u8 pad3e[0x40 - 0x3E];
} S_8005B4D0_req;
extern s32 D_80073734[4];
extern s32 D_80073740[128];
extern S_80085458 D_80085458[64];
extern s32 D_80085F98[4];
extern S_80086A40 D_80086A40[16];
extern S_80086A40 D_80086A40_C[16] __asm__("D_80086A40");
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 arg0);
extern void func_8005EC0C(void *a0);
extern s32 func_8005E4A0(s32 a0, s32 a1);
void func_8005B4D0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4)
{
  S_8005B4D0_req req;
  u16 sp50;
  u16 sp52;
  s32 sp54;
  s32 active;
  u8 *blob;
  u8 *blob2;
  S_8005B4D0_hdr *grp;
  S_8005B4D0_data *rgn;
  s32 idx;
  s32 kg;
  s32 slot;
  s32 s4;
  s32 i;
  u8 *p;
  s32 r;
  s32 sum;
  s32 n;
  s16 *vp;
  s32 pan;
  s32 vol;
  s32 lvol;
  s32 rvol;
  u16 t10;
  u16 t12;
  s32 tv;
  s32 rv;
  s32 a0h;
  i = 0;
  active = 0;
  kg = arg0 & 0x7F;
  a0h = arg0 >> 8;
  D_80085F98[0] = 1;
  sp50 = arg2;
  sp52 = arg3;
  blob2 = D_80086A40[(s16) a0h].unk4;
  idx = a0h;
  blob = blob2;
  if (kg != 0)
  {
    p = blob2;
    do
    {
      if (((S_8005B4D0_hdr *) (p + 0x20))->unk00 != 0)
      {
        active += 1;
      }
      p += 0x10;
      i += 1;
    }
    while (i < kg);
  }

  s4 = 0;
  grp = (S_8005B4D0_hdr *) (blob + ((kg * 0x10) + 0x20));
  sp54 = arg1 >> 8;
  if (grp->unk00 == 0)
  {
    D_80085F98[0] = 0;
    return;
  }
  do
  {
    rgn = (S_8005B4D0_data *) (blob + ((((active * 0x10) + s4) << 5) + 0x820));
    if ((sp54 >= ((s32) rgn->unk06)) && (((s32) rgn->unk07) >= sp54))
    {
      slot = 0;
      while (1)
      {
        if (func_8005EB78(D_80073740[slot]) == 0)
        {
          break;
        }
        slot += 1;
        if ((D_80073734[0] - 1) < slot)
        {
          slot = -1;
          break;
        }
      }

      if (slot == (-1))
      {
        slot = 0;
        while (1)
        {
          if (D_80085458[slot].unk1A == 0)
          {
            break;
          }
          slot += 1;
          if ((D_80073734[0] - 1) < slot)
          {
            slot = -1;
            break;
          }
        }

      }
      if (slot != (-1))
      {
        func_80056DB4(slot);
        do
        {
          func_8005E97C(0, D_80073740[slot]);
          r = func_8005EB78(D_80073740[slot]);
        }
        while ((r != 2) && (r != 0));
        i = 0;
        sum = 0;
        vp = (s16 *) ((D_80086A40[(s16) idx].unk4 + ((*((u16 *) (blob2 + 0x12))) << 9)) + 0x820);
        n = rgn->unk16;
        if (n > 0)
        {
          do
          {
            sum += *((u16 *) vp);
            vp += 1;
            i += 1;
          }
          while (i < n);
        }
        sum <<= 3;
        req.f04 = 0x701EF;
        req.f0c = 0;
        req.f0e = 0;
        req.f00 = D_80073740[slot];
        req.f1c = D_80086A40_C[(s16) idx].unk10 + sum;
        t10 = rgn->unk10;
        req.f3a = t10;
        D_80085458[slot].unk60 = t10;
        t12 = rgn->unk12;
        req.f3c = t12;
        D_80085458[slot].unk64 = t12;
        if (rgn->unk10 & 0x80) { req.f24 = 5; } else { req.f24 = 1; }
        req.f20 = req.f1c;
        D_80085458[slot].unk22 = rgn->unk04;
        D_80085458[slot].unk23 = rgn->unk05;
        D_80085458[slot].unk21 = rgn->unk0C;
        D_80085458[slot].unk20 = rgn->unk0D;
        D_80085458[slot].unk00 = slot;
        D_80085458[slot].unk04 = kg;
        D_80085458[slot].unk08 = s4;
        D_80085458[slot].unk0A = arg1 >> 8;
        D_80085458[slot].unk06 = 0x11;
        D_80085458[slot].unk1A = 1;
        D_80085458[slot].unk14 = grp->unk01;
        D_80085458[slot].unk16 = grp->unk04;
        D_80085458[slot].unk15 = rgn->unk02;
        D_80085458[slot].unk17 = rgn->unk03;
        D_80085458[slot].unk5C = idx;
        pan = ((D_80086A40[(s16) idx].unk1B + D_80085458[slot].unk16) + D_80085458[slot].unk17) - 0x80;
        if (pan < 0)
        {
          pan = 0;
        }
        if (pan >= 0x80)
        {
          pan = 0x7F;
        }
        D_80085458[slot].unk18 = pan;
        vol = ((D_80086A40[(s16) idx].unk18 * D_80085458[slot].unk14) * D_80085458[slot].unk15) >> 7;
        if (pan >= 0x40)
        {
          rvol = vol;
          lvol = ((0x40 - (pan & 0x3F)) * (rvol << 1)) >> 7;
        }
        else
        {
          lvol = vol;
          rvol = (pan * (lvol << 1)) >> 7;
        }
        lvol = (lvol * D_80086A40[(s16) idx].unk18) >> 7;
        rvol = (rvol * D_80086A40[(s16) idx].unk18) >> 7;
        tv = lvol * sp50;
        rv = rvol * sp52;
        D_80085458[slot].unk10 = tv >> 7;
        D_80085458[slot].unk12 = rv >> 7;
        req.f08 = (u16) D_80085458[slot].unk10;
        req.f0a = D_80085458[slot].unk12;
        req.f16 = arg1;
        if (rgn->unk05 != 0)
        {
          req.f18 = ((rgn->unk04 - 1) << 8) | (0x7F - rgn->unk05);
        }
        else
        {
          req.f18 = (rgn->unk04 << 8) | rgn->unk05;
        }
        func_8005EC0C(&req);
        if ((rgn->unk01 & 4) || (arg4 != 0))
        {
          func_8005E4A0(1, D_80073740[slot]);
        }
        else
        {
          func_8005E4A0(0, D_80073740[slot]);
        }
      }
    }
    s4 += 1;
  }
  while (s4 < ((s32) grp->unk00));
  D_80085F98[0] = 0;
}
