#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK func_800C2E84();
extern M2C_UNK D_800CB474;
extern M2C_UNK D_800D6938;

typedef struct S_800CB4B0_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800CB4B0_0;   /* arg0 in func_800CB4B0 */

void func_800CB4B0(S_800CB4B0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C2E84(arg0, arg2, &D_800D6938);
        arg0->unk_54 = &D_800CB474;
        arg0->unk_6C = 0xAU;
    }
}
