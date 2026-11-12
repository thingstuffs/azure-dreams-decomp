#include "common.h"
#include "town/menu.h"
#include "town/menu/catalog_grid_data.h"

typedef struct S_80123238_0_pre {
    s8 unk_00;
    u8 pad_01[0x6];
    s8 unk_07;
    s8 unk_08;
    s8 unk_09;
} S_80123238_0_pre;

/* Initializes 16 entries with fixed attributes and coordinates in a three-column grid. */
void initialize_catalog_entry_packets(void)
{
    s32 grid_row;
    s32 grid_col;
    s32 entry_index;
    S_80123238_0_pre *entry_tail;
    CatalogGridPacket *entry;

    entry = &catalog_grid_packets[0];
    entry_index = 0;
    do {
        entry_tail = (S_80123238_0_pre *)((s8 *)entry + 0xB);
        entry->f0 = 0xC0;
        entry_tail[-1].unk_00 = 0x2C;
        entry->f2 = 0;
        entry->f3 = 0;
        entry->f4 = 6;
        entry->f6 = 0x7C81;
        grid_row = entry_index / 3;
        grid_col = entry_index % 3;
        entry_index += 1;
        entry_tail[-1].unk_07 = (s8)(grid_col * 0x48);
        entry_tail[-1].unk_08 = (s8)((grid_row * 0x10) - 0x80);
        entry_tail[-1].unk_09 = 0x48;
        entry_tail->unk_00 = 0x10;
        entry += 1;
    } while (entry_index < 0x10);
}
