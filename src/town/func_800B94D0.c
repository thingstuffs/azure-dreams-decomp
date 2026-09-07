#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B6508();                      /* extern */
M2C_UNK func_800B6B10();                         /* extern */
M2C_UNK func_800B6E3C();                      /* extern */

typedef struct S_800B6C30_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0x8E];
    s32 unk_98;
} S_800B6C30_0;   /* temp_s0 in func_800B6C30 */

void func_800B6C30(s32 arg0, s32 arg1, s16 arg2) {
    S_800B6C30_0 *temp_s0;

    if (arg0 != 0) {
        temp_s0 = arg0 + 0x20;
        func_800B6B10(temp_s0->unk_98);
        temp_s0->unk_08 = arg2;
        temp_s0->unk_04 = arg1;
        func_800B6508(temp_s0);
        func_800B6E3C(temp_s0);
    }
}
