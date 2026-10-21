#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 D_800E2082[];

extern s32 begin_deferred_item_action(void *, u8 *, u8 *, void *);
extern void display_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);
extern void place_actor_item(void *, s32);
extern void play_sound_if_enabled(u32);
extern void apply_entity_effects(void *);
extern void adjust_source_value_and_finalize(void *, u8 *);
extern void clear_slot_and_update_linked_state(s32);

/* Applies a stat-reducing item to a target and handles item consumption. */
s32 use_item_to_lower_defense(void *target, s32 item, s16 use_type) {
    if (target == dungeon_actor_ring_anchor) {
        *(s32 *)((u8 *)target + 0x110) = item;
        begin_deferred_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, item, use_type);
        if (feed_actor_restore_mp(target, (entity_action_selectors[*((u8 *)target + 0x13)] >> 6) & 3, 0) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    }

    if (*((u8 *)target + 0x27) >= 2) {
        play_sound_if_enabled(0x615);
        (*((u8 *)target + 0x27))--;
        apply_entity_effects(target);
        if (*(s32 *)((u8 *)target + 0x14) & 0x4000) {
            adjust_source_value_and_finalize(target, D_800E2082);
        }
    }

    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
