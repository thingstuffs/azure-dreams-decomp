#include "common.h"



typedef struct S_8001A8DC_0 {
    s16 unk_00;
    s16 unk_02;
} S_8001A8DC_0;   /* other in func_8001A8DC */

typedef struct S_8001A8DC_1 {
    u16 unk_00;
    u16 unk_02;
} S_8001A8DC_1;   /* base in func_8001A8DC */

typedef struct S_8001A8DC_2 {
    s16 unk_00;
    s16 unk_02;
} S_8001A8DC_2;   /* out in func_8001A8DC */

s32 func_8001A8DC(void *arg0, void *arg1, s32 arg2, s32 arg3, void *arg4)
{
    s32 temp_lo;
    s32 other_value;
    s32 other_value2;
    s32 var_a3;
    s32 base_value;
    s32 base_value2;
    register void *base ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register void *other ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 original ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 var_t0 ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register void *out ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */

    base = arg0;
    other = arg1;
    original = arg2;
    out = arg4;
    ASM_KEEP(base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(other);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(out);   /* MATCH pin: retail register colouring depends on it */
    var_a3 = arg3;
    var_t0 = original;
    if (original < 0) {
        var_t0 = -var_t0;
    }
    if (var_a3 < 0) {
        var_a3 = -var_a3;
    }
    var_t0 += var_a3;
    other_value = ((S_8001A8DC_0 *)other)->unk_00;
    ASM_KEEP(other_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    base_value = ((S_8001A8DC_1 *)base)->unk_00;
    ASM_KEEP(base_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_8001A8DC_2 *)out)->unk_00 =
        base_value
        + ((other_value - (s16)((S_8001A8DC_1 *)base)->unk_00) * original) / var_t0;
    other_value2 = ((S_8001A8DC_0 *)other)->unk_02;
    ASM_KEEP(other_value2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    base_value2 = ((S_8001A8DC_1 *)base)->unk_02;
    ASM_KEEP(base_value2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_lo =
        (other_value2 - (s16)((S_8001A8DC_1 *)base)->unk_02) * original;
    ((S_8001A8DC_2 *)out)->unk_02 =
        base_value2 + temp_lo / var_t0;
    return temp_lo;
}
