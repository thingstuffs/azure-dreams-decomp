#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C8FF0;
extern M2C_UNK D_800D6268;

typedef struct S_800C8F80_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
    u8 pad_74[0x22];
    u8 unk_96;
} S_800C8F80_0;   /* arg0 in func_800C8F80 */

void func_800C8F80(S_800C8F80_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C2E84(arg0, arg2, &D_800D6268);
        arg0->unk_50 = &D_800C8FF0;
        arg0->unk_72 = 0xC00;
        arg0->unk_6C = (u16) (arg0->unk_96 * 3);
    }
}
