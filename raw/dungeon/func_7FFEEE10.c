#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s32 func_8008CFE8(s32 *, s32, s32);

s32 func_8008C570(void *arg0, s32 arg1, s32 arg2) {
    s32 sp10[5];
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0_2;
    void *temp_s0;

    temp_a2 = arg2 * 0x10;
    temp_s0 = temp_a2 + arg1;
    sp10[0] = M2C_FIELD(arg0, s32 *, 0) + M2C_FIELD(temp_s0, s32 *, 0);
    sp10[1] = M2C_FIELD(arg0, s32 *, 4) + M2C_FIELD(temp_s0, s32 *, 4);
    sp10[2] = M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(temp_s0, s32 *, 8);
    temp_v0 = func_8008CFE8(sp10, arg1, temp_a2);
    if ((temp_v0 << 0x10) == 0) {
        return 0;
    }
    temp_v1 = M2C_FIELD(temp_s0, s32 *, 0);
    var_v0_2 = temp_v1 >> 0x10;
    if (temp_v1 < 0) {
        temp_v1 += 0xFFFF;
        var_v0_2 = temp_v1 >> 0x10;
    }
    return (s16) (temp_v0 - var_v0_2);
}
