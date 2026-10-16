#include "common.h"
#include "m2c_compat.h"

void func_80158A64(void *arg0, void *arg1) {
    s16 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + M2C_FIELD(arg0, s32 *, 0x4C));
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) + M2C_FIELD(arg0, s32 *, 0x50));
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + M2C_FIELD(arg0, s32 *, 0x54));
    var_v0 = M2C_FIELD(arg0, s16 *, 0x36) - M2C_FIELD(arg1, s16 *, 2);
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    if (var_v0 < 0x10) {
        var_v0_2 = M2C_FIELD(arg0, s16 *, 0x38) - M2C_FIELD(arg1, s16 *, 6);
        if (var_v0_2 < 0) {
            var_v0_2 = -var_v0_2;
        }
        if (var_v0_2 < 0x10) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
    }
    var_a0 = M2C_FIELD(arg0, u8 *, 0) * M2C_FIELD(arg0, s16 *, 0x32);
    if (var_a0 < 0) {
        var_a0 += 0xFF;
    }
    var_a1 = M2C_FIELD(arg0, u8 *, 1) * M2C_FIELD(arg0, s16 *, 0x32);
    M2C_FIELD(arg0, s8 *, 4) = (s8) (var_a0 >> 8);
    if (var_a1 < 0) {
        var_a1 += 0xFF;
    }
    var_v1 = M2C_FIELD(arg0, u8 *, 2) * M2C_FIELD(arg0, s16 *, 0x32);
    M2C_FIELD(arg0, s8 *, 5) = (s8) (var_a1 >> 8);
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    M2C_FIELD(arg0, s8 *, 6) = (s8) (var_v1 >> 8);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 8;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s8 *, 4);
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(void *)0x800814A0 = (s32) (*(void *)0x800814A0 | 0x8000);
    }
}
