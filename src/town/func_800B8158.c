#include "common.h"
#include "m2c_compat.h"

extern s32 D_800814A8;

typedef struct S_800B58B8_0 {
    u8 pad_00[0x4C];
    s32 unk_4C;
    s32 unk_50;
    u8 pad_54[0x84];
    s32 unk_D8;
} S_800B58B8_0;   /* arg1 in func_800B58B8 */

void func_800B58B8(s32 *arg0, S_800B58B8_0 *arg1) {
    s32 *var_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    var_a0 = arg0;
    temp_v0 = arg1->unk_4C;
    if (temp_v0 != 0) {
        *var_a0 = temp_v0;
        var_a0 += 1;
    }
    temp_v0_2 = arg1->unk_50;
    if (temp_v0_2 != 0) {
        *var_a0 = temp_v0_2;
        var_a0 += 1;
    }
    if (arg1 == D_800814A8) {
        temp_a1 = arg1->unk_D8;
        if (temp_a1 != 0) {
            *var_a0 = temp_a1;
        }
    }
}
