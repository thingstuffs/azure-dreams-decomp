#include "town/person_callbacks_api.h"
#include "common.h"
#include "town/person.h"

/* Raise output as the timer counts down, then set it to the base value plus 0x800. */
void raise_reaction_output_until_expiry(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 timer;
    u16 output_value;

    timer = object->timer - 1;
    object->timer = timer;
    if ((timer << 16) <= 0) {
        initialize_actor_primary_handler(object, position, sprite);
        output_value = object->origin_heading + 0x800;
    } else {
        output_value = object->heading + 0x100;
    }
    object->heading = output_value;
}

/* MECHANISM: The seed's 24-byte frame and s0-held object base were already exact. The live output RMW
   uses +0x100. */
