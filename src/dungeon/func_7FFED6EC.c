#include "modules/dungeon_ovl_d54c.h"

void move_resource_to_front(s32 entry_index) {
    ovl_d54c_7FFED6EC_DungeonEntry *entries;
    ovl_d54c_7FFED6EC_DungeonEntry *entry;
    DungeonCacheState *state;
    s32 saved_field_0;
    s32 saved_field_1;
    s32 saved_field_2;
    s32 data_size;
    s32 scratch_buffer;

    entries = D_800CF720;
    entry = &entries[entry_index];
    saved_field_0 = entry->field_0;
    saved_field_1 = entry->field_1;
    saved_field_2 = entry->field_2;
    data_size = entry->field_4;
    scratch_buffer = alloc_gpu_scratch_ring(0x8000);
    func_80069ED8(scratch_buffer, D_801131B8.field_2C + sum_resource_bytes(entry_index), data_size);
    shift_resource_entries_and_data(entry_index, data_size);
    state = &D_801131B8;
    func_80069ED8(state->field_2C, scratch_buffer, data_size);
    D_800CF720[0].field_0 = saved_field_0;
    entries->field_1 = saved_field_1;
    entries->field_2 = saved_field_2;
    entries->field_4 = data_size;
}
