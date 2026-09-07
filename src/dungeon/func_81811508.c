#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026370();                    /* extern */
s32 func_80026388();               /* extern */

typedef struct S_80026508_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0x5C];
    s32 unk_70;
} S_80026508_0;   /* temp_s0 in func_80026508 */

void func_80026508(s32 arg0) {
    s32 temp_v0;
    S_80026508_0 *temp_s0;

    temp_s0 = arg0 + 0x20;
    temp_v0 = func_80026388(-1, temp_s0->unk_08, temp_s0->unk_10);
    temp_s0->unk_08 = temp_v0;
    func_80026370(temp_s0->unk_70, temp_v0);
}
