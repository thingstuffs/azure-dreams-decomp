#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "common.h"


/* Finds the first matching value in the four slots at offset 0xE4, or returns -1. */
s32 find_entity_slot_by_field_e4(s32 target_value) {
    s32 slot;
    s32 *slot_ptr;
    s32 slot_value;
    s16 match_index;

    slot = 0;
    slot_ptr = (s32 *)dungeon_actor_ring_anchor;
    do {
        slot_value = slot_ptr[0x39];
        if (slot_value != target_value) {
            slot++;
            slot_ptr++;
            continue;
        }
        match_index = (s16)slot;
        return match_index;
    } while (slot < 4);
    return -1;
}
