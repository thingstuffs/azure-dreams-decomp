#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"

/* extern */


#include "town/person/object_setup.h"
#include "town/person.h"
/* Decrement the object countdown and call initialize_reaction_movement when it expires. */
void restart_reaction_when_timer_ends(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_reaction_movement(object, position, sprite);
    }
}
