#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D64;

typedef struct S_80170510_0 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
} S_80170510_0;   /* temp_v1 in func_80170510 */

void func_80170510(void) {
    S_80170510_0 *temp_v1;

    temp_v1 = D_80175D64 + 0x20;
    temp_v1->unk_18 = 0;
    temp_v1->unk_12 = (u16) (temp_v1->unk_12 + 1);
}
