#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_800CDF00();    /* extern */

typedef struct S_800CD9F4_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800CD9F4_0;   /* arg0 in func_800CD9F4 */


s32 func_800C30E0(S_800CD9F4_0 *, M2C_UNK, M2C_UNK, s32);
/* Decrement the counter when the check returns zero and enter state 3 when it expires. */
void func_800CD9F4(S_800CD9F4_0 *object, M2C_UNK context_a, M2C_UNK context_b, s32 check_arg) {
    u16 remaining_count;

    if (func_800C30E0(object, context_a, context_b, check_arg) == 0) {
        remaining_count = object->unk_6C - 1;
        object->unk_6C = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            object->unk_90 = 3;
            func_800CDF00(object, context_a, context_b);
        }
    }
}
