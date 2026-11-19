#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "town/map/state.h"
#include "town/map/effect.h"
#include "town/menu.h"

/* Clear the object's linked flag and mark completion, or advance its wrapped angle. */
void spin_object_until_outside_bounds(void *object, ObjectPosition *position)
{
    MapParticleEffect *effect = object;
    u8 *linked_flag;

    if (classify_object_against_bounds(object, position) != 0) {
        linked_flag = effect->active_flag;
        if (linked_flag != 0) {
            *linked_flag = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    effect->angle = (u16)effect->angle + effect->index;
    effect->angle %= 0x1000;
}
