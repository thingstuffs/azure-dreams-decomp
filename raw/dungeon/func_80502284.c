#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

void func_80019A84(s16 arg0) {
    s32 var_a1;
    s32 var_a2;
    void *temp_v1;

    var_a2 = 1;
    do {
        var_a1 = 1;
loop_2:
        temp_v1 = ((var_a1 + (var_a2 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + &D_800EA000;
        if (M2C_FIELD(temp_v1, u16 *, 0) == 0) {
            M2C_FIELD(temp_v1, s16 *, 2) = arg0;
        }
        var_a1 += 1;
        if (var_a1 < 0x3F) {
            goto loop_2;
        }
        var_a2 += 1;
    } while (var_a2 < 0x3F);
}
