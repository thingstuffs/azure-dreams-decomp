#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

s32 func_8001A8DC(void *arg0, void *arg1, s32 arg2, s32 arg3, void *arg4)
{
    s32 temp_lo;
    s32 other_value;
    s32 other_value2;
    s32 var_a3;
    s32 base_value;
    s32 base_value2;
    register void *base ASM_REG("$4");
    register void *other ASM_REG("$5");
    register s32 original ASM_REG("$6");
    register s32 var_t0 ASM_REG("$8");
    register void *out ASM_REG("$9");

    base = arg0;
    other = arg1;
    original = arg2;
    out = arg4;
    ASM_KEEP(base);
    ASM_KEEP(other);
    ASM_KEEP(original);
    ASM_KEEP(out);
    var_a3 = arg3;
    var_t0 = original;
    if (original < 0) {
        var_t0 = -var_t0;
    }
    if (var_a3 < 0) {
        var_a3 = -var_a3;
    }
    var_t0 += var_a3;
    ASM_KEEP(var_t0);
    other_value = FIELD(other, s16, 0);
    ASM_KEEP(other_value);
    base_value = FIELD(base, u16, 0);
    ASM_KEEP(base_value);
    FIELD(out, s16, 0) =
        base_value
        + ((other_value - (s16)FIELD(base, u16, 0)) * original) / var_t0;
    other_value2 = FIELD(other, s16, 2);
    ASM_KEEP(other_value2);
    base_value2 = FIELD(base, u16, 2);
    ASM_KEEP(base_value2);
    temp_lo =
        (other_value2 - (s16)FIELD(base, u16, 2)) * original;
    FIELD(out, s16, 2) =
        base_value2 + temp_lo / var_t0;
    return temp_lo;
}
