#include "dungeon/item.h"
#include "shared/actor_property_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
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
#include "dungeon/actor.h"
#include "shared/object_node.h"

extern u8 D_800E0F07[];



/* Apply an item effect to the entity and consume the item when handled. */
s32 use_item_to_restore_defense(ActorRecord *entity, DungeonItemEntry *item, s16 use_type) {
    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = item;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, item, use_type);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }

    create_timed_paired_particle_emitter(((ObjectNodeHeader *)entity - 1)->position, 0x40C040, entity);
    entity->current_defense = entity->base_defense;
    if (entity->flags14 & ACTOR_PARTY_MEMBER) {
        adjust_source_value_and_finalize(entity, D_800E0F07);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}
