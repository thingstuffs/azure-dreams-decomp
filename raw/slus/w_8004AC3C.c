#include "common.h"

#include "common.h"
typedef struct 
{
  u8 kind;
  u8 pad[0xB];
  void *records;
  u8 pad2[4];
} S_8004AC3C_CategoryEntry;
typedef struct 
{
  s16 a;
  s16 b;
  s32 f4;
  s32 f8;
  s32 fC;
  s32 f10;
} S_8004AC3C_Rec20;
typedef struct 
{
  s16 a;
  s16 b;
  s32 f4;
  s32 f8;
} S_8004AC3C_Rec12;
typedef struct 
{
  u8 unk0;
  u8 unk1;
  u8 unk2;
  u8 unk3;
} S_8004AC3C_Item;
typedef struct 
{
  u8 f0;
  u8 pad[0xF];
} S_80082E6A;
extern S_80082E6A D_80082E6A;
extern S_8004AC3C_CategoryEntry itemCategoryTable[];
extern s32 func_80049330(S_8004AC3C_Item *);
extern s32 func_80042A80(S_8004AC3C_Item *);
s32 func_8004AC3C(S_8004AC3C_Item *item, s32 *out)
{
  s32 flags;
  register S_8004AC3C_CategoryEntry *base ASM_REG("$3");
  S_8004AC3C_CategoryEntry *entry;
  s32 ret;
  *out = 0;
  if (D_80082E6A.f0 != 1)
  {
    if (item->unk1 == 0x13)
    {
      ret = func_80049330(item) + 0x34;
    }
    else
    {
      flags = func_80042A80(item);
      if (flags != 0)
      {
        if ((((u32) (item->unk1 - 0xF)) < 3U) || ((item->unk1 == 4) && ((flags & 0x400) == 0)))
        {
          ret = ((S_8004AC3C_Rec20 *) itemCategoryTable[((volatile S_8004AC3C_Item *) item)->unk1].records)[item->unk0].f4;
        }
        else
        {
          ret = ((S_8004AC3C_Rec20 *) itemCategoryTable[((volatile S_8004AC3C_Item *) item)->unk1].records)[item->unk0].fC;
        }
        *out = 4;
      }
      else
      {
        base = itemCategoryTable;
        entry = base + item->unk1;
        ASM_KEEP(base);
        ret = (entry->kind == 0) ? (((S_8004AC3C_Rec20 *) entry->records)[item->unk0].f4) : (((S_8004AC3C_Rec12 *) entry->records)[item->unk0].f4);
      }
    }
  }
  else
    if (item->unk1 == 0x13)
  {
    ret = 0x80010324 + ((item->unk3 & 0x1F) * 0x54);
  }
  else
  {
    if (item->unk1 == 0x16)
    {
      *out = 7;
    }
    base = itemCategoryTable;
    entry = base + item->unk1;
    ASM_KEEP(base);
    ret = (entry->kind == 0) ? (((S_8004AC3C_Rec20 *) entry->records)[item->unk0].f4) : (((S_8004AC3C_Rec12 *) entry->records)[item->unk0].f4);
  }
  return ret;
}
