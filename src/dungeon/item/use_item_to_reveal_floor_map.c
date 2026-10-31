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
#include "dungeon/effect/screen.h"


extern u8 D_800E11FD[];

#include "dungeon/player/item.h"
#include "dungeon/actor.h"

extern s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void clear_slot_and_update_linked_state(DungeonItemEntry *slot);
extern void display_formatted_context_message(void *, s32, s16);
extern void play_sound_if_enabled(s32);
extern void place_actor_item(void *object_context, struct DungeonItemEntry *target);
extern void display_actor_item_status_message(void *, struct DungeonItemEntry *, s16);

/* Applies an item to the target and removes it when consumed. */
s32 use_item_to_reveal_floor_map(ActorRecord *target, DungeonItemEntry *item, s16 target_kind, s32 target_data)
{
    if (target_kind == 13) {
        return process_record_and_update_linked_state(item, target_data);
    }

    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, item, target_kind);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[(*((u8 *)&target->unk_10 + 3))] & 3,
                          item) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    } else {
        display_formatted_context_message(D_800E11FD, target_data, target_kind);
        pack_and_submit_cell_height_levels();
        dungeon_floor_flags |= FLOOR_MAP_VIEW_HOLD;
        play_sound_if_enabled(0x80F);
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(item);
    return 1;
}
