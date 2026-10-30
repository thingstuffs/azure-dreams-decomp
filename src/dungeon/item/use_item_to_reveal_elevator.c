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


extern u8 D_800E1224[];

#include "dungeon/player/item.h"
#include "dungeon/actor.h"

extern s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void clear_slot_and_update_linked_state(DungeonItemEntry *slot);
extern void display_formatted_context_message(void *, s32, s16);
extern void place_actor_item(void *object_context, struct DungeonItemEntry *target);
extern void display_actor_item_status_message(void *, struct DungeonItemEntry *, s16);

/* Dispatch an action by type and target, updating the shared action state. */
s32 use_item_to_reveal_elevator(EntityRec *target, DungeonItemEntry *action_id, s16 action_type, s32 action_param)
{
    if (action_type == 13) {
        return process_record_and_update_linked_state(action_id, action_param);
    }

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        target->unk_110 = action_id;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action_id, action_type);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                          action_id) == 0) {
            place_actor_item(target, action_id);
            return 1;
        }
    } else {
        display_formatted_context_message(D_800E1224, action_param, action_type);
        dungeon_floor_flags |= FLOOR_REVEAL_ELEVATOR;
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(action_id);
    return 1;
}
