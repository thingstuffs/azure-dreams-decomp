#include "common.h"
#include "m2c_compat.h"

extern u8 D_80082660;
extern M2C_UNK D_800C3C28;

typedef struct S_800C591C_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_800C591C_0;   /* arg0 in func_800C591C */

void func_800C591C(S_800C591C_0 *arg0) {
    *((arg0->unk_60 * 8) + &D_80082660) = 0;
    arg0->unk_54 = &D_800C3C28;
}
