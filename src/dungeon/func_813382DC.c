#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D50;

typedef struct S_8016F2DC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    s8 unk_9B;
} S_8016F2DC_0;   /* temp_v0 in func_8016F2DC */

void func_8016F2DC(void) {
    S_8016F2DC_0 *temp_v0;

    temp_v0 = D_80175D50 + 0x20;
    temp_v0->unk_9B = 0;
    temp_v0->unk_96 = 0;
    temp_v0->unk_9A = (u8) (temp_v0->unk_9A + 1);
}
