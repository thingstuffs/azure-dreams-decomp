#include "dungeon/level/floor_flags.h"
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
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void display_formatted_context_message(void *, s32, s16);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);

/* Applies a value according to the target and mode, then updates bookkeeping. */
s32 use_item_to_reveal_items(EntityRec *target, s32 value, s16 mode, s32 context)
{
    if (mode == 13) {
        return process_record_and_update_linked_state(value, context);
    }

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        target->unk_110 = value;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, value, mode);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                          value) == 0) {
            place_actor_item(target, value);
            return 1;
        }
    } else {
        display_formatted_context_message(D_800E12A9, context, mode);
        dungeon_floor_flags |= FLOOR_REVEAL_ITEMS;
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(value);
    return 1;
}
