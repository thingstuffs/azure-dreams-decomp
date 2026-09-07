#include "common.h"

typedef struct
{
  u8 pad0[0x10];
  u8 kind;
  u8 pad1[3];
} S_8004951C_CatEntry;

typedef struct
{
  u8 unk0;
  u8 unk1;
  s8 unk2;
  u8 unk3;
} S_8004951C_Item;

typedef struct
{
  u8 pad[0x28];
  u8 unk28;
} S_800492B0_Ret;

typedef struct
{
  u8 unk0;
  u8 pad[0xF];
} S_80082E6A;

extern S_8004951C_CatEntry itemCategoryTable[];
extern S_80082E6A D_80082E6A;
extern void *memset(void *, s32, s32);
extern s32 func_80042A80(void *);
extern s32 func_800438E4(void *);
extern S_800492B0_Ret *func_800492B0(s32);
extern void func_8004E5A0(s32, s32, u8 *);
extern u8 *func_8004E69C(u8 *);
extern s32 func_8004E298(s32, u8 *, s32);

s32 func_8004951C(s32 arg0, S_8004951C_Item *arg1)
{
  u8 buf[0x20];
  s32 cat;
  s32 kind;

  memset(buf, 0x20, 0x20);
  buf[0x1F] = 0;

  if ((D_80082E6A.unk0 == 2) && (func_80042A80(arg1) != 0))
  {
    return 0;
  }

  cat = arg1->unk1;
  kind = itemCategoryTable[cat].kind;
  if (kind >= 4)
  {
    return 0;
  }

  if (kind == 3)
  {
    s32 mask = arg1->unk3 & 0x1F;
    if ((mask < 0x14) && (D_80082E6A.unk0 != 1))
    {
      if (func_800492B0(mask)->unk28 == 0)
      {
        buf[0] = 0x7A;
      }
    }
  }
  else
  {
    if (arg1->unk1 == 18)
    {
      if (D_80082E6A.unk0 != 1)
      {
        func_8004E5A0(0x64 - arg1->unk2, 3, &buf[9]);
        func_8004E69C(&buf[9]);
        buf[0xC] = 0xA;
        buf[0xD] = 9;
        buf[0xE] = 0x39;
        buf[0x12] = 0x25;
      }
    }
    else if (arg1->unk1 == 4)
    {
      func_8004E5A0(arg1->unk2, 2, &buf[0xB]);
      func_8004E69C(&buf[0xB]);
    }
    else if (arg1->unk1 == 14)
    {
      func_8004E5A0(func_800438E4(arg1), 5, &buf[6]);
      func_8004E69C(&buf[6]);
      buf[0xB] = 0xA;
      buf[0xC] = 9;
      buf[0xD] = 0x39;
      buf[0x10] = 0x47;
    }
    else if (kind == 1)
    {
      s8 v = arg1->unk2;
      if (v != 0)
      {
        buf[0xA] = (v > 0) ? (0x6B) : (0x6C);
        func_8004E5A0((arg1->unk2 >= 0) ? (arg1->unk2) : (-arg1->unk2), 2, &buf[0xB]);
        func_8004E69C(&buf[0xB]);
      }
    }

    if (kind == 1)
    {
      if (arg1->unk3 & 0x40)
      {
        buf[0xD] = 0xA;
        buf[0xE] = 0x7A;
      }
      if (arg1->unk3 & 0x20)
      {
        buf[0] = 0x79;
      }
    }
  }

  return func_8004E298(arg0, buf, 0);
}
