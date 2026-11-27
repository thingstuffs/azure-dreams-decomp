#include "common.h"
#include "engine/resource.h"
#include "sdk/memory.h"

typedef struct TownEntry {
    s8 flag_bit;
    s8 high_key;
    s16 low_key;
    s32 size;
} TownEntry;

typedef struct TownState {
    u8 pad0[0x2C];
    u8 *cache_buffer;
} TownState;

extern TownEntry resource_cache_records[];
extern TownState town_resource_context;

extern s32 sum_resource_bytes(s32);
extern void shift_resource_entries_and_data(s32, s32);

/* Move the selected entry and its data to the first slot. */
void move_resource_to_front(s32 entry_index)
{
    TownEntry *entries;
    TownEntry *entry;
    TownState *state;
    void *scratch;
    s32 saved_field0;
    s32 saved_field1;
    s32 saved_field2;
    s32 data_size;
    s32 data_offset;

    entries = resource_cache_records;
    entry = &entries[entry_index];
    saved_field0 = entry->flag_bit;
    saved_field1 = entry->high_key;
    saved_field2 = entry->low_key;
    data_size = entry->size;

    scratch = alloc_gpu_scratch_ring(0x8000);
    data_offset = sum_resource_bytes(entry_index);
    state = &town_resource_context;
    memcpy(scratch, state->cache_buffer + data_offset, data_size);
    shift_resource_entries_and_data(entry_index, data_size);
    memcpy(state->cache_buffer, scratch, data_size);

    resource_cache_records[0].flag_bit = saved_field0;
    entries[0].high_key = saved_field1;
    entries[0].low_key = saved_field2;
    entries[0].size = data_size;
}
