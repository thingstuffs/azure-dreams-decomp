#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E5910;

typedef struct S_800DBF5C_0 {
    u8 pad_00[0x54];
    s32 unk_54;
    u8 pad_58[0x4];
    s32 unk_5C;
} S_800DBF5C_0;   /* temp_v1 in func_800DBF5C */

void func_800DBF5C(void) {
    S_800DBF5C_0 *temp_v1;

    temp_v1 = D_800E5910 + 0x20;
    if (temp_v1->unk_5C == 0) {
        temp_v1->unk_54 = (s32) (temp_v1->unk_54 | 1);
    }
}
