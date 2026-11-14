#include "common.h"
#include "shared/entity.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/motion.h"
#include "town/person/object.h"
#include "town/person/mother_event_motion_g00670.h"


/* Updates turning motion, applies a position adjustment, and checks the timer. */
void update_turning_motion_and_timer(TownObjectRecord *actor, ObjectPosition *position, void *update_param, s32 check_param) {
    CollisionOverlap *adjustment;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(actor, position, update_param) != 0) {
        return;
    }

    angle = (u16)actor->unk_86;
    actor->unk_86 = angle - 0x40;
    actor->heading = angle - 0x440;

    position->x.unsigned_parts.integer = ((u16)actor->unk_84) +
        rsin((actor->unk_86)) / (0x1000 / actor->unk_84);
    position->y.unsigned_parts.integer = (u16)actor->unk_86 +
        rcos((actor->unk_86)) / (0x1000 / actor->unk_84) -
        ((u16)actor->unk_84);

    adjustment = get_box_overlap_axis(actor, &town_actor_control);
    if (adjustment != 0) {
        axis = adjustment->axis;
        if (axis != 2) {
            if (axis == 0) {
                position->x.v -= adjustment->amount;
            } else if (axis == 1) {
                position->y.v -= adjustment->amount;
            }
            start_random_wait_select_setup(actor, position, update_param);
            return;
        }
    }

    timer = actor->timer - 1;
    actor->timer = timer;
    if ((s32)(timer << 16) <= 0) {
        start_random_wait_select_setup(actor, position, update_param);
    }
}
