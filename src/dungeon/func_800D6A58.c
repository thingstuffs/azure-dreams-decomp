#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E5910;

typedef struct S_800DC1B8_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x10];
    s32 unk_2C;
} S_800DC1B8_0;   /* temp_a1 in func_800DC1B8 */

void func_800DC1B8(s32 arg0) {
    s32 temp_v1;
    s32 var_v0;
    S_800DC1B8_0 *temp_a1;

    temp_a1 = D_800E5910 + 0x20;
    temp_v1 = temp_a1->unk_18;
    var_v0 = temp_v1;
    if (temp_v1 < 0) {
        var_v0 = temp_v1 + 0x1F;
    }
    temp_a1->unk_18 = (s32) ((temp_v1 - ((var_v0 >> 5) << 5)) + 0x20);
    temp_a1->unk_2C = arg0;
}
