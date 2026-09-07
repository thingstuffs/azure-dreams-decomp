#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern s32 func_80024AE8();

void func_80025710(void *arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4) {
    register s32 match_x ASM_REG("$21") = arg1;
    register s32 match_y ASM_REG("$20") = arg2;
    s32 match_lo;
    s32 match_hi;
    s16 temp_v1;
    u16 temp_v1_2;
    void *temp_a1;
    void *temp_a2;
    register void *temp_next ASM_REG("$2");
    void *var_a0;
    register void *var_s0 ASM_REG("$16");
    register void *var_s1 ASM_REG("$17");

    var_s0 = arg0;
    var_s1 = var_s0;
    temp_next = FIELD(var_s0, s32 *, 0x5C);
    var_s0 = temp_next + 0x20;
    if (var_s0 != var_s1) {
        ASM_KEEP(var_s0);
        ASM_USE(temp_next);
        match_lo = (s16)arg3;
        match_hi = (s16)arg4;
        ASM_USE2(match_lo, match_hi);
        var_a0 = var_s0 - 0x20;
        do {
            temp_a2 = FIELD(var_s0, void **, -0x14);
            temp_a1 = FIELD(var_a0, void **, 8);
            if ((FIELD(temp_a2, u8 *, 0x24) == (match_x & 0xFFFF)) &&
                (FIELD(temp_a2, u8 *, 0x25) == (match_y & 0xFFFF))) {
                temp_v1 = FIELD(temp_a1, s16 *, 0xA);
                if ((match_lo >= temp_v1) && (match_hi < temp_v1)) {
                    temp_v1_2 = FIELD(var_a0, u16 *, 0x1E);
                    if (!(temp_v1_2 & 0x2000)) {
                        FIELD(var_a0, u16 *, 0x1E) = temp_v1_2 | 0x2000;
                        func_80024AE8(var_a0, temp_a1, temp_a2);
                    }
                }
            }
            temp_next = FIELD(var_s0, s32 *, 0x5C);
            var_s0 = temp_next + 0x20;
            ASM_KEEP(var_s0);
            ASM_USE(temp_next);
            var_a0 = var_s0 - 0x20;
        } while (var_s0 != var_s1);
    }
}
