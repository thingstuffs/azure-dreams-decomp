#include "common.h"
#include "town/scene.h"

typedef struct TownEntry {
    u8 flag_bit;
    u8 high_key;
    u16 low_key;
    s32 size;
} TownEntry;

typedef struct TownState {
    u8 pad0[0x2C];
    u8 *cache_buffer;
} TownState;

extern TownEntry resource_cache_records[];
extern TownState town_resource_context;
extern s32 sum_resource_bytes(s32 index);

/* Shifts town entries up one slot and relocates their associated data by the given offset. */
void shift_resource_entries_and_data(s32 count, s32 data_offset) {
    TownEntry *entries;
    TownState *state;
    s32 src_index;
    s32 entry_value;
    u8 *entry_data;

    if (count != 0) {
        entries = resource_cache_records;
        state = &town_resource_context;
        do {
            TownEntry *dst_entry = (TownEntry *)((count << 3) + (unsigned long)entries);
            src_index = count - 1;
            dst_entry->flag_bit = entries[src_index].flag_bit;
            dst_entry->high_key = entries[src_index].high_key;
            dst_entry->low_key = entries[src_index].low_key;
            entry_value = entries[src_index].size;
            dst_entry->size = entry_value;
            entry_data = state->cache_buffer + sum_resource_bytes(src_index);
            copy_words_backward_from_offset(entry_data + data_offset, entry_data, entry_value);
            count = src_index;
        } while (count != 0);
    }
}
