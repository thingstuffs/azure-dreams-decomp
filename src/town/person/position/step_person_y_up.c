#include "town/person.h"

extern s32 get_clamped_transform_coordinate(ObjectPosition *);
extern void apply_object_setup_and_update(PersonObject *, ObjectPosition *, s8 *);

/* Clamp height, advance the timer, and move two units along Y until expiry. */
void step_person_y_up(PersonObject *object, ObjectPosition *position, s8 *output) {
    position->z.w.i = get_clamped_transform_coordinate(position);
    object->timer--;
    if (object->timer < 0) {
        apply_object_setup_and_update(object, position, output);
    } else {
        position->y.v += 0x20000;
    }
}
