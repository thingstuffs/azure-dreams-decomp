#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C7E70_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u16 unk_6E;
    u8 pad_70[0x2];
    u16 unk_72;
} S_800C7E70_0;   /* arg0 in func_800C7E70 */


M2C_UNK func_800C4174(S_800C7E70_0 *, M2C_UNK, M2C_UNK);
/* Decrement the countdown, then restore unk_72 from unk_6E and call func_800C4174 when it expires. */
void func_800C7E70(S_800C7E70_0 *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        object->unk_72 = (u16) object->unk_6E;
        func_800C4174(object, callback_arg_1, callback_arg_2);
    }
}
