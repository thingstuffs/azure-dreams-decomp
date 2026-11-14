#include "dungeon/level/floor_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E12A9[];

#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "dungeon/system.h"
#include "dungeon/item/message.h"

extern s32 resolve_item_attack(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/player/state/clear_slot_and_update_linked_state_api.h"

/* Applies a value according to the target and mode, then updates bookkeeping. */
s32 use_item_to_reveal_items(ActorRecord *target, DungeonItemEntry *value, s16 mode, s32 context)
{
    if (mode == 13) {
        return resolve_item_attack(value, context);
    }

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = value;
        begin_mode_selected_item_action(target, ((&view_reference_entity)), ((&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, value);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[(*(&target->unk_10 + 3))] & 3,
                          value) == 0) {
            place_actor_item(target, value);
            return 1;
        }
    } else {
        display_formatted_context_message(D_800E12A9);
        dungeon_floor_flags |= FLOOR_REVEAL_ITEMS;
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_item_slot(value);
    return 1;
}
