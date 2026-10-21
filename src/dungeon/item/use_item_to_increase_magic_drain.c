#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void begin_deferred_item_action(void *, void *, void *, void *);
extern void clear_slot_and_update_linked_state(s32);
extern void display_formatted_context_message(void *);
extern void adjust_source_value_and_finalize(void *, void *);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void apply_item_effect_at_entity_position(void *, s32);
extern void display_item_status_message(void *, s32, s16);
extern s32 generate_random_value(void);
extern s32 feed_actor_restore_mp(void *, s32, s32);
extern void create_colored_effect_with_event(void *source, s32 color, unsigned short event_id);

extern u8 D_800E10C0[];
extern u8 D_800E10F2[];

/* Applies an item effect with randomized duration and handles item consumption. */
s32 use_item_to_increase_magic_drain(void *target, s32 item, s16 message_kind)
{
    s32 random_value;

    if (target == D_800E3D7C) {
        *(s32 *)((u8 *)target + 0x110) = item;
        begin_deferred_item_action(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, item, message_kind);
        if (feed_actor_restore_mp(
                target, (entity_action_selectors[*((u8 *)target + 0x13)] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(target, item);
            return 1;
        }

        random_value = generate_random_value();
        set_or_clear_actor_status_slot(target, 15, (random_value & 0x1F) | 0x20);
        if (*(s32 *)((u8 *)target + 0x14) & 0x4000) {
            adjust_source_value_and_finalize(target, D_800E10C0);
        }
        create_colored_effect_with_event((u8 *)target - 0x20, 0x804040, 0x612);
    } else {
        display_formatted_context_message(D_800E10F2);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
