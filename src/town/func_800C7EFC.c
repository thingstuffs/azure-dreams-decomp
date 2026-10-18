#include "common.h"

/* extern */

typedef struct S_800C565C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
} S_800C565C_0;   /* arg0 in decrement_countdown_call */
#include "records/Rec_func_80094268_arg0.h"
void func_800C5864(Rec_func_80094268_arg0 *actor, s32 unused, s32 init_param);
/* Decrement the countdown, then call func_800C5864 and clear unk_72 when it expires. */
void decrement_countdown_call(S_800C565C_0 *object, s32 callback_arg_1, s32 callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800C5864(object, callback_arg_1, callback_arg_2);
        object->unk_72 = 0;
    }
}
