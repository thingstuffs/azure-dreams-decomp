#include "common.h"
#include "m2c_compat.h"

s32 func_80049DE8();                        /* extern */
extern M2C_UNK D_800AE5B8;

typedef struct S_800AF1B4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
} S_800AF1B4_0;   /* temp_s0 in func_800AF1B4 */

typedef struct S_800AF1B4_1 {
    u8 pad_00[0x20];
    M2C_UNK * unk_20;
} S_800AF1B4_1;   /* arg0 in func_800AF1B4 */

void func_800AF1B4(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_v0;
    S_800AF1B4_0 *temp_s0;

    temp_s0 = arg0 + 0x20;
    temp_v0 = func_80049DE8(temp_s0->unk_1C, arg1, temp_s0->unk_28);
    if (temp_v0 != temp_s0->unk_1C) {
        temp_s0->unk_1C = temp_v0;
        temp_s0->unk_04 = arg2;
        temp_s0->unk_08 = 0;
        ((S_800AF1B4_1 *)arg0)->unk_20 = &D_800AE5B8;
        temp_s0->unk_20 = (s32) temp_s0->unk_1C;
    }
}
