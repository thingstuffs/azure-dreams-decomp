#include "dungeon/actor/status.h"
#include "shared/actor_status_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_property_flags.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/player.h"

#include "dungeon/player/item.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"
void display_formatted_context_message(void *context);                   /* extern */
void adjust_source_value_and_finalize(void *context, const void *source);           /* extern */
s32 play_sound_if_enabled(s32 query_value);                     /* extern */
extern u8 D_800E17C6[41];
extern u8 D_800E17EF[];
extern u8 D_800E180E[];

/* Processes an entity action, preserves its state flag, and updates the shared counter. */
s32 apply_familiar_magic_drain_item(ActorRecord *entity, DungeonItemEntry *action, s16 action_param) {
    DungeonGlobalStatus *counter_page;
    DungeonGlobalStatus *counter_base;
    s32 saved_flag;
    s32 flag_test;
    u32 flags;

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = action;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }
    if (((u32) (entity->species - 1) < 0x2EU) && ((u32) entity <= 0x9FFFFFFFU)) {
        display_item_status_message(entity, action, action_param);
        saved_flag = ((u32) ((u32)entity->flags1C) >> 3) & 1;
        if (feed_actor_restore_mp(entity, (entity_action_selectors[entity->species] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, action);
            return 1;
        }
        flag_test = saved_flag;
        if (flag_test != 0) {
            entity->flags1C = (u32) (((u32)entity->flags1C) | ACTOR_MP_EMPTY);
        }
        flags = ((u32)entity->flags1C);
        entity->mp_value.whole = 0;
        if (!(flags & 8)) {
            flag_test = flags & 0x80000;
            counter_page = (void *)0x80080000;
            if (flag_test != 0) {
                clear_player_linked_action_flags();
                counter_page = (void *)0x80080000;
            }
            counter_page = &g_dungeon_status.turn_scale;
            counter_page->activity_counts.parts.pending_action_count = (u16) (*(u16 *)&counter_page->activity_counts.parts.pending_action_count + 1);
        }
        play_sound_if_enabled(0x51E);
        if (entity->flags14 & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(entity, D_800E17C6);
        }
        clear_slot_and_update_linked_state(action);
    } else if (entity->species == 0) {
        display_formatted_context_message(&D_800E17EF);
        play_sound_if_enabled(0x506);
    } else {
        clear_slot_and_update_linked_state(action);
        display_formatted_context_message(&D_800E180E);
    }
    counter_base = &g_dungeon_status;
    counter_base->activity_counts.parts.pending_action_count = (u16) (((u16)counter_base->activity_counts.parts.pending_action_count) - 1);
    return 1;
}
