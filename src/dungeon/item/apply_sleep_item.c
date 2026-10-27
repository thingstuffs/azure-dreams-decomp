#include "shared/entity_action_selectors.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


#include "dungeon/player/item.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/state.h"
s32 play_sound_if_enabled(s32 query_value);
extern s32 try_apply_action_by_chance(void *actor, s32 chance, s32 action);


/* Process an entity's item, deferring the primary entity's handling and cleaning up completed uses. */
s32 apply_sleep_item(ActorRecord *entity, DungeonItemEntry *item, s16 use_type) {
    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = item;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }
    if ((s32)entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, use_type);
        if (feed_actor_restore_mp(entity,
                          (entity_action_selectors[entity->species] >> 6) & 3,
                          0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }
    if (try_apply_action_by_chance(entity, 0x400, 8) != 0) {
        play_sound_if_enabled(0x520);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
