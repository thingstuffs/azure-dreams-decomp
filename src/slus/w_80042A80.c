#include "common.h"

#include "common.h"

typedef struct S_80042A80_Item
{
  u8 f0;
  u8 f1;
  u8 pad2;
  u8 f3;
} S_80042A80_Item;
typedef struct S_80042A80_Rec20
{
  u16 f0;
  u8 pad[18];
} S_80042A80_Rec20;
typedef struct S_80042A80_CategoryEntry
{
  u8 kind;
  u8 pad1[11];
  S_80042A80_Rec20 *records;
  u8 pad2[4];
} S_80042A80_CategoryEntry;
extern u8 D_80082E6A[9];
extern S_80042A80_Rec20 *D_80073470[3];
extern S_80042A80_CategoryEntry itemCategoryTable[];
s32 func_80042A80(S_80042A80_Item *a0)
{
  S_80042A80_CategoryEntry *cat;
  s32 result;
  s16 t;
  u8 kind;
  if (D_80082E6A[0] != 2)
  {
    return 0;
  }
  kind = a0->f1;
  if (kind == 4)
  {
    result = ((D_80073470[0][a0->f0].f0 & 0x400) != 0) << 10;
    if (a0->f3 & 0x80)
    {
      result |= 0x80;
    }
    return result;
  }
  if (3 > ((u32) (kind - 15)))
  {
    return a0->f3 & 0x80;
  }
  {
    S_80042A80_CategoryEntry *base = itemCategoryTable;
    u32 index = ((volatile S_80042A80_Item *) a0)->f1;
    cat = &base[index];
  }
  if (cat->kind != 0)
  {
    return 0;
  }
  t = cat->records[a0->f0].f0 & 0x400;
  ASM_KEEP(t);   /* MATCH pin: slus-diff */
  return t;
}
