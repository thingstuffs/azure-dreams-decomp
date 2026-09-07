#include "common.h"
#include "m2c_compat.h"

extern u8 D_80011F80[];
asm(".globl D_80011F80\nD_80011F80 = 0x80011F80");

typedef struct S_800B2964_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2964_0;   /* var_v1 in func_800B2964 */

void func_800B2964(M2C_UNK *arg0, s32 arg1) {
    M2C_UNK *var_a0;
    s8 *var_v1;
    s32 var_a2;

    var_a0 = arg0;
    var_a2 = 0;
    if (arg1 > 0) {
        var_v1 = D_80011F80;
        do {
            if (((S_800B2964_0 *)var_v1)->unk_01 != 0) {
                *var_a0 = (M2C_UNK) var_v1;
                var_a0 += 1;
            }
            var_a2 += 1;
            var_v1 += 4;
        } while (var_a2 < arg1);
    }
    *var_a0 = NULL;
}
