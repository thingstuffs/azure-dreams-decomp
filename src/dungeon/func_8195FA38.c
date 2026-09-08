#include "common.h"

extern s32 func_80024C3C();
extern void func_800252AC() __attribute__((noreturn));
extern void func_800252C0() __attribute__((noreturn));

s32 func_8195FA38(void *arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    register s32 var_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    register s32 var_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    var_s2 = 0;
    var_s7 = 6;
    var_s6 = 0xF;
    var_s5 = 0x10;
    var_s3 = -0x80;
loop_1:
    var_s0 = 0;
    var_s4 = (s16)var_s2;
loop_2:
    *(s8 *)((s8 *)arg0 + 8) = var_s0 * 0x10;
    *(s8 *)((s8 *)arg0 + 9) = var_s3;
    if (var_s0 == var_s7) {
        *(s8 *)((s8 *)arg0 + 0xA) = var_s6;
        func_800252AC();
    }
    *(volatile s8 *)((s8 *)arg0 + 0xA) = var_s5;
    if (var_s2 == var_s7) {
        *(s8 *)((s8 *)arg0 + 0xB) = var_s6;
        func_800252C0();
    }
    *(volatile s8 *)((s8 *)arg0 + 0xB) = var_s5;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80024C3C(arg0, arg1, arg2, (s16)var_s0, var_s4);
    var_s0 += 1;
    if (var_s0 >= 7) {
        var_s2 += 1;
        var_s3 += 0x10;
        if (var_s2 >= 7) {
            return 0;
        }
        goto loop_1;
    }
    goto loop_2;
}
