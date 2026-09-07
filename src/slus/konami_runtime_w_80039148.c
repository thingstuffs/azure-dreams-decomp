#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039148_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0x6];
    s16 unk_20;
    s16 unk_22;
    u8 pad_24[0x1];
    u8 unk_25;
    u8 pad_26[0x8];
    u8 unk_2E;
} S_80039148_0;   /* arg0 in func_80039148 */


extern M2C_UNK func_800381A4;
extern M2C_UNK func_800387D0;

void func_80039148(S_80039148_0 *arg0) {
    M2C_UNK *var_v0;

    arg0->unk_20 = 0;
    if (arg0->unk_22 < (arg0->unk_25 - 1)) {
        arg0->unk_22 = (s16) ((u16) arg0->unk_22 + 1);
        if (arg0->unk_2E == 1) {
            var_v0 = &func_800381A4;
            arg0->unk_18 = 0;
            goto block_4;
        }
    } else {
        var_v0 = &func_800387D0;
block_4:
        arg0->unk_10 = var_v0;
    }
}
