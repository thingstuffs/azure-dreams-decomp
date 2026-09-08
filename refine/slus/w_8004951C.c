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

/* Formats and displays item modifiers and status markers. */
s32 func_8004951C(s32 text_target, S_8004951C_Item *item)
{
  u8 text[0x20];
  s32 category;
  s32 kind;

  memset(text, 0x20, 0x20);
  text[0x1F] = 0;

  if ((D_80082E6A.unk0 == 2) && (func_80042A80(item) != 0))
  {
    return 0;
  }

  category = item->unk1;
  kind = itemCategoryTable[category].kind;
  if (kind >= 4)
  {
    return 0;
  }

  if (kind == 3)
  {
    s32 subtype = item->unk3 & 0x1F;
    if ((subtype < 0x14) && (D_80082E6A.unk0 != 1))
    {
      if (func_800492B0(subtype)->unk28 == 0)
      {
        text[0] = 0x7A;
      }
    }
  }
  else
  {
    if (item->unk1 == 18)
    {
      if (D_80082E6A.unk0 != 1)
      {
        func_8004E5A0(0x64 - item->unk2, 3, &text[9]);
        func_8004E69C(&text[9]);
        text[0xC] = 0xA;
        text[0xD] = 9;
        text[0xE] = 0x39;
        text[0x12] = 0x25;
      }
    }
    else if (item->unk1 == 4)
    {
      func_8004E5A0(item->unk2, 2, &text[0xB]);
      func_8004E69C(&text[0xB]);
    }
    else if (item->unk1 == 14)
    {
      func_8004E5A0(func_800438E4(item), 5, &text[6]);
      func_8004E69C(&text[6]);
      text[0xB] = 0xA;
      text[0xC] = 9;
      text[0xD] = 0x39;
      text[0x10] = 0x47;
    }
    else if (kind == 1)
    {
      s8 modifier = item->unk2;
      if (modifier != 0)
      {
        text[0xA] = (modifier > 0) ? (0x6B) : (0x6C);
        func_8004E5A0((item->unk2 >= 0) ? (item->unk2) : (-item->unk2), 2, &text[0xB]);
        func_8004E69C(&text[0xB]);
      }
    }

    if (kind == 1)
    {
      if (item->unk3 & 0x40)
      {
        text[0xD] = 0xA;
        text[0xE] = 0x7A;
      }
      if (item->unk3 & 0x20)
      {
        text[0] = 0x79;
      }
    }
  }

  return func_8004E298(text_target, text, 0);
}
