#include "common.h"
#include "m2c_compat.h"

s32 func_800C30E0();                                /* extern */
M2C_UNK func_800C382C();    /* extern */

typedef struct S_800C34EC_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C34EC_0;   /* arg0 in func_800C34EC */

void func_800C34EC(S_800C34EC_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    if (func_800C30E0() == 0) {
        temp_v0 = arg0->unk_6C - 1;
        arg0->unk_6C = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            func_800C382C(arg0, arg1, arg2);
        }
    }
}
