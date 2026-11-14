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


extern u8 D_800E1258[];

#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "dungeon/system.h"
#include "dungeon/item/message.h"

extern s32 resolve_item_attack(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/player/state/clear_slot_and_update_linked_state_api.h"

/* Handles item use on a target and consumes the item when the action completes. */
s32 use_item_to_reveal_traps(ActorRecord *target, DungeonItemEntry *item, s16 use_type, s32 use_context)
{
    if (use_type == 13) {
        return resolve_item_attack(item, use_context);
    }

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_mode_selected_item_action(target, ((&view_reference_entity)), ((&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, item);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[(*(&target->unk_10 + 3))] & 3,
                          item) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    } else {
        display_formatted_context_message(D_800E1258);
        dungeon_floor_flags |= FLOOR_REVEAL_TRAPS;
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_item_slot(item);
    return 1;
}
