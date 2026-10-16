#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_80083350;
extern M2C_UNK D_800EA000;

s32 func_8001CBD4(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;

    temp_v1 = arg2 * 2;
    var_v0 = arg2 << 0x10;
    if (M2C_FIELD((((((s16) (arg1 + *(temp_v1 + &D_8006CCE8)) << D_80083350) + (s16) (arg0 + *(temp_v1 + &D_8006CCD8))) * 6) + &D_800EA000), u16 *, 4) != 0) {
        var_a1 = 2;
        var_v0_2 = arg2 + 2;
loop_2:
        temp_v0 = (var_v0_2 & 6) * 2;
        if (M2C_FIELD((((((s16) (arg1 + *(temp_v0 + &D_8006CCE8)) << D_80083350) + (s16) (arg0 + *(temp_v0 + &D_8006CCD8))) * 6) + &D_800EA000), u16 *, 4) == 0) {
            return (arg2 + var_a1) & 6;
        }
        var_a1 += 4;
        var_v0_2 = arg2 + var_a1;
        if (var_a1 >= 7) {
            var_v0 = arg2 << 0x10;
            goto block_6;
        }
        goto loop_2;
    }
block_6:
    return var_v0 >> 0x10;
}
