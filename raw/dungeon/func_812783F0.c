#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8014FFBC;
extern s32 D_80150710;
extern s32 D_80150714;
extern s16 D_80150718;

void func_8014FBF0(s16 arg0) {
    void *temp_a1;

    D_80150718 = 0;
    temp_a1 = D_80150710 + 0x20;
    D_80150714 = *((arg0 * 4) + &D_8014FFBC);
    M2C_FIELD(temp_a1, s8 *, 0xBA) = 1;
    M2C_FIELD(temp_a1, s16 *, 0xB8) = arg0;
}
