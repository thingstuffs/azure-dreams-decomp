#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8016DFBC;
extern s32 D_8016E710;
extern s32 D_8016E714;
extern s16 D_8016E718;

void func_8016DBF0(s16 arg0) {
    void *temp_a1;

    D_8016E718 = 0;
    temp_a1 = D_8016E710 + 0x20;
    D_8016E714 = *((arg0 * 4) + &D_8016DFBC);
    M2C_FIELD(temp_a1, s8 *, 0xBA) = 1;
    M2C_FIELD(temp_a1, s16 *, 0xB8) = arg0;
}
