#include "modules/dungeon_town_load.h"

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
