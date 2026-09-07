#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B0FD4();                      /* extern */
M2C_UNK func_800B173C();                      /* extern */

typedef struct S_800B1778_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B1778_0;   /* temp_s0 in func_800B1778 */

void func_800B1778(s32 arg0, s32 arg1, s32 arg2) {
    S_800B1778_0 *temp_s0;

    temp_s0 = arg0 + 0x20;
    temp_s0->unk_08 = arg2;
    func_800B173C(temp_s0);
    temp_s0->unk_10 = arg1;
    func_800B0FD4(temp_s0);
}
