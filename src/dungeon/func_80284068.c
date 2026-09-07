#include "common.h"
typedef struct
{
  u8 value[4];
} UnalignedWord;
typedef struct
{
  u32 words[0x23];
} Entry;
typedef struct
{
  u8 pad0000[0x244];
  UnalignedWord src;
  u8 pad0248[0x50];
  void *arg;
  u8 pad029C[0x1F48];
  UnalignedWord dest;
} Cursor;
typedef union
{
  u8 *raw;
  Cursor *entry;
} CursorPtr;
extern void func_80041E28(void *arg0, void *arg1);
extern s8 func_800422A8(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern u8 D_800E3DF0[];
extern u8 D_800E3E48[];
void func_80017068(void)
{
  s32 i;
  volatile u8 *clear;
  s32 offset;
  Entry *entry;
  Entry **table;
  int new_var;
  u8 *table_page;
  u8 *entry_page;
  i = 3;
  clear = (u8 *) 0x80010006;
  {
    u8 *init = (u8 *) 0x80010000;
    init[0x2194] = 5;
    init[0x21BA] = 5;
    init[0x2195] = 4;
    init[0x21BB] = 4;
    init[0x2196] = 4;
    init[0x2197] = 100;
    init[0x2199] = 16;
    init[0x21BC] = 16;
    *((s16 *) (init + 0x219A)) = 16;
    init[0x21A5] = 1;
    *((s32 *) (init + 0x21A8)) = 0x6000;
    *((s32 *) (init + 0x21B0)) = 0x6000;
    init[0x21A7] = 0;
    *((s32 *) (init + 0x21AC)) = 0;
    *((s16 *) (init + 0x21B4)) = 0;
    *((s16 *) (init + 0x21B6)) = 0;
    *((s16 *) (init + 0x21BE)) = 0x400;
  }
  do
  {
    clear[0x21C0] = 0;
    clear[0x21C1] = 0;
    ASM_USE_NV(i);   /* MATCH pin: keeps a constant in a register as retail does */
    clear -= 2;
  }
  while ((--i) >= 0);
  i = 19;
  table_page = D_800E3DF0;
  table = (Entry **) (table_page + 0x4C);
  offset = 0x63C;
  entry_page = D_800E3E48;
  new_var = 0x3E48;
  entry = (Entry *) (entry_page + 0xA64);
  {
    u8 *page = (u8 *) 0x80010000;
    page[0x21E0] = 0xFF;
    page[0x21E1] = 0xFF;
    *((s32 *) (page + 0x21E4)) = 0;
  }
  entry_init_loop:
  func_80041E28(entry, (void *) (0x800102F0 + offset));

  *(table--) = entry;
  offset -= 0x54;
  entry--;
  if ((--i) >= 0)
  {
    goto entry_init_loop;
  }
  i = 19;
  {
    volatile u8 *status = (volatile u8 *) 0x80010013;
    u8 *table_page2 = D_800E3DF0;
    Entry **table2 = (Entry **) (table_page2 + 0x4C);
    u8 *page = (u8 *) 0x800E0000;
    u8 *entry_base = page + new_var;
    Entry *entry2 = (Entry *) (entry_base + 0xA64);
    volatile u8 *dest;
    CursorPtr cursor;
    dest = (u8 *) 0x80010A64;
    cursor.raw = (u8 *) 0x80010050;
    do
    {
      cursor.entry->dest = cursor.entry->src;
      status[0x2238] = func_800422A8(cursor.entry->arg, (void *) 0x80010248, 4, 20);
      *((Entry *) (dest + 0x2260)) = *entry2;
      status[0x224C] = func_800422A8(*table2, page + 0x3E48, 0x8C, 20);
      table2--;
      entry2--;
      dest -= 0x8C;
      cursor.raw -= 4;
      status--;
    }
    while ((--i) >= 0);
  }
  {
    u8 *page = (u8 *) 0x80010000;
    *((s32 *) (page + 0x2D58)) = 0;
    *((s16 *) (page + 0x2D50)) = 0;
  }
}
