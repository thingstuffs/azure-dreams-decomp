#include "town/person.h"

#include "town/person/object_setup.h"

/* Clamp height, advance the timer, and move two units along Y until expiry. */
void step_person_y_up(PersonObject *object, ObjectPosition *position, SpriteFrameState *output) {
    position->z.w.i = get_clamped_transform_coordinate(position);
    object->timer--;
    if (object->timer < 0) {
        apply_object_setup_and_update(object, position, output);
    } else {
        position->y.v += 0x20000;
    }
}
