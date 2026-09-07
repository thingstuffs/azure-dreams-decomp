#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80029510[12];

s32 func_80026C20(s32 arg0) {
    register s32 temp_v1 ASM_REG("$3");
    register s32 loop_bound ASM_REG("$10");
    register s32 compare_space ASM_REG("$11");
    register s32 var_a1 ASM_REG("$5");
    s32 var_a3;
    register s32 var_t0 ASM_REG("$8");
    u8 temp_a1;
    register u8 global_byte ASM_REG("$9");
    void *temp_a0;
    void *temp_a0_2;
    void *var_a2;
    register u8 *global ASM_REG("$12");

    var_t0 = 0;
    if (arg0 != 0) {
        temp_a0 = arg0 + 0x20;
        var_a1 = 9;
        if (M2C_FIELD(temp_a0, s32 *, 0xC) == 0x13) {
            var_a1 = 6;
        }
        temp_v1 = var_a1 * 2;
        var_a3 = 0;
        if (var_t0 < temp_v1) {
            global = D_80029510;
            compare_space = 0x20;
            loop_bound = temp_v1;
            temp_a0_2 = M2C_FIELD(temp_a0, void **, 0x14);
            global_byte = D_80029510[0];
loop_5:
            var_a2 = temp_a0_2 + var_a3;
            temp_a1 = M2C_FIELD(var_a2, u8 *, 0);
            if (temp_a1 != 0) {
                if (((temp_a1 != global_byte) ||
                     (M2C_FIELD(var_a2, u8 *, 1) !=
                      global[1])) &&
                    ((temp_a1 != compare_space) ||
                     (M2C_FIELD(var_a2, volatile u8 *, 1) != temp_a1))) {
                    var_t0 = 1;
                }
                var_a3 += 2;
                if (var_a3 < loop_bound) {
                    goto loop_5;
                }
            }
        }
    }
    return var_t0;
}

/* MECHANISM: Frameless leaf with held t0/t1/t2/t3/t4 roles and a volatile second byte read.
   Distinct a1 -> v1 -> t2 bound lifetimes plus the t0-relative test force retail's slt/beqz
   and move handoff, restoring the two missing words and every cascaded branch displacement. */
