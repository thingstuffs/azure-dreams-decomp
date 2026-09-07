#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025888();                /* extern */

typedef struct S_80026340_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x48];
    s32 unk_54;
} S_80026340_0;   /* temp_a0 in func_80026340 */

void func_80026340(s32 arg0) {
    S_80026340_0 *temp_a0;

    temp_a0 = arg0 + 0x20;
    temp_a0->unk_08 = 4;
    func_80025888(temp_a0->unk_54, 4);
}
