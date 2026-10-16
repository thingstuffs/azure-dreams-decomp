#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009C93C(void *, s32, s16, M2C_UNK, s32); /* extern */

void func_80150800(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    s16 temp_v1;
    s32 temp_s7;
    void *temp_a0;
    void *var_s0;

    temp_s7 = M2C_FIELD(arg0, s32 *, -0x14);
    var_s0 = M2C_FIELD(arg0, s32 *, 0x5C) + 0x20;
    if (var_s0 != arg0) {
        do {
            temp_a0 = M2C_FIELD(var_s0, void **, -0x14);
            if ((M2C_FIELD(temp_a0, u8 *, 0x24) == (arg1 & 0xFFFF)) && (M2C_FIELD(temp_a0, u8 *, 0x25) == (arg2 & 0xFFFF))) {
                temp_v1 = M2C_FIELD(M2C_FIELD(var_s0, void **, -0x18), s16 *, 0xA);
                if (((arg3 + 0x38) >= temp_v1) && ((arg3 - 0x38) < temp_v1) && ((u32) (M2C_FIELD(var_s0, u8 *, 0x13) - 0x33) >= 4U)) {
                    M2C_FIELD(arg0, s8 *, 0x84) = 0x7C;
                    M2C_FIELD(arg0, s8 *, 0x85) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0x26) * 3) >> 1);
                    func_8009C93C(arg0, temp_s7, M2C_FIELD(arg0, s16 *, 0x2A), 1, 0);
                }
            }
            var_s0 = M2C_FIELD(var_s0, s32 *, 0x5C) + 0x20;
        } while (var_s0 != arg0);
    }
}
