#include "common.h"
#include "m2c_compat.h"

extern u32 *D_801131EC;

typedef struct S_8008AF2C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8008AF2C_0;   /* var_t0 in func_8008AF2C */

u32 func_8008AF2C(s32 arg0, s32 arg1, s32 arg2) {
    u32 *var_a3;
    u32 *var_t0;
    u32 temp_v1;
    u32 mask_3f;
    u32 mask_7f;

    var_t0 = D_801131EC;
    if (((S_8008AF2C_0 *)var_t0)->unk_04 != 0) {
        mask_3f = 0x3F000000;
        mask_7f = 0x007F0000;
        var_a3 = var_t0 + 1;
loop_2:
        temp_v1 = *var_t0;
        if ((arg0 == ((temp_v1 >> 0x17) & 1)) && (arg1 == ((temp_v1 & mask_3f) >> 0x18)) && (arg2 == ((temp_v1 & mask_7f) >> 0x10))) {
            return *var_a3;
        }
        var_a3 += 2;
        var_t0 += 2;
        if (*var_a3 != 0) {
            goto loop_2;
        }
    } else {
        return 0U;
    }
    return 0U;
}
