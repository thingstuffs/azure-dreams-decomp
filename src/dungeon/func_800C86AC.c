#include "common.h"
#include "m2c_compat.h"

extern void *D_800E3D7C;

typedef struct S_800CDE0C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    s32 unk_5C;
} S_800CDE0C_0;   /* var_a0 in func_800CDE0C */

void func_800CDE0C(void) {
    void *temp_a1;
    S_800CDE0C_0 *var_a0;

    var_a0 = D_800E3D7C;
    temp_a1 = var_a0;
    do {
        var_a0->unk_1C = (s32) (var_a0->unk_1C | 0x40000000);
        var_a0 = var_a0->unk_5C + 0x20;
    } while (var_a0 != temp_a1);
}
