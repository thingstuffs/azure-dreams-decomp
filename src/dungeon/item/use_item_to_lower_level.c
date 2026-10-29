#include "dungeon/actor/status.h"
#include "shared/entity_action_selectors.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"


typedef struct {
    u8 pad_0[0xA];
    u16 field_A;
} D_80083460_Type;


#include "dungeon/player/item.h"
#include "dungeon/item.h"
extern u8 D_800E173A[28];

/* Processes an entity's item interaction and consumes the item when finished. */
s32 use_item_to_lower_level(ActorRecord *entity, DungeonItemEntry *item, s16 action) {
    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = item;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, action);
        if (feed_actor_restore_mp(
                entity,
                (entity_action_selectors[entity->species] >> 6) & 3,
                0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }
    if (lower_entity_level(entity, 1) == 0) {
        adjust_source_value_and_finalize(entity, D_800E173A);
    }
    clear_slot_and_update_linked_state(item);
    {
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    }
    return 1;
}
