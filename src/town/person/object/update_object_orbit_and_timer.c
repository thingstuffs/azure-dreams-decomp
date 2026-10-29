#include "common.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/object.h"

extern ColliderView town_actor_control;

#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Update the object's orbit, apply a movement offset, and advance its timed state. */
void update_object_orbit_and_timer(void *object, void *position, void *update_arg, s32 check_param) {
    CollisionOverlap *motion_entry;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(object, position, update_arg) != 0) {
        return;
    }

    angle = U16_AT(object, 0x86);
    U16_AT(object, 0x86) = angle + 0x40;
    S16_AT(object, 0x72) = angle + 0x440;

    U16_AT(position, 2) = U16_AT(object, 0x84) +
        rsin(S16_AT(object, 0x86)) / (0x1000 / S16_AT(object, 0x84));
    U16_AT(position, 6) = U16_AT(object, 0x86) +
        rcos(S16_AT(object, 0x86)) / (0x1000 / S16_AT(object, 0x84)) -
        U16_AT(object, 0x84);

    motion_entry = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, &town_actor_control);
    if (motion_entry != 0 && (axis = motion_entry->axis) != 2) {
        if (axis == 0) {
            S32_AT(position, 0) -= motion_entry->amount;
        } else {
            S32_AT(position, 4) -= motion_entry->amount;
        }
    } else {
        timer = U16_AT(object, 0x6C) - 1;
        U16_AT(object, 0x6C) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
    }
    initialize_object_from_context(object, position, update_arg);
}
