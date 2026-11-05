#include "common.h"
#include "shared/entity.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/object.h"

extern ColliderView town_actor_control;


/* Update the object's orbit, apply a movement offset, and advance its timed state. */
void update_object_orbit_and_timer(TownObjectRecord *object, void *position, void *update_arg, s32 check_param) {
    ObjectPosition *coordinates = position;
    CollisionOverlap *motion_entry;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(object, position, update_arg) != 0) {
        return;
    }

    angle = object->unk_86.as_u16;
    object->unk_86.as_u16 = angle + 0x40;
    object->heading.as_s16 = angle + 0x440;

    coordinates->x.unsigned_parts.integer = object->unk_84.as_u16 +
        rsin(object->unk_86.as_s16) / (0x1000 / object->unk_84.as_s16);
    coordinates->y.unsigned_parts.integer = object->unk_86.as_u16 +
        rcos(object->unk_86.as_s16) / (0x1000 / object->unk_84.as_s16) -
        object->unk_84.as_u16;

    motion_entry = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, &town_actor_control);
    if (motion_entry != 0 && (axis = motion_entry->axis) != 2) {
        if (axis == 0) {
            coordinates->x.v -= motion_entry->amount;
        } else {
            coordinates->y.v -= motion_entry->amount;
        }
    } else {
        timer = object->timer.as_u16 - 1;
        object->timer.as_u16 = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
    }
    initialize_object_from_context(object, position, update_arg);
}
