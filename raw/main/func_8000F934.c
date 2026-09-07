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

void func_80022934(void *arg0)
{
    unsigned long table_offset;
    s32 i;
    s32 x;
    s32 record_offset;
    MainEntry *entry;
    u8 *entry_source;
    unsigned long table_base;
    unsigned long table_page;

    i = 0;
    table_page = (unsigned long)D_80030000;
    ASM_USE_NV(table_page);
    table_base = table_page - 0x7F4C;
    record_offset = 0x114;
    if (arg0 != 0) {
        x = i;
    } else {
        x = i;
    }
    entry_source = arg0;
    do {
        s32 selector;
        void *call_arg0;

        call_arg0 = (u8 *)arg0 + record_offset;
        i++;
        i--;
        entry_source++;
        entry_source--;
        x++;
        x--;
        record_offset++;
        record_offset--;
        record_offset += 0x180;
        entry = *(MainEntry **)(entry_source + 0x8CC);
        entry_source += 4;
        entry->position->x = 0x124 - (*(s32 *)((u8 *)arg0 + 0x18) / 2);
        table_offset = i * 4;
        entry->position->y = x - (*(s32 *)((u8 *)arg0 + 0x1C) / 2) + 0xFC;
        i++;
        x += 0x11;
        selector = *(s32 *)((u8 *)arg0 + 8);
        table_offset += (selector * 0x18) + table_base;
        table_offset = *(s32 *)table_offset;
        entry->value = func_8004DA74(call_arg0, (s32)table_offset, 1);
    } while (i < 5);
}
