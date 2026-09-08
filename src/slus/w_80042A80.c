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
/* Returns category-dependent item flags when the current mode is 2. */
s32 func_80042A80(S_80042A80_Item *item)
{
  S_80042A80_CategoryEntry *category;
  s32 item_flags;
  s16 record_flags;
  u8 kind;
  if (D_80082E6A[0] != 2)
  {
    return 0;
  }
  kind = item->f1;
  if (kind == 4)
  {
    item_flags = ((D_80073470[0][item->f0].f0 & 0x400) != 0) << 10;
    if (item->f3 & 0x80)
    {
      item_flags |= 0x80;
    }
    return item_flags;
  }
  if (3 > ((u32) (kind - 15)))
  {
    return item->f3 & 0x80;
  }
  {
    S_80042A80_CategoryEntry *categories = itemCategoryTable;
    u32 category_index = ((volatile S_80042A80_Item *) item)->f1;
    category = &categories[category_index];
  }
  if (category->kind != 0)
  {
    return 0;
  }
  record_flags = category->records[item->f0].f0 & 0x400;
  ASM_KEEP(record_flags);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
  return record_flags;
}
