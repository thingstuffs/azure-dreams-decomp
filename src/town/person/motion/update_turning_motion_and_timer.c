#include "common.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/motion.h"
#include "town/person/object.h"

extern ColliderView town_actor_control;

#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Updates turning motion, applies a position adjustment, and checks the timer. */
void update_turning_motion_and_timer(TownObjectRecord *actor, void *position, void *update_param, s32 check_param) {
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

    U16_AT(position, 2) = actor->unk_84.as_u16 +
        rsin(actor->unk_86.as_s16) / (0x1000 / actor->unk_84.as_s16);
    U16_AT(position, 6) = actor->unk_86.as_u16 +
        rcos(actor->unk_86.as_s16) / (0x1000 / actor->unk_84.as_s16) -
        actor->unk_84.as_u16;

    adjustment = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(actor, &town_actor_control);
    if (adjustment != 0) {
        axis = adjustment->axis;
        if (axis != 2) {
            if (axis == 0) {
                S32_AT(position, 0) -= adjustment->amount;
            } else if (axis == 1) {
                S32_AT(position, 4) -= adjustment->amount;
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
