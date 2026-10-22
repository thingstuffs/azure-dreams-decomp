#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/record_ptrs.h"

extern u8 held_item_record[];

/* Selects a table entry address, fixed buffer, or current data pointer by ID. */
u8 *select_item_record_pointer(s32 selector_id) {
    s16 selector_index = selector_id - 1;
    u8 *result;
    if (selector_index < 0x14) {
        result = (u8 *)(0x80010248 + (selector_index * (s32)sizeof(void *)));
    } else if (selector_index != 0x14) {
        result = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 0xF0);
    } else {
        result = held_item_record;
    }
    return result;
}

/* MECHANISM: Frameless s16 selector preserves the retail a0 lifetime and CFG. */
