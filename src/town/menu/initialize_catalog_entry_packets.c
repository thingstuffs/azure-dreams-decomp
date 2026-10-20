#include "common.h"

typedef struct S_80123238_0_pre {
    s8 unk_00;
    u8 pad_01[0x6];
    s8 unk_07;
    s8 unk_08;
    s8 unk_09;
} S_80123238_0_pre;

typedef struct S_80123238_0 {
    s8 unk_00;
} S_80123238_0;


typedef struct Row {
    u8 f0;
    s8 f1;
    s8 f2;
    s8 f3;
    s16 f4;
    s16 f6;
    s8 f8;
    s8 f9;
    s8 f10;
    s8 f11;
} Row;

extern Row D_801331D0[0x10];

/* Initializes 16 entries with fixed attributes and coordinates in a three-column grid. */
void initialize_catalog_entry_packets(void)
{
    s32 grid_row;
    s32 grid_col;
    s32 entry_index;
    s8 *entry_tail;
    Row *entry;

    entry = &D_801331D0[0];
    entry_index = 0;
    do {
        entry_tail = (s8 *)entry + 0xB;
        entry->f0 = 0xC0;
        ((S_80123238_0_pre *)entry_tail)[-1].unk_00 = 0x2C;
        entry->f2 = 0;
        entry->f3 = 0;
        entry->f4 = 6;
        entry->f6 = 0x7C81;
        grid_row = entry_index / 3;
        grid_col = entry_index % 3;
        entry_index += 1;
        ((S_80123238_0_pre *)entry_tail)[-1].unk_07 = (s8)(grid_col * 0x48);
        ((S_80123238_0_pre *)entry_tail)[-1].unk_08 = (s8)((grid_row * 0x10) - 0x80);
        ((S_80123238_0_pre *)entry_tail)[-1].unk_09 = 0x48;
        ((S_80123238_0 *)entry_tail)->unk_00 = 0x10;
        entry += 1;
    } while (entry_index < 0x10);
}
