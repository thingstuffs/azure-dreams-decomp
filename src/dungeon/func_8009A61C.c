#include "common.h"

extern s32 func_8009FB34();
extern s32 func_800A0818(s32, s32, s32, s32, s16 *);

s32 func_8009FD7C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 raw0 = arg0;
    register u16 raw1 ASM_REG("$9") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    u16 raw2 = arg2;
    u16 raw3 = arg3;
    s16 sp18;
    s32 temp_s0;
    register s32 call_arg0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call_arg1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 saved_result;
    s32 second_result;
    s16 *stack_arg;
    s32 call_arg2;
    s32 call_arg3;
    s32 temp_v0;
    register s32 temp_v0_2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 signed0 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 signed1 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 signed2 ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 signed3 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 temp_v1;
    s32 var_a0;
    s32 var_v0;
    s32 var_v1;
    register s32 sum ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    signed2 = (s16) arg2;
    signed0 = (s16) arg0;
    temp_v0 = signed2 - signed0;
    var_a0 = __builtin_abs(temp_v0);
    if (var_a0 < 2) {
        temp_v0_2 = arg3 << 0x10;
        signed3 = temp_v0_2 >> 0x10;
        temp_v0_2 = arg1 << 0x10;
        signed1 = temp_v0_2 >> 0x10;
        temp_v0_2 = signed3 - signed1;
        var_v1 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_v1 = -var_v1;
        }
        if (var_v1 < 2) {
            sum = var_a0 + var_v1;
            ASM_KEEP_NV(raw0);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ASM_KEEP_NV(raw1);   /* MATCH pin: retail schedule: same instructions, different order without it */
            if (sum != 0) {
                call_arg0 = raw0 & 0xFFFF;
                call_arg1 = raw1 & 0xFFFF;
                temp_s0 = func_8009FB34(call_arg0, call_arg1, arg2 << 0x10);
                ASM_KEEP_NV(raw2);   /* MATCH pin: load-bearing for the whole function shape */
                call_arg0 = raw2 & 0xFFFF;
                call_arg1 = raw3 & 0xFFFF;
                saved_result = temp_s0;
                second_result = func_8009FB34(call_arg0, call_arg1);
                if ((saved_result << 0x10) == (second_result << 0x10)) {
                    return 1;
                }
                call_arg0 = signed0;
                call_arg1 = signed1;
                stack_arg = &sp18;
                ASM_KEEP(stack_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
                call_arg2 = signed2;
                call_arg3 = signed3;
                temp_v1 = (s32) (func_800A0818(call_arg0, call_arg1, call_arg2, call_arg3, stack_arg) << 0x10) >> 0x19;
                sp18 = (s16) temp_v1;
                var_v0 = 1;
                if (temp_v1 & 1) {
                    goto block_11;
                }
                return var_v0;
            }
        }
        goto block_11;
    }
block_11:
    var_v0 = 0;
    return var_v0;
}
