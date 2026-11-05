#include "common.h"
#include "shared/town_object.h"

/* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
/* Decrement the countdown, then call func_800C5864 and clear unk_72 when it expires. */
void decrement_countdown_call(TownObjectRecord *object, s32 callback_arg_1, void *callback_arg_2) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_two_value_adjustment_action(object, callback_arg_1, callback_arg_2);
        object->heading = 0;
    }
}
