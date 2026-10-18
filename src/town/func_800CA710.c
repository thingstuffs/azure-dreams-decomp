#include "common.h"

/* extern */

typedef struct S_800C7E70_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u16 unk_6E;
    u8 pad_70[0x2];
    u16 unk_72;
} S_800C7E70_0;   /* arg0 in decrement_mother_event_timer_and_restore */


void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the countdown, then restore unk_72 from unk_6E and call apply_object_setup_and_update when it expires. */
void decrement_mother_event_timer_and_restore(S_800C7E70_0 *object, s32 callback_arg_1, s32 callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        object->unk_72 = (u16) object->unk_6E;
        apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    }
}
