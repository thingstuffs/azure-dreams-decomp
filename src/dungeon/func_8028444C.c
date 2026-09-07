#include "common.h"
#include "m2c_compat.h"

extern u8 D_800EA000[];

typedef struct S_8001744C_0 {
    s16 unk_00;
} S_8001744C_0;   /* var_v0 in func_8001744C */

typedef struct S_8001744C_1 {
    s16 unk_00;
    s16 unk_02;
} S_8001744C_1;   /* var_v1 in func_8001744C */

void func_8001744C(void) {
    s8 *var_v0;
    s8 *var_v1;
    s32 var_a0;

    var_v0 = D_800EA000;
    var_a0 = 0x1000;
    var_v1 = var_v0 + 2;
    do {
        var_a0 -= 1;
        ((S_8001744C_0 *)var_v0)->unk_00 = 0;
        ((S_8001744C_1 *)var_v1)->unk_02 = 0;
        ((S_8001744C_1 *)var_v1)->unk_00 = 0;
        var_v1 += 6;
        var_v0 += 6;
    } while (var_a0 > 0);
}
