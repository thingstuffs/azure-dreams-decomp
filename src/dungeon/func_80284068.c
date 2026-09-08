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
/* Initializes default state, builds the entry table, and snapshots entry data. */
void func_80017068(void)
{
  s32 slot_index;
  volatile u8 *clear_ptr;
  s32 source_offset;
  Entry *init_entry;
  Entry **table_slot;
  int entry_page_offset;
  u8 *table_base;
  u8 *entries_base;
  slot_index = 3;
  clear_ptr = (u8 *) 0x80010006;
  {
    u8 *state_base = (u8 *) 0x80010000;
    state_base[0x2194] = 5;
    state_base[0x21BA] = 5;
    state_base[0x2195] = 4;
    state_base[0x21BB] = 4;
    state_base[0x2196] = 4;
    state_base[0x2197] = 100;
    state_base[0x2199] = 16;
    state_base[0x21BC] = 16;
    *((s16 *) (state_base + 0x219A)) = 16;
    state_base[0x21A5] = 1;
    *((s32 *) (state_base + 0x21A8)) = 0x6000;
    *((s32 *) (state_base + 0x21B0)) = 0x6000;
    state_base[0x21A7] = 0;
    *((s32 *) (state_base + 0x21AC)) = 0;
    *((s16 *) (state_base + 0x21B4)) = 0;
    *((s16 *) (state_base + 0x21B6)) = 0;
    *((s16 *) (state_base + 0x21BE)) = 0x400;
  }
  do
  {
    clear_ptr[0x21C0] = 0;
    clear_ptr[0x21C1] = 0;
    ASM_USE_NV(slot_index);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    clear_ptr -= 2;
  }
  while ((--slot_index) >= 0);
  slot_index = 19;
  table_base = D_800E3DF0;
  table_slot = (Entry **) (table_base + 0x4C);
  source_offset = 0x63C;
  entries_base = D_800E3E48;
  entry_page_offset = 0x3E48;
  init_entry = (Entry *) (entries_base + 0xA64);
  {
    u8 *ram_page = (u8 *) 0x80010000;
    ram_page[0x21E0] = 0xFF;
    ram_page[0x21E1] = 0xFF;
    *((s32 *) (ram_page + 0x21E4)) = 0;
  }
  entry_init_loop:
  func_80041E28(init_entry, (void *) (0x800102F0 + source_offset));

  *(table_slot--) = init_entry;
  source_offset -= 0x54;
  init_entry--;
  if ((--slot_index) >= 0)
  {
    goto entry_init_loop;
  }
  slot_index = 19;
  {
    volatile u8 *index_ptr = (volatile u8 *) 0x80010013;
    u8 *copy_table_base = D_800E3DF0;
    Entry **copy_table_slot = (Entry **) (copy_table_base + 0x4C);
    u8 *ram_page = (u8 *) 0x800E0000;
    u8 *copy_entries_base = ram_page + entry_page_offset;
    Entry *copy_entry = (Entry *) (copy_entries_base + 0xA64);
    volatile u8 *copy_dest;
    CursorPtr word_cursor;
    copy_dest = (u8 *) 0x80010A64;
    word_cursor.raw = (u8 *) 0x80010050;
    do
    {
      word_cursor.entry->dest = word_cursor.entry->src;
      index_ptr[0x2238] = func_800422A8(word_cursor.entry->arg, (void *) 0x80010248, 4, 20);
      *((Entry *) (copy_dest + 0x2260)) = *copy_entry;
      index_ptr[0x224C] = func_800422A8(*copy_table_slot, ram_page + 0x3E48, 0x8C, 20);
      copy_table_slot--;
      copy_entry--;
      copy_dest -= 0x8C;
      word_cursor.raw -= 4;
      index_ptr--;
    }
    while ((--slot_index) >= 0);
  }
  {
    u8 *ram_page = (u8 *) 0x80010000;
    *((s32 *) (ram_page + 0x2D58)) = 0;
    *((s16 *) (ram_page + 0x2D50)) = 0;
  }
}
