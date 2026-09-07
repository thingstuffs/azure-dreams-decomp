#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800A0958;

typedef struct S_800A092C_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_800A092C_0;   /* arg0 in func_800A092C */

void func_800A092C(S_800A092C_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_50 = &D_800A0958;
    }
}
