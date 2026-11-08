#include "town/map/state_callbacks_api.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"

struct town_inactive_object {
    s8 pad00[0x98];
    u8 *field_98;
    u8 *field_9C;
};

/* Mark inactive objects or advance their wrapped 12-bit state value. */
void update_inactive_object_state(struct town_inactive_object *obj, void *unused, SpriteFrameState *sprite)
{
    s32 t;
    if (*obj->field_98 == 0) {
        unlink_node_if_registered(obj);
        *(u16 *)((u8 *)obj - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    sprite->angle_z += *(s8 *)(obj->field_9C + 0x97);
    t = sprite->angle_z;
    sprite->angle_z = t & 0xFFF;
}
