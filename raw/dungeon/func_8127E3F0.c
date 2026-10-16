#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80172FBC;
extern s32 D_80173710;
extern s32 D_80173714;
extern s16 D_80173718;

void func_80172BF0(s16 arg0) {
    void *temp_a1;

    D_80173718 = 0;
    temp_a1 = D_80173710 + 0x20;
    D_80173714 = *((arg0 * 4) + &D_80172FBC);
    M2C_FIELD(temp_a1, s8 *, 0xBA) = 1;
    M2C_FIELD(temp_a1, s16 *, 0xB8) = arg0;
}
