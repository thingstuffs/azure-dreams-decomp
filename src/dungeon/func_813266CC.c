#include "common.h"
#include "m2c_compat.h"

extern s32 D_80174704;

typedef struct S_8016DECC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    s8 unk_9B;
} S_8016DECC_0;   /* temp_v0 in func_8016DECC */

void func_8016DECC(void) {
    S_8016DECC_0 *temp_v0;

    temp_v0 = D_80174704 + 0x20;
    temp_v0->unk_9B = 0;
    temp_v0->unk_96 = 0;
}
