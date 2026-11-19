#include "common.h"

#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Decrement the timer and lower output until expiry restores the base value. */
void lower_reaction_output_until_expiry(TownObjectRecord *obj, ObjectPosition *update_input_1, SpriteFrameState *update_input_2) {
    u16 timer;

    timer = obj->timer - 1;
    obj->timer = timer;
    if ((timer << 16) <= 0) {
        apply_object_setup_and_update(obj, update_input_1, update_input_2);
        obj->heading = obj->unk_6E;
        return;
    }
    obj->heading -= 0x400;
}
