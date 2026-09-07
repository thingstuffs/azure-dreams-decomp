#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036484_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x3];
    s8 unk_51;
    u8 pad_52[0x12];
    u16 unk_64;
    u8 pad_66[0x2];
    M2C_UNK * unk_68;
} S_80036484_0;   /* arg0 in func_80036484 */


extern M2C_UNK func_800364BC;

void func_80036484(S_80036484_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_64 - 1;
    arg0->unk_64 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_4D = 0xFF;
        arg0->unk_51 = 0;
        arg0->unk_68 = &func_800364BC;
    }
}
