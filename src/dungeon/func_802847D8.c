#include "modules/dungeon_floor_generate.h"

void func_800177D8(s16 row_index, s16 first_byte, s16 second_byte, s16 value) {
    s32 row_offset;
    u16 entry_count;
    void *rows_base;
    void *entries_base;
    floor_generate_isolated_802847D8_S_800177D8_0 *row;
    floor_generate_isolated_802847D8_S_800177D8_1 *entry;

    rows_base = (void *)D_800E2970;
    row = (row_index * 0x14) + rows_base;
    if (row->unk_0A != 0) {
        row_offset = row_index << 6;
        entries_base = (void *)D_800E2C40;
        entry_count = row->unk_0E;
        row->unk_10 = row_offset + entries_base;
        entry = ((s32)(entry_count << 0x10) >> 0xE) + row_offset + entries_base;
        row->unk_0E = (u16)(entry_count + 1);
        entry->unk_02 = value;
        entry->unk_00 = first_byte;
        entry->unk_01 = second_byte;
    }
}
