/* Advance town actor countdowns and invoke their completion handlers. */

#include "common.h"
#include "town/person/state.h"
#include "town/system/object_hooks.h"
#include "shared/town_object.h"

/* extern */


#include "town/person/object_setup.h"
#include "town/person/object.h"
#include "town/system.h"
/* Decrement the countdown and call apply_object_setup_and_update when it reaches zero or becomes negative. */
void decrement_object_timer_and_update(TownObjectRecord *object, void *callback_arg_1, void *callback_arg_2) {
    u16 countdown;

    countdown = object->timer - 1;
    object->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}
#include "m2c_compat.h"

/* extern */


/* Decrements the timer and calls the handler when its signed value is nonpositive. */
void decrement_object_timer_and_call_handler(TownObjectRecord *object) {
    u16 remaining_ticks;

    remaining_ticks = object->timer - 1;
    object->timer = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        install_object_handler_and_clear_slot_flag(object);
    }
}
