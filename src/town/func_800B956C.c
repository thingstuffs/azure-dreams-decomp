#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6CCC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B6CCC_0;   /* arg2 in func_800B6CCC */

void func_800B6CCC(s32 arg0, s32 arg1, S_800B6CCC_0 *arg2, s32 arg3) {
    s32 var_v0;

    var_v0 = arg1 + 0x42E6;
    if (arg0 == 0) {
        var_v0 = arg1 + 0x42DB;
    }
    arg2->unk_04 = var_v0;
    arg2->unk_00 = (s32) (arg3 + 0x80800000);
}
