#include "dungeon/player/held_item_kind_data.h"
#include "shared/game_state.h"
#include "common.h"
#include "dungeon/item/actor_target.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"

/* Selects an item record from the item table, the selected floor entry, or the held item. */
u8 *select_item_record_pointer(s32 selector_id) {
    s16 selector_index = selector_id - 1;
    DungeonItemEntry *result;
    if (selector_index < 0x14) {
        result = &(GAME_STATE->items)[selector_index];
    } else if (selector_index != 0x14) {
        result = ((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry;
    } else {
        result = &held_item_record;
    }
    return (u8 *)result;
}
