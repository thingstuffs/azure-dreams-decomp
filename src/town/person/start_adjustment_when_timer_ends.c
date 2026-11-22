#include "common.h"
#include "shared/town_object.h"

/* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
/* Decrement the countdown, then call func_800C5864 and clear unk_72 when it expires. */
void start_adjustment_when_timer_ends(TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_two_value_adjustment_action(object, position, sprite);
        object->heading = 0;
    }
}
