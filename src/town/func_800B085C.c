#include "common.h"
#include "m2c_compat.h"

typedef struct S_800ADFBC_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800ADFBC_0;   /* var_a0 in func_800ADFBC */

s32 func_800ADFBC(void *arg0) {
    s32 var_v1;
    void *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    if (((S_800ADFBC_0 *)var_a0)->unk_01 != 0) {
        do {
            var_a0 += 4;
            var_v1 += 1;
        } while (((S_800ADFBC_0 *)var_a0)->unk_01 != 0);
    }
    return var_v1;
}
