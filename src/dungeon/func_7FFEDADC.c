#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8008B0E8();

void func_8008B23C(u8 *arg0) {
    u8 *var_s0;
    u32 temp_a2;

    var_s0 = arg0;
    if (M2C_FIELD(var_s0, s32 *, 4) != 0) {
        do {
            temp_a2 = M2C_FIELD(var_s0, u32 *, 0);
            func_8008B0E8(
                (temp_a2 >> 0x17) & 1,
                (u32)(temp_a2 & 0x3F000000) >> 0x18,
                (u32)(temp_a2 & 0x7F0000) >> 0x10
            );
            var_s0 += 8;
        } while (M2C_FIELD(var_s0, s32 *, 4) != 0);
    }
}
