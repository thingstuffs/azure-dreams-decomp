#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8014EFBC;
extern s32 D_8014F710;
extern s32 D_8014F714;
extern s16 D_8014F718;

void func_8014EBF0(s16 arg0) {
    void *temp_a1;

    D_8014F718 = 0;
    temp_a1 = D_8014F710 + 0x20;
    D_8014F714 = *((arg0 * 4) + &D_8014EFBC);
    M2C_FIELD(temp_a1, s8 *, 0xBA) = 1;
    M2C_FIELD(temp_a1, s16 *, 0xB8) = arg0;
}
