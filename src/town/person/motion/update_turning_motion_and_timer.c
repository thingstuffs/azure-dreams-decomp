#include "common.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/motion.h"
#include "town/person/object.h"

extern ColliderView town_actor_control;

#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Updates turning motion, applies a position adjustment, and checks the timer. */
void update_turning_motion_and_timer(void *actor, void *position, void *update_param, s32 check_param) {
    CollisionOverlap *adjustment;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(actor, position, update_param) != 0) {
        return;
    }

    angle = U16_AT(actor, 0x86);
    U16_AT(actor, 0x86) = angle - 0x40;
    S16_AT(actor, 0x72) = angle - 0x440;

    U16_AT(position, 2) = U16_AT(actor, 0x84) +
        rsin(S16_AT(actor, 0x86)) / (0x1000 / S16_AT(actor, 0x84));
    U16_AT(position, 6) = U16_AT(actor, 0x86) +
        rcos(S16_AT(actor, 0x86)) / (0x1000 / S16_AT(actor, 0x84)) -
        U16_AT(actor, 0x84);

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

    timer = U16_AT(actor, 0x6C) - 1;
    U16_AT(actor, 0x6C) = timer;
    if ((s32)(timer << 16) <= 0) {
        initialize_object_from_context(actor, position, update_param);
    }
}
