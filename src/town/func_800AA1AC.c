#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
extern M2C_UNK D_800A7950;

typedef struct S_800A790C_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800A790C_0;   /* arg0 in func_800A790C */

void func_800A790C(S_800A790C_0 *arg0) {
    s16 temp_v0;

    arg0->unk_50 = &D_800A7950;
    temp_v0 = func_800374F4(0x60) + 0xC0;
    arg0->unk_90 = temp_v0;
    arg0->unk_6C = temp_v0;
}
