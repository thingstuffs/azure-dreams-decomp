#include "common.h"
#include "m2c_compat.h"

typedef struct S_800DCA1C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800DCA1C_0;   /* ((*var_a1 * 0x10) + arg0) in func_800DCA1C */

extern u8 D_800E2954;
extern u8 D_800E2960[];

s32 func_800DCA1C(s32 arg0, s32 arg1) {
    s32 var_a2;
    u8 *var_a1;
    u8 *var_v1;
    u8 temp_v1;

    var_a2 = 0;
    if (arg1 != 0) {
        var_v1 = D_800E2960;
    } else {
        var_v1 = &D_800E2954;
    }
    if (*var_v1 < 9U) {
        var_a1 = var_v1;
        do {
            ((S_800DCA1C_0 *)(((*var_a1 * 0x10) + arg0)))->unk_0C = var_a2;
            temp_v1 = *var_a1;
            var_a1 += 1;
            var_a2 = arg0 + (temp_v1 * 0x10);
        } while ((u8) *var_a1 < 9U);
    }
    return var_a2;
}
