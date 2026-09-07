#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008CAA0(); /* extern */
M2C_UNK func_8008CBA0(); /* extern */
M2C_UNK func_80090200(); /* extern */
M2C_UNK func_800B6AA4();                            /* extern */

typedef struct S_800B69DC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x44];
    s16 unk_64;
} S_800B69DC_0;   /* arg3 in func_800B69DC */

typedef struct S_800B69DC_1 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x71];
    u16 unk_10C;
} S_800B69DC_1;   /* arg0 in func_800B69DC */

typedef struct S_800B69DC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800B69DC_2;   /* arg2 in func_800B69DC */

void func_800B69DC(S_800B69DC_1 *arg0, M2C_UNK arg1, S_800B69DC_2 *arg2, S_800B69DC_0 *arg3) {
    s16 temp_v1;

    temp_v1 = arg3->unk_64;
    if ((temp_v1 < 0) || (arg0->unk_10C & 1)) {
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        func_8008CAA0(arg0, arg1, arg2, arg3);
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if ((arg0->unk_9A != 0xD) && (arg3->unk_1C & 0x200)) {
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        func_80090200(arg0, arg1, arg2, arg3);
    }
}
