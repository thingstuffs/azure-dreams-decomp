#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 D_800E17A1[];

extern s32 begin_deferred_item_action();
extern void display_item_status_message();
extern s32 feed_actor_restore_mp();
extern void apply_item_effect_at_entity_position();
extern void play_sound_if_enabled();
extern void apply_entity_effects();
extern void adjust_source_value_and_finalize();
extern void clear_slot_and_update_linked_state();

/* Apply the level-down item effect to an entity and finish item use. */
s32 use_item_to_lower_attack(void *entity, s32 item, s16 action)
{
    if (entity == D_800E3D7C) {
        *(s32 *)((u8 *)entity + 0x110) = item;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, item, action);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[*((u8 *)entity + 0x13)] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(entity, item);
            return 1;
        }
    }

    if (*((u8 *)entity + 0x26) >= 2) {
        play_sound_if_enabled(0x615);
        (*((u8 *)entity + 0x26))--;
        apply_entity_effects(entity);
        if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
            adjust_source_value_and_finalize(entity, D_800E17A1);
        }
    }

    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
