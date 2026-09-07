#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D60;

typedef struct S_8017178C_0 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
} S_8017178C_0;   /* temp_v0 in func_8017178C */

void func_8017178C(s16 arg0) {
    S_8017178C_0 *temp_v0;

    temp_v0 = D_80175D60 + 0x20;
    temp_v0->unk_12 = arg0;
    temp_v0->unk_18 = 0;
}
