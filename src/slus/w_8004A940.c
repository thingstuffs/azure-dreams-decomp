#include "common.h"

/* {category, index} pair table at raw address 0x80013564 (not referenced
   elsewhere in this TU via a %hi/%lo symbol, so materialized as a literal,
   matching sibling func_8004A784's treatment of the neighboring 0x800133E8
   table). */
typedef struct S_8004A940_Pair {
    s16 a;
    s16 b;
} S_8004A940_Pair;

/* 20-byte item record; offset 0xC holds a pointer this function writes. */
typedef struct S_8004A940_Rec {
    s16 f0;
    s16 f1;
    u8 pad1[8];
    void *ptr;
    u8 pad2[4];
} S_8004A940_Rec;

/* 20-byte category-table entry (same layout/stride as
   S_8004A658_CategoryEntry in src/w_8004A658.c); offset 0xC holds the
   records pointer. */
typedef struct S_8004A940_CategoryEntry {
    u8 pad0[0xC];
    S_8004A940_Rec *records;
    u8 pad1[4];
} S_8004A940_CategoryEntry;

extern S_8004A940_CategoryEntry itemCategoryTable[];

/* Assign consecutive 19-byte data blocks to the items selected by the category/index table. */
void func_8004A940(void)
{
    S_8004A940_Pair *item_pair = (S_8004A940_Pair *)0x80013564;
    void *item_data = (void *)0x800133E8;
    S_8004A940_CategoryEntry *category_table;
    s32 pair_index = 0;

    category_table = itemCategoryTable;
    for (; pair_index < 20; pair_index++) {
        if (item_pair->a != 0) {
            category_table[item_pair->a].records[item_pair->b].ptr = item_data;
        }
        item_pair++;
        item_data = (u8 *)item_data + 0x13;
    }
}
