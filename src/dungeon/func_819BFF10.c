#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern s32 func_80024AE8();

void func_80025710(void *arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4) {
    s32 match_x = arg1;
    s32 match_y = arg2;
    s32 match_lo;
    s32 match_hi;
    s16 temp_v1;
    u16 temp_v1_2;
    void *temp_a1;
    void *temp_a2;
    register void *temp_next ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *var_a0;
    void *var_s0;
    register void *var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    var_s0 = arg0;
    var_s1 = var_s0;
    temp_next = FIELD(var_s0, s32 *, 0x5C);
    var_s0 = temp_next + 0x20;
    if (var_s0 != var_s1) {
        ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        match_lo = (s16)arg3;
        match_hi = (s16)arg4;
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
            ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            var_a0 = var_s0 - 0x20;
        } while (var_s0 != var_s1);
    }
}
