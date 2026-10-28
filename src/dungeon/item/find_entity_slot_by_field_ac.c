#include "dungeon/item/actor_target.h"
#include "common.h"
#include "shared/record_ptrs.h"

/* Finds the first matching value in the four slots at offset 0xAC, or returns -1. */
s32 find_entity_slot_by_field_ac(void *target_value) {
    s32 slot;
    void **slot_ptr;
    void *slot_value;
    s16 match_index;

    slot = 0;
    slot_ptr = (void **)dungeon_actor_ring_anchor;
    do {
        slot_value = slot_ptr[0x2B];
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
