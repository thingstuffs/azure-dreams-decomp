#include "common.h"

typedef struct TownEntry {
    u8 field0;
    u8 field1;
    u16 field2;
    s32 field4;
} TownEntry;

typedef struct TownState {
    u8 pad0[0x2C];
    u8 *field2C;
} TownState;

extern TownEntry D_800CF720[];
extern TownState D_801131B8;
extern s32 func_8008ACE8(s32 index, TownEntry *entry);
extern void func_8008ACAC(void *dst, void *src, s32 value);

/* Shifts town entries up one slot and relocates their associated data by the given offset. */
void func_8008AD90(s32 count, s32 data_offset) {
    TownEntry *entries;
    TownState *state;
    s32 src_index;
    s32 entry_value;
    u8 *entry_data;

    if (count != 0) {
        entries = D_800CF720;
        state = &D_801131B8;
        do {
            TownEntry *dst_entry = (TownEntry *)((count << 3) + (unsigned long)entries);
            src_index = count - 1;
            dst_entry->field0 = entries[src_index].field0;
            dst_entry->field1 = entries[src_index].field1;
            dst_entry->field2 = entries[src_index].field2;
            entry_value = entries[src_index].field4;
            dst_entry->field4 = entry_value;
            entry_data = state->field2C + func_8008ACE8(src_index, dst_entry);
            func_8008ACAC(entry_data + data_offset, entry_data, entry_value);
            count = src_index;
        } while (count != 0);
    }
}
