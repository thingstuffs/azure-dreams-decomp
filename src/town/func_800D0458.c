#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_800CDFF8();    /* extern */

typedef struct S_800CDBB8_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800CDBB8_0;   /* arg0 in func_800CDBB8 */


s32 func_800C30E0(S_800CDBB8_0 *, M2C_UNK, M2C_UNK, s32);
/* Decrement the object's countdown when its update returns zero and handle expiration. */
void func_800CDBB8(S_800CDBB8_0 *object, M2C_UNK context_a, M2C_UNK context_b, s32 update_arg) {
    u16 countdown;

    if (func_800C30E0(object, context_a, context_b, update_arg) == 0) {
        countdown = object->unk_6C - 1;
        object->unk_6C = countdown;
        if ((countdown << 0x10) <= 0) {
            object->unk_90 = 0;
            func_800CDFF8(object, context_a, context_b);
        }
    }
}
