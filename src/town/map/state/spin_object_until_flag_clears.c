#include "town/map/state_callbacks_api.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"
#include "town/map/state.h"
#include "town/map/effect.h"

/* Mark inactive objects or advance their wrapped 12-bit state value. */
void spin_object_until_flag_clears(MapParticleEffect *effect, ObjectPosition *unused_position, SpriteFrameState *sprite)
{
    s32 t;
    if (*effect->active_flag == 0) {
        unlink_node_if_registered(effect);
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    sprite->angle_z += effect->parent->index;
    t = sprite->angle_z;
    sprite->angle_z = t & 0xFFF;
}
