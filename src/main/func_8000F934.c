#include "common.h"

typedef struct MainPosition {
    u8 pad0[8];
    s16 x;
    s16 y;
} MainPosition;

typedef struct MainEntry {
    s32 value;
    MainPosition *position;
} MainEntry;

extern s32 func_8004DA74(void *arg0, s32 arg1, s32 arg2);
extern s32 D_800280B4[];
extern u8 D_80030000[];
__asm__(".set D_80030000, 0x80030000");

/* Positions five entries in a vertical list and initializes their values from the selected table. */
void func_80022934(void *context)
{
    unsigned long table_offset;
    s32 entry_index;
    s32 row_y;
    s32 record_offset;
    MainEntry *entry;
    u8 *entry_source;
    unsigned long table_base;
    unsigned long table_page;

    entry_index = 0;
    table_page = (unsigned long)D_80030000;
    ASM_USE_NV(table_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    table_base = table_page - 0x7F4C;
    record_offset = 0x114;
    if (context != 0) {
        row_y = entry_index;
    } else {
        row_y = entry_index;
    }
    entry_source = context;
    do {
        s32 table_index;
        void *record;

        record = (u8 *)context + record_offset;
        entry_index++;
        entry_index--;
        entry_source++;
        entry_source--;
        row_y++;
        row_y--;
        record_offset++;
        record_offset--;
        record_offset += 0x180;
        entry = *(MainEntry **)(entry_source + 0x8CC);
        entry_source += 4;
        entry->position->x = 0x124 - (*(s32 *)((u8 *)context + 0x18) / 2);
        table_offset = entry_index * 4;
        entry->position->y = row_y - (*(s32 *)((u8 *)context + 0x1C) / 2) + 0xFC;
        entry_index++;
        row_y += 0x11;
        table_index = *(s32 *)((u8 *)context + 8);
        table_offset += (table_index * 0x18) + table_base;
        table_offset = *(s32 *)table_offset;
        entry->value = func_8004DA74(record, (s32)table_offset, 1);
    } while (entry_index < 5);
}
