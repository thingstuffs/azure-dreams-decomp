#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "town/shop/monster_status_initialization_g00634.h"
#include "engine/node.h"
#include "engine/graphics.h"
#include "engine/item.h"
#include "town/shop.h"
#include "town/shop/object.h"
#include "town/shop/state.h"

/* Allocate and initialize an object, marking it for cleanup if setup fails. */
void *create_monster_status_object(struct ActorRecord *actor, s32 slot_index, s32 x, s32 y, s32 z) {
    ShopFirstCallbackObject *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    state = NODE_BODY(object);
    if (object != 0) {
        if (load_storage_display_resource(state, 0x18) != 0) {
            object->sprite = (struct SpriteFrameState *)&state->display;
            state->display.next = link_monster_status_display_entries(state->parts);
            initialize_monster_status_object(state, actor, slot_index, x, y, z);
            object->update_callback = &invoke_object_first_callback;
            register_node(object, &draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries(state->allocations);
        object->flags = (u16) (object->flags | 0x8000);
        object = 0;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
    return object;
}
