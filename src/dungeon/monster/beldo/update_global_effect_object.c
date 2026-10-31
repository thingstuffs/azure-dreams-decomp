#include "shared/object_node_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

extern u8 *beldo_active_entity;

extern void * detach_record_and_update_slot_state(void *record);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern void unlink_entity_node(void *node);

/* Updates the active object, triggers its positional effect, and clears its slot. */
void update_global_effect_object(void) {
    u8 **active_slot;
    ObjectNodeHeader *active_obj;

    active_slot = &beldo_active_entity;
    active_obj = *active_slot;
    if (active_obj != 0) {
        u8 *obj_state = ((u8 *)active_obj) + 0x20;
        u8 *obj_data = *(u8 * *)&active_obj->sprite;
        s32 sound_x;
        s32 sound_y;
        s32 effect_id;

        detach_record_and_update_slot_state(obj_state);
        sound_x = obj_data[0x24];
        sound_y = obj_data[0x25];
        effect_id = 0x3000;
        if (*(u32 *)(obj_state + 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, effect_id);
        unlink_entity_node(obj_state);
        ((ObjectNodeHeader *)(obj_state - 0x20))->flags |= NODE_REMOVE;
        *active_slot = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
