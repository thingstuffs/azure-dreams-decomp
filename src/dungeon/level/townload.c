#include "dungeon/level/townload.h"
#include "dungeon/level/townload.h"

s32 resource_value_table_contains(s32 value) {
    s32 i = 0;

    while (D_800CF85C[i] != 0) {
        if (value == D_800CF85C[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
#include "dungeon/level/townload.h"

s32 has_listed_resource_in_slots(void) {
    s32 slot;
    u8 *entry_indices;
    s32 *entries;
    s32 any_found;

    slot = 0;
    entry_indices = D_800CF828;
    entries = D_800CF838;
    for (; slot < 0xF; slot++) {
        s32 found = resource_value_table_contains(entries[*(u8 *)((u32)slot + (u32)entry_indices)]);

        if (found != 0) {
            any_found = 1;
            return any_found;
        }
    }
    any_found = 0;
    return any_found;
}
#include "dungeon/level/townload.h"

s32 find_slot_for_resource_entry(void) {
    s32 slot_index = 0;
    u8 *entry_indices = D_800CF828;
    s32 *entry_table = D_800CF838;
    u8 *target_entry = D_80080EA8;

    do {
        if (entry_table[*(u8 *)((s32)slot_index + (s32)entry_indices)] == (s32)target_entry)
            return slot_index;
        slot_index++;
    } while (slot_index < 15);
    return -1;
}
#include "dungeon/level/townload.h"

void reserve_twch_load(s32 entry_id) {
    s32 entry_index;
    s32 found;

    found = resource_value_table_contains(D_800CF838[entry_id]);
    entry_index = 0;
    if (found != 0) {
        entry_index = find_slot_for_resource_entry();
        if (entry_index >= 0) {
            D_800CF828[entry_index] = entry_id;
            return;
        }
        entry_index = 0;
    }

    do {
        if (D_800CF828[entry_index] == 0) {
            D_800CF828[entry_index] = entry_id;
            D_800CF828[entry_index + 1] = 0;
            return;
        }
        entry_index++;
    } while (entry_index < 15);
}
#include "dungeon/level/townload.h"

void func_8008B4B0(void) {
    s32 slot;
    u8 *entry_id;

    for (slot = 0; slot < 15; slot++) {
        entry_id = &D_800CF828[slot];
        if (*entry_id != 0) {
            file_load_com(D_800CF838[*entry_id]);
        }
    }
    if (has_listed_resource_in_slots() != 0) {
        D_800CF828[0] = 1;
        D_800CF828[1] = 0;
        return;
    }
    D_800CF828[0] = 0;
    return;
}
