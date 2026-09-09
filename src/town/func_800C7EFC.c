#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C565C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
} S_800C565C_0;   /* arg0 in func_800C565C */


M2C_UNK func_800C5864(S_800C565C_0 *, M2C_UNK, M2C_UNK);
/* Decrement the countdown, then call func_800C5864 and clear unk_72 when it expires. */
void func_800C565C(S_800C565C_0 *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800C5864(object, callback_arg_1, callback_arg_2);
        object->unk_72 = 0;
    }
}
