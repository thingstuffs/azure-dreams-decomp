#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800A092C;

typedef struct S_800A08F0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A08F0_0;   /* arg0 in func_800A08F0 */

void func_800A08F0(S_800A08F0_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6E + 0x40;
    arg0->unk_6E = temp_v0;
    if ((s16) temp_v0 >= 0x400) {
        arg0->unk_6E = 0x400U;
        arg0->unk_50 = &D_800A092C;
    }
}
