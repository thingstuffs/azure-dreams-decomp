/* Find free inventory slots and locate an item table entry. */

#include "common.h"
#include "m2c_compat.h"
#include "dungeon/system.h"



typedef struct S_80098FB0_0 {
    u8 pad_00[0x249];
    u8 unk_249;
} S_80098FB0_0;

/* Find the start of the last contiguous run of zero entries. */
s32 find_last_zero_entry_run_start(void) {
    s8 *entry_address;
    s32 run_start;
    s32 shifted_index;
    s32 entry_index;

    run_start = -1;
    for (entry_index = 0x13, entry_address = (s8 *)0x8001004C; entry_index >= 0; entry_index--, entry_address -= 4) {
        if (((S_80098FB0_0 *)entry_address)->unk_249 == 0) {
            run_start = entry_index;
        } else if (run_start >= 0) {
            break;
        }
    }
    shifted_index = run_start << 0x10;
    return shifted_index >> 0x10;
}

/* Find the first empty slot and clear its associated table entry. */
s32 find_and_clear_empty_item_slot(void) {
    s32 slot_index;
    s32 empty_index;
    s32 *base;

    base = (s32 *)0x80010000;
    empty_index = -1;
    for (slot_index = 0; slot_index < 20; slot_index++) {
        if (base[slot_index + 0xA7] == 0) {
            empty_index = slot_index;
            break;
        }
    }
    if (empty_index >= 0) {
        base[empty_index + 0xA8] = 0;
    }
    return (s16)empty_index;
}
/*
 * Searches up to 20 words at 0x8001029C, stopping at the first zero; returns the matching index or
 * -1.
 */
s32 find_table_value_index(s32 target_value) {
    s32 *table = (s32 *)0x80010000;
    s32 entry_index;
    for (entry_index = 0; entry_index < 20; entry_index++) {
        if (table[167 + entry_index] == 0)
            break;
        if (table[167 + entry_index] == target_value)
            return (s16)entry_index;
    }
    return -1;
}
