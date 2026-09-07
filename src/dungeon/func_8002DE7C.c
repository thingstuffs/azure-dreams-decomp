#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(void *arg0, M2C_UNK arg1, M2C_UNK *arg2);
extern s8 D_80082660[];
extern M2C_UNK D_800CB570;
extern M2C_UNK D_800D694C;

typedef struct S_800CB5DC_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    M2C_UNK16 unk_6C;
} S_800CB5DC_0;   /* arg0 in func_800CB5DC */

void func_800CB5DC(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D694C);
    D_80082660[((S_800CB5DC_0 *)arg0)->unk_60 * 8] = 0;
    ((S_800CB5DC_0 *)arg0)->unk_54 = &D_800CB570;
    ((S_800CB5DC_0 *)arg0)->unk_6C = 0xA;
}
