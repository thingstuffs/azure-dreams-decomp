#include "town/person.h"
#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Interpolate toward the saved coordinates, then snap and restore heading on expiry. */
void interpolate_person_to_saved_position(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output) {
    s16 steps_left;

    position->z.w.i = get_clamped_transform_coordinate(position);
    steps_left = --object->timer;
    if (steps_left <= 0) {
        position->x.w.i = object->origin_x;
        position->y.w.i = object->origin_y;
        object->heading = object->origin_heading;
        apply_object_setup_and_update(object, position, output);
        return;
    }

    position->x.w.i += (object->origin_x - position->x.w.i) / steps_left;
    /* BYTES: Sign-extend the timer for the second signed division. */
    position->y.w.i += (object->origin_y - position->y.w.i) / (s16)object->timer;
}
