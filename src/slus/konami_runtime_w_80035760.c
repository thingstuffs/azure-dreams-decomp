#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035760_0 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 unk_4D;
    u8 pad_4E[0x3];
    u8 unk_51;
    u8 pad_52[0x16];
    M2C_UNK * unk_68;
    u8 pad_6C[0x8];
    u8 * unk_74;
} S_80035760_0;   /* arg0 in func_80035760 */


extern M2C_UNK func_800357B0;

void func_80035760(S_80035760_0 *arg0) {
    u8 *temp_a1;

    temp_a1 = arg0->unk_74;
    if ((*temp_a1 == 1) || (arg0->unk_51 == 0xFF)) {
        *temp_a1 = 1;
        arg0->unk_4C = 0xFE;
        arg0->unk_4D = 0xFE;
        arg0->unk_51 = 0U;
        arg0->unk_68 = &func_800357B0;
    }
}
