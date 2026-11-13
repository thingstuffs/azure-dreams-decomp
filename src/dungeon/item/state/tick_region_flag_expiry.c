#include "shared/object_node.h"
#include "shared/dungeon_floor.h"
#include "shared/item_ids.h"
#include "dungeon/level/room_flags.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/item/message.h"
#include "dungeon/item/state.h"
#include "dungeon/data.h"
extern s32 D_800E18C8;
/* Counts active dungeon ticks, optionally reports expiry and clears room flag 2, then removes the timer. */
void tick_region_flag_expiry(RegionFlagExpiryBody *state)
{
    s32 countdown;
    s32 entry_index;
    if (dungeon_status_flags_alias & 0x10) {
        countdown = state->ticks_remaining - 1;
        state->ticks_remaining = countdown;
        if ((countdown << 16) <= 0) {
            if (state->item_id == ITEM_HOLY_BELL) {
                display_formatted_context_message(&D_800E18C8);
                entry_index = state->room_index;
                dungeon_rooms[entry_index].flags = dungeon_rooms[entry_index].flags & ROOM_HOLY_BEAM_CLEAR_MASK;
            }
            NODE_HEADER(state)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
