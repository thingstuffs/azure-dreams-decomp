#include "shared/actor_property_flags.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/state.h"

extern u8 D_800E17A1[];

#include "dungeon/player/item.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "engine/entity.h"

extern s32 play_sound_if_enabled(s32 query_value);

/* Apply the level-down item effect to an entity and finish item use. */
s32 use_item_to_lower_attack(void *entity, DungeonItemEntry *item, s16 action)
{
    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = item;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, item, action);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[*((u8 *)entity + 0x13)] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }

    if (*((u8 *)entity + 0x26) >= 2) {
        play_sound_if_enabled(0x615);
        (*((u8 *)entity + 0x26))--;
        apply_entity_effects(entity);
        if (*(s32 *)((u8 *)entity + 0x14) & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(entity, D_800E17A1);
        }
    }

    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
