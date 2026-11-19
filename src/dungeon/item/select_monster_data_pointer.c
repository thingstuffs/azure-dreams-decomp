#include "dungeon/player/held_item_kind_data.h"
#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"


/* Selects a table entry address, fixed buffer, or current data pointer by ID. */
u8 *select_item_record_pointer(s32 selector_id) {
    s16 selector_index = selector_id - 1;
    DungeonItemEntry *result;
    if (selector_index < 0x14) {
        result = &((DungeonItemEntry *)0x80010248)[selector_index];
    } else if (selector_index != 0x14) {
        result = ((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry;
    } else {
        result = &held_item_record;
    }
    return (u8 *)result;
}

/* MECHANISM: Frameless s16 selector preserves the retail a0 lifetime and CFG. */
