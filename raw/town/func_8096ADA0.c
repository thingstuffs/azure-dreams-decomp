#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Row {
    u8 f0;
    s8 f1;
    s8 f2;
    s8 f3;
    s16 f4;
    s16 f6;
    s8 f8;
    s8 f9;
    s8 f10;
    s8 f11;
} Row;

extern Row D_801331D0[0x10];

void func_80123238(void)
{
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a2;
    s8 *var_a1;
    Row *var_a3;

    var_a3 = &D_801331D0[0];
    var_a2 = 0;
    do {
        var_a1 = (s8 *)var_a3 + 0xB;
        var_a3->f0 = 0xC0;
        M2C_FIELD(var_a1, s8 *, -0xA) = 0x2C;
        M2C_FIELD(var_a1, s8 *, -9) = 0;
        M2C_FIELD(var_a1, s8 *, -8) = 0;
        M2C_FIELD(var_a1, s16 *, -7) = 6;
        M2C_FIELD(var_a1, s16 *, -5) = 0x7C81;
        temp_a0 = var_a2 / 3;
        temp_v1 = var_a2 % 3;
        var_a2 += 1;
        M2C_FIELD(var_a1, s8 *, -3) = (s8)(temp_v1 * 0x48);
        M2C_FIELD(var_a1, s8 *, -2) = (s8)((temp_a0 * 0x10) - 0x80);
        M2C_FIELD(var_a1, s8 *, -1) = 0x48;
        M2C_FIELD(var_a1, s8 *, 0) = 0x10;
        var_a3 += 1;
    } while (var_a2 < 0x10);
}
