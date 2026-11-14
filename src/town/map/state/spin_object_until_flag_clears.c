#include "town/map/state_callbacks_api.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"
#include "town/map/state.h"

struct town_inactive_object {
    s8 pad00[0x98];
    u8 *field_98;
    u8 *field_9C;
};

/* Mark inactive objects or advance their wrapped 12-bit state value. */
void spin_object_until_flag_clears(struct town_inactive_object *obj, void *unused, SpriteFrameState *sprite)
{
    s32 t;
    if (*obj->field_98 == 0) {
        unlink_node_if_registered(obj);
        NODE_HEADER(obj)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    sprite->angle_z += *(s8 *)(obj->field_9C + 0x97);
    t = sprite->angle_z;
    sprite->angle_z = t & 0xFFF;
}
