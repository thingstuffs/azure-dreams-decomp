#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* extern */

#include "town/person/object_setup.h"
/* Decrement the countdown, then call func_800C5864 and clear unk_72 when it expires. */
void decrement_countdown_call(Rec_func_80094268_arg0 *object, s32 callback_arg_1, void *callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_two_value_adjustment_action(object, callback_arg_1, callback_arg_2);
        object->unk_72.as_s16 = 0;
    }
}
