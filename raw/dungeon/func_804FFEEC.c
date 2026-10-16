#include "common.h"
#include "m2c_compat.h"

extern s16 D_8008146E;
extern M2C_UNK D_800E2970;

void func_800176EC(void) {
    M2C_UNK *var_a2;
    M2C_UNK *var_t0;
    s16 var_a3_2;
    s16 var_t1;
    s32 var_a3;
    void *var_v1;

    var_a3 = 0;
    var_t1 = 0;
    var_a2 = &D_800E2970;
    var_t0 = &D_800E2970;
    do {
        if (M2C_FIELD(var_a2, s16 *, 0xA) != 0) {
            if (var_a3 != var_t1) {
                M2C_FIELD(var_t0, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
                M2C_FIELD(var_t0, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
                M2C_FIELD(var_t0, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
                M2C_FIELD(var_t0, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
                M2C_FIELD(var_t0, s32 *, 0x10) = (s32) M2C_FIELD(var_a2, s32 *, 0x10);
            }
            var_t0 += 0x14;
            var_t1 += 1;
        }
        var_a3 += 1;
        var_a2 += 0x14;
    } while (var_a3 < 0x24);
    var_a3_2 = var_t1;
    if (var_t1 < 0x24) {
        var_v1 = (var_t1 * 0x14) + &D_800E2970;
        do {
            M2C_FIELD(var_v1, s16 *, 0xA) = 0;
            M2C_FIELD(var_v1, s16 *, 0xE) = 0;
            M2C_FIELD(var_v1, s32 *, 0x10) = 0;
            var_a3_2 += 1;
            var_v1 += 0x14;
        } while (var_a3_2 < 0x24);
    }
    D_8008146E = var_t1;
}
