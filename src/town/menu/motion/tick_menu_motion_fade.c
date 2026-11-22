#include "town/menu/motion.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "town/menu.h"

/* Advance the object's motion and timer-scaled value, or mark it expired. */
void tick_menu_motion_fade(MenuRingAnimationState *obj, struct ObjectPosition *center)
{
    obj->timer--;
    if (obj->timer < 0) {
        NODE_HEADER(obj)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    obj->radius_a += obj->delta_a;
    obj->radius_b += obj->delta_b;
    obj->delta_a -= 16;
    obj->shade = (obj->timer * 255) / 20;
    draw_segmented_menu_ring(center, obj->radius_a, obj->radius_b, obj->shade);
}
