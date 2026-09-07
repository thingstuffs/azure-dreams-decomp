#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern M2C_UNK func_80024610();
extern s32 func_800644B8();
extern s32 func_80064584();

s32 func_818B1484(void *arg0, void *arg1, M2C_UNK arg2) {
    register void *call_a0 ASM_REG("$4");
    s32 sp20[34];
    s32 *var_s5;
    s32 *var_s2;
    s16 temp_s0_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    u16 temp_a2;
    void *var_s2_2;

    var_s5 = sp20;
    var_s1 = 0x10;
    var_s2 = &sp20[16];
    do {
        var_s0 = var_s1;
        if (var_s1 < 0) {
            var_s0 = var_s1 + 0xF;
        }
        temp_s0 = (var_s1 - ((var_s0 >> 4) * 0x10)) << 8;
        M2C_FIELD(var_s2, s32 *, 0) = (u32) (func_800644B8(temp_s0) >> 4);
        M2C_FIELD(var_s2, s32 *, 0x44) = (s32) (func_80064584(temp_s0) >> 4);
        ASM_SCHED_BARRIER();
        var_s1 -= 1;
        var_s2--;
    } while (var_s1 >= 0);
    var_s1_2 = ((s32) (M2C_FIELD(arg0, u16 *, 0x16) << 0x10) >> 0x12) + 1;
    if (var_s1_2 < 8) {
        var_s2_2 = (void *) ((var_s1_2 << 1) + (u32) arg0);
        do {
            temp_v0 = M2C_FIELD(arg0, s16 *, 0x10) - var_s1_2;
            var_a0 = temp_v0;
            if (temp_v0 < 0) {
                var_a0 = temp_v0 + 0xF;
            }
            temp_s0_2 = (func_800644B8((temp_v0 - ((var_a0 >> 4) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(var_s1_2 << 9);
            call_a0 = arg0;
            ASM_KEEP(call_a0);
            temp_a2 = M2C_FIELD(var_s2_2, u16 *, 0x1A);
            var_s2_2 += 2;
            temp_a1 = var_s1_2 << 0x11;
            var_s1_2 += 1;
            func_80024610(call_a0, arg1, arg2, temp_s0_2,
                         (s32) (s16) (M2C_FIELD(arg1, u16 *, 0xA) - temp_a2),
                         var_s5, 0xFF, temp_a1 >> 0x10);
        } while (var_s1_2 < 8);
    }
    return 0;
}
