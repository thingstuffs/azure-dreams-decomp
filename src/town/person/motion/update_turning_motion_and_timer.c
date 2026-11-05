#include "common.h"
#include "shared/entity.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/motion.h"
#include "town/person/object.h"

extern ColliderView town_actor_control;


/* Updates turning motion, applies a position adjustment, and checks the timer. */
void update_turning_motion_and_timer(TownObjectRecord *actor, void *position, void *update_param, s32 check_param) {
    ObjectPosition *coordinates = position;
    CollisionOverlap *adjustment;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(actor, position, update_param) != 0) {
        return;
    }

    angle = actor->unk_86.as_u16;
    actor->unk_86.as_u16 = angle - 0x40;
    actor->heading.as_s16 = angle - 0x440;

    coordinates->x.unsigned_parts.integer = actor->unk_84.as_u16 +
        rsin(actor->unk_86.as_s16) / (0x1000 / actor->unk_84.as_s16);
    coordinates->y.unsigned_parts.integer = actor->unk_86.as_u16 +
        rcos(actor->unk_86.as_s16) / (0x1000 / actor->unk_84.as_s16) -
        actor->unk_84.as_u16;

    adjustment = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(actor, &town_actor_control);
    if (adjustment != 0) {
        axis = adjustment->axis;
        if (axis != 2) {
            if (axis == 0) {
                coordinates->x.v -= adjustment->amount;
            } else if (axis == 1) {
                coordinates->y.v -= adjustment->amount;
            }
            initialize_object_from_context(actor, position, update_param);
            return;
        }
    }

    timer = actor->timer.as_u16 - 1;
    actor->timer.as_u16 = timer;
    if ((s32)(timer << 16) <= 0) {
        initialize_object_from_context(actor, position, update_param);
    }
}
