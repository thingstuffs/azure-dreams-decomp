#include "common.h"
void func_800CDFF8(void *, s32, s32);    /* extern */

typedef struct S_800CDBB8_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800CDBB8_0;   /* arg0 in tick_countdown_and_handle_expiration */
s32 select_object_setup_path(void *object, s32 request_data, s32 request_param, s32 check_param);
/* Decrement the object's countdown when its update returns zero and handle expiration. */
void tick_countdown_and_handle_expiration(S_800CDBB8_0 *object, s32 context_a, s32 context_b, s32 update_arg) {
    u16 countdown;

    if (select_object_setup_path(object, context_a, context_b, update_arg) == 0) {
        countdown = object->unk_6C - 1;
        object->unk_6C = countdown;
        if ((countdown << 0x10) <= 0) {
            object->unk_90 = 0;
            func_800CDFF8(object, context_a, context_b);
        }
    }
}
