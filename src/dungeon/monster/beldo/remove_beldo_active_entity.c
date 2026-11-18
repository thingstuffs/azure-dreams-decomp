#include "shared/object_node_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/monster/beldo/command_ticks_data.h"
#include "dungeon/player/object.h"

#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

extern void unlink_entity_node(void *node);

/* Removes the active Beldo entity: detaches its record, updates the map cell flags at its tile,
 * unlinks its node and marks it for removal, then clears the slot. */
void remove_beldo_active_entity(void) {
    ObjectNodeHeader **active_slot;
    ObjectNodeHeader *active_obj;

    active_slot = &beldo_active_entity;
    active_obj = *active_slot;
    if (active_obj != 0) {
        ActorRecord *obj_state = NODE_BODY(active_obj);
        SpriteFrameState *obj_data = active_obj->sprite;
        s32 sound_x;
        s32 sound_y;
        s32 effect_id;

        detach_record_and_update_slot_state(obj_state);
        sound_x = obj_data->tile_x;
        sound_y = obj_data->tile_y;
        effect_id = 0x3000;
        if (obj_state->flags1C & 0x2000) {
            effect_id = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, effect_id);
        unlink_entity_node(obj_state);
        NODE_HEADER(obj_state)->flags |= NODE_REMOVE;
        *active_slot = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
