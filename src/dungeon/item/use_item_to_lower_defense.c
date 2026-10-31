#include "shared/actor_property_flags.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 D_800E2082[];

#include "dungeon/player/item.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/player/state.h"
#include "engine/entity.h"

extern void display_item_status_message(void *entity, struct DungeonItemEntry *item, s32 message_kind);
extern void place_actor_item(void *object_context, struct DungeonItemEntry *target);
extern void play_sound_if_enabled(u32);

/* Applies a stat-reducing item to a target and handles item consumption. */
s32 use_item_to_lower_defense(ActorRecord *target, DungeonItemEntry *item, s16 use_type) {
    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_deferred_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, item, use_type);
        if (feed_actor_restore_mp(target, (entity_action_selectors[target->species] >> 6) & 3, 0) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    }

    if (target->current_defense >= 2) {
        play_sound_if_enabled(0x615);
        target->current_defense--;
        apply_entity_effects(target);
        if (target->flags14 & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, D_800E2082);
        }
    }

    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
