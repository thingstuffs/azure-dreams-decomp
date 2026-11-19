#include "shared/actor_status_flags.h"
#include "dungeon/level/tile_flags.h"
#include "dungeon/player/held_item_kind_data.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "common.h"
#include "dungeon/player/state.h"
#include "dungeon/actor/effect.h"
#include "slus.h"


extern s16 find_table_value_index(DungeonItemEntry *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

/* Clears a slot and updates its associated entry or dungeon state. */
void clear_item_slot(DungeonItemEntry *slot) {
    s16 lookup_result;
    if (slot != 0) {
        *(s32 *)slot = 0;
        lookup_result = find_table_value_index(slot);
        if (lookup_result >= 0) {
            compact_item_entry_table(lookup_result);
            return;
        }
        if (slot == &held_item_record) {
            ActorRecord *state = dungeon_actor_ring_anchor;
            ((PlayerRecord *)state)->unk_124 = 0;
            state->flags1C &= ACTOR_CARRYING_CLEAR_MASK;
            return;
        }
        if (slot == &temporary_item_record || slot == ((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry) {
            s16 record_index;
            *(u32 *)&temporary_item_record = 0;
            record_index = get_bounded_stride_index(((s32 *)((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry), ((u8 *)dungeon_ground_items), 4, 0x40);
            if (record_index >= 0) {
                update_map_cell_flags_with_item_limit(dungeon_ground_item_positions[record_index].x, dungeon_ground_item_positions[record_index].y, TILE_HAS_ITEM);
            }
            *(s32 *)((PlayerRecord *)dungeon_actor_ring_anchor)->selected_floor_entry = 0;
        }
    }
}
