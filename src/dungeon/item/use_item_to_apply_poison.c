#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "dungeon/item.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect.h"





/* cfail-repair: tf7-phase1-cache-v3 */
#include "dungeon/player/item.h"
void clear_slot_and_update_linked_state();                         /* extern */
void adjust_source_value_and_finalize();           /* extern */
s32 set_or_clear_actor_status_slot();        /* extern */
void place_actor_item();                 /* extern */
void display_item_status_message(void *entity, s32 item, s16 action_type);   /* extern */
s32 feed_actor_restore_mp();            /* extern */
extern u8 D_800E1729[17];

/* Handles an item action for an entity, including its effect and item cleanup. */
s32 use_item_to_apply_poison(ActorRecord *entity, s32 item, s16 action_type) {
    SpriteFrameState *tile;
    ObjectNodeHeader *node;

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = item;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, item, action_type);
        if (feed_actor_restore_mp(entity, (entity_action_selectors[entity->species] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }
    node = (ObjectNodeHeader *)entity - 1;
    tile = node->sprite;
    spawn_randomized_particle_burst((tile->tile_x << 6) | 0x20, (tile->tile_y << 6) | 0x20,
        entity->ground_height, 0x802080, 0x20, 1);
    /*
     * Original bug: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 when
     * insertion fails. This nonzero test suppresses feedback for success in slot 0 and gives
     * it for failure (-1). try_apply_confusion_status uses the correct nonnegative success
     * test.
     */
    if (((set_or_clear_actor_status_slot(entity, STATUS_POISON, 8) << 0x10) != 0) && (entity->flags14 & 0x4000)) {
        adjust_source_value_and_finalize(entity, D_800E1729);
    }
    clear_slot_and_update_linked_state(item);
    {
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    }
    return 1;
}
