#include "common.h"
#include "m2c_compat.h"

void func_800B474C(void **arg0) {
    s32 temp_v0;
    s32 var_a1;
    void **var_a2;

    var_a1 = 0;
    var_a2 = arg0;
    do {
        M2C_FIELD(M2C_FIELD(*var_a2, void **, 4), s16 *, 8) = (s16) (((var_a1 / 5) << 7) + 0x58);
        temp_v0 = var_a1 % 5;
        var_a1 += 1;
        M2C_FIELD(M2C_FIELD(*var_a2, void **, 4), s16 *, 0xA) = (s16) ((temp_v0 * 0x10) + 0x88);
        var_a2 += 4;
    } while (var_a1 < 0xA);
}
