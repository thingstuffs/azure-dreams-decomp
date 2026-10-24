#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

#include "dungeon/player/item.h"
extern void clear_slot_and_update_linked_state(s32);
extern void adjust_source_value_and_finalize(void *, void *);
extern s32 set_or_clear_actor_status_slot(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void place_actor_item(void *, s32);
extern void display_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);

extern u8 D_800E1827[];

/* Applies the item's status effect to the target and consumes the handled item. */
s32 use_item_to_apply_slow(void *target, s32 item, s16 use_kind)
{
    if (target == dungeon_actor_ring_anchor) {
        *(s32 *)((u8 *)target + 0x110) = item;
        begin_deferred_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, item, use_kind);
        if (feed_actor_restore_mp(
                target, (entity_action_selectors[*((u8 *)target + 0x13)] >> 6) & 3, 0) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    }

    /*
     * Original bug: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 when
     * insertion fails. This nonzero test suppresses feedback for success in slot 0 and gives
     * it for failure (-1). try_apply_confusion_status uses the correct nonnegative success
     * test.
     */
    if ((set_or_clear_actor_status_slot(target, STATUS_SPEED, -10) << 16) != 0) {
        play_sound_if_enabled(0x615);
        if (*(s32 *)((u8 *)target + 0x14) & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, D_800E1827);
        }
    }

    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
