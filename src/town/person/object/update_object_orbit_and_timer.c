#include "common.h"
#include "shared/entity.h"
#include "town/scene/collision.h"

#include "town/person/object_setup.h"
#include "sdk/libgte.h"
#include "town/person/object.h"

extern ColliderView town_actor_control;


/* Update the object's orbit, apply a movement offset, and advance its timed state. */
void update_object_orbit_and_timer(TownObjectRecord *object, ObjectPosition *position, void *update_arg, s32 check_param) {
    CollisionOverlap *motion_entry;
    s32 axis;
    u16 angle;
    u16 timer;

    if (select_object_setup_path(object, position, update_arg) != 0) {
        return;
    }

    angle = (u16)object->unk_86;
    object->unk_86 = angle + 0x40;
    object->heading = angle + 0x440;

    position->x.unsigned_parts.integer = ((u16)object->unk_84) +
        rsin((object->unk_86)) / (0x1000 / object->unk_84);
    position->y.unsigned_parts.integer = (u16)object->unk_86 +
        rcos((object->unk_86)) / (0x1000 / object->unk_84) -
        ((u16)object->unk_84);

    motion_entry = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, &town_actor_control);
    if (motion_entry != 0 && (axis = motion_entry->axis) != 2) {
        if (axis == 0) {
            position->x.v -= motion_entry->amount;
        } else {
            position->y.v -= motion_entry->amount;
        }
    } else {
        timer = object->timer - 1;
        object->timer = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
    }
    initialize_object_from_context(object, position, update_arg);
}
