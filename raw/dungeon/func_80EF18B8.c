#include "common.h"
#include "m2c_compat.h"

void func_8015F0B8(void *arg0, void *arg1) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + M2C_FIELD(arg0, s32 *, 0x4C));
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) + M2C_FIELD(arg0, s32 *, 0x50));
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + M2C_FIELD(arg0, s32 *, 0x54));
    if (M2C_FIELD(arg0, s32 *, 0x40) > 0x40000) {
        M2C_FIELD(arg0, s32 *, 0x40) = 0x40000;
    }
    if (M2C_FIELD(arg0, s32 *, 0x40) < 0xFFFC0000) {
        M2C_FIELD(arg0, s32 *, 0x40) = -0x40000;
    }
    if (M2C_FIELD(arg0, s32 *, 0x44) > 0x40000) {
        M2C_FIELD(arg0, s32 *, 0x44) = 0x40000;
    }
    if (M2C_FIELD(arg0, s32 *, 0x44) < 0xFFFC0000) {
        M2C_FIELD(arg0, s32 *, 0x44) = -0x40000;
    }
    if (M2C_FIELD(arg0, s32 *, 0x48) > 0x40000) {
        M2C_FIELD(arg0, s32 *, 0x48) = 0x40000;
    }
    if (M2C_FIELD(arg0, s32 *, 0x48) < 0xFFFC0000) {
        M2C_FIELD(arg0, s32 *, 0x48) = -0x40000;
    }
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x5A);
    temp_v1 = M2C_FIELD(arg1, s16 *, 2);
    var_v0 = temp_a0 - temp_v1;
    if (temp_v1 < temp_a0) {
        if (var_v0 < 0) {
            var_v0 = -var_v0;
        }
        var_v0_2 = 0x1000;
        if (var_v0 >= 0x11) {
            var_v0_2 = 0x10000;
        }
    } else {
        if (var_v0 < 0) {
            var_v0 = -var_v0;
        }
        var_v0_2 = -0x1000;
        if (var_v0 >= 0x11) {
            var_v0_2 = 0xFFFF0000;
        }
    }
    M2C_FIELD(arg0, s32 *, 0x4C) = var_v0_2;
    temp_a0_2 = M2C_FIELD(arg0, s16 *, 0x5E);
    temp_v1_2 = M2C_FIELD(arg1, s16 *, 6);
    var_v0_3 = temp_a0_2 - temp_v1_2;
    if (temp_v1_2 < temp_a0_2) {
        if (var_v0_3 < 0) {
            var_v0_3 = -var_v0_3;
        }
        var_v0_4 = 0x1000;
        if (var_v0_3 >= 0x11) {
            var_v0_4 = 0x10000;
        }
    } else {
        if (var_v0_3 < 0) {
            var_v0_3 = -var_v0_3;
        }
        var_v0_4 = -0x1000;
        if (var_v0_3 >= 0x11) {
            var_v0_4 = 0xFFFF0000;
        }
    }
    M2C_FIELD(arg0, s32 *, 0x50) = var_v0_4;
    temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x62);
    temp_a1 = M2C_FIELD(arg1, s16 *, 0xA);
    var_v0_5 = temp_v1_3 - temp_a1;
    if (temp_a1 < temp_v1_3) {
        if (var_v0_5 < 0) {
            var_v0_5 = -var_v0_5;
        }
        var_v0_6 = 0x1000;
        if (var_v0_5 >= 0x11) {
            var_v0_6 = 0x10000;
        }
    } else {
        if (var_v0_5 < 0) {
            var_v0_5 = -var_v0_5;
        }
        var_v0_6 = -0x1000;
        if (var_v0_5 >= 0x11) {
            var_v0_6 = 0xFFFF0000;
        }
    }
    M2C_FIELD(arg0, s32 *, 0x54) = var_v0_6;
}
