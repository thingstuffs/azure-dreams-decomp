#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
void func_800CDFF8(void *, s32, s32);    /* extern */

s32 select_object_setup_path(void *object, s32 request_data, s32 request_param, s32 check_param);
/* Decrement the object's countdown when its update returns zero and handle expiration. */
void tick_countdown_and_handle_expiration(Rec_func_80094268_arg0 *object, s32 context_a, s32 context_b, s32 update_arg) {
    u16 countdown;

    if (select_object_setup_path(object, context_a, context_b, update_arg) == 0) {
        countdown = object->unk_6C.as_u16 - 1;
        object->unk_6C.as_u16 = countdown;
        if ((countdown << 0x10) <= 0) {
            object->unk_90.as_s16 = 0;
            func_800CDFF8(object, context_a, context_b);
        }
    }
}
