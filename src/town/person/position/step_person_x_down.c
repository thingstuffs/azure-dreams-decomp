#include "town/person.h"
#include "town/person/object.h"

void step_person_x_down(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output)
{
    position->z.w.i = get_clamped_transform_coordinate(position);
    object->timer--;
    if ((s16)object->timer < 0) {
        apply_object_setup_and_update(object, position, output);
    } else {
        position->x.v -= 0x20000;
    }
}
