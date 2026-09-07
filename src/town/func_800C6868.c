#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800C3F44;

typedef struct S_800C3FC8_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800C3FC8_0;   /* arg0 in func_800C3FC8 */

typedef struct S_800C3FC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C3FC8_1;   /* arg1 in func_800C3FC8 */

void func_800C3FC8(S_800C3FC8_0 *arg0, S_800C3FC8_1 *arg1) {
    s16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if (temp_v0 < 0) {
        arg0->unk_54 = &D_800C3F44;
        arg1->unk_14 = 0xFFF60000;
    }
}
