#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8008B0E8();


typedef struct S_8008B23C_0 {
    u32 unk_00;
    s32 unk_04;
} S_8008B23C_0;   /* var_s0 in func_8008B23C */

void func_8008B23C(u8 *arg0) {
    u8 *var_s0;
    u32 temp_a2;

    var_s0 = arg0;
    if (((S_8008B23C_0 *)var_s0)->unk_04 != 0) {
        do {
            temp_a2 = ((S_8008B23C_0 *)var_s0)->unk_00;
            func_8008B0E8(
                (temp_a2 >> 0x17) & 1,
                (u32)(temp_a2 & 0x3F000000) >> 0x18,
                (u32)(temp_a2 & 0x7F0000) >> 0x10
            );
            var_s0 += 8;
        } while (((S_8008B23C_0 *)var_s0)->unk_04 != 0);
    }
}
