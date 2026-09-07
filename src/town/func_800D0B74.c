#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */

typedef struct S_800CE2D4_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x16];
    s16 unk_84;
    s16 unk_86;
} S_800CE2D4_0;   /* arg0 in func_800CE2D4 */

typedef struct S_800CE2D4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CE2D4_1;   /* arg1 in func_800CE2D4 */

void func_800CE2D4(S_800CE2D4_0 *arg0, S_800CE2D4_1 *arg1) {
    u16 temp_v0;
    u32 temp_v1;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C4174();
    }
    arg1->unk_02 = (s16) ((u16) arg1->unk_02 + ((s32) (arg0->unk_84 - arg1->unk_02) / 2));
    temp_v1 = arg0->unk_86 - arg1->unk_06;
    arg1->unk_0A = (s16) ((u16) arg1->unk_0A + ((s32) (0 - arg1->unk_0A) / 2));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) (temp_v1 + (temp_v1 >> 0x1F)) >> 1));
}
