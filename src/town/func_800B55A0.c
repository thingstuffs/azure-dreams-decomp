#include "common.h"
#include "m2c_compat.h"

s32 func_80049790();                             /* extern */

typedef struct S_800B2D00_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800B2D00_0;   /* arg1 in func_800B2D00 */

void func_800B2D00(s32 **arg0, S_800B2D00_0 *arg1, s32 arg2) {
    s32 **var_s2;
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_s1;
    s32 var_s3;

    var_s3 = 0;
    temp_v1 = arg1->unk_00;
    var_s2 = arg0;
    var_s1 = temp_v1 * 0xA;
    var_s0 = (temp_v1 * 0x28) + arg2;
loop_1:
    var_s3 += 1;
    if (var_s1 < arg1->unk_0C) {
        temp_a0 = *var_s0;
        var_s0 += 1;
        var_s1 += 1;
        **var_s2 = func_80049790(temp_a0);
        var_s2 += 1;
        if (var_s3 < 0xA) {
            goto loop_1;
        }
    }
}
