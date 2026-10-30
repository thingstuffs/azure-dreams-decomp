#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

#include "dungeon/player/item.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/effect.h"

s32 play_sound_if_enabled(s32 query_value);
extern u16 entity_action_selectors[];

/* Handle item use on a target, deferring the player action or consuming the item. */
s32 apply_paralysis_item(ActorRecord *target, DungeonItemEntry *item, s16 use_type) {
    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_deferred_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }
    if ((s32)target <= 0x9FFFFFFFU) {
        display_item_status_message(target, item, use_type);
        if (feed_actor_restore_mp(target,
                          (entity_action_selectors[target->species] >> 6) & 3,
                          0) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    }
    if (try_apply_effect_four_by_chance(target, 0x400, 8) != 0) {
        play_sound_if_enabled(0x612);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
