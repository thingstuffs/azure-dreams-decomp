#include "common.h"
#include "m2c_compat.h"

s32 func_800C30E0();                                /* extern */
M2C_UNK func_800CDF00();    /* extern */

typedef struct S_800CD9F4_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800CD9F4_0;   /* arg0 in func_800CD9F4 */

void func_800CD9F4(S_800CD9F4_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    if (func_800C30E0() == 0) {
        temp_v0 = arg0->unk_6C - 1;
        arg0->unk_6C = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            arg0->unk_90 = 3;
            func_800CDF00(arg0, arg1, arg2);
        }
    }
}
