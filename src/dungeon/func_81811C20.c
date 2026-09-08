#include "common.h"

typedef struct S_80026C20_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
} S_80026C20_0;   /* temp_a0 in func_80026C20 */

typedef struct S_80026C20_1 {
    u8 unk_00;
    union { u8 s; volatile u8 u; } unk_01;   /* accessed as both */
} S_80026C20_1;   /* var_a2 in func_80026C20 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80029510[12];

s32 func_80026C20(s32 arg0) {
    s32 temp_v1;
    s32 loop_bound;
    register s32 compare_space ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    u8 temp_a1;
    u8 global_byte;
    S_80026C20_0 *temp_a0;
    void *temp_a0_2;
    S_80026C20_1 *var_a2;
    u8 *global;

    var_t0 = 0;
    if (arg0 != 0) {
        temp_a0 = arg0 + 0x20;
        var_a1 = 9;
        if (temp_a0->unk_0C == 0x13) {
            var_a1 = 6;
        }
        temp_v1 = var_a1 * 2;
        var_a3 = 0;
        if (var_t0 < temp_v1) {
            global = D_80029510;
            compare_space = 0x20;
            loop_bound = temp_v1;
            temp_a0_2 = temp_a0->unk_14;
            global_byte = D_80029510[0];
loop_5:
            var_a2 = temp_a0_2 + var_a3;
            temp_a1 = var_a2->unk_00;
            if (temp_a1 != 0) {
                if (((temp_a1 != global_byte) ||
                     (var_a2->unk_01.s !=
                      global[1])) &&
                    ((temp_a1 != compare_space) ||
                     (var_a2->unk_01.u != temp_a1))) {
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
