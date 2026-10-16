/* Relink of matched town/func_800C7EFC; every changed retail word is a paired relocation. */
#define func_800C5864 func_800CA88C
#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C565C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
} S_800C565C_0;   /* arg0 in func_800CA40C */


extern void func_800CA88C(void *, s32, s32);
/* Decrement the countdown, then call func_800CA88C and clear unk_72 when it expires. */
void func_800CA40C(S_800C565C_0 *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CA88C(object, callback_arg_1, callback_arg_2);
        object->unk_72 = 0;
    }
}
