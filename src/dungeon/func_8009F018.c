#include "common.h"

extern s32 func_8009A350();
extern s32 func_800BCB04();

s32 func_800A4778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 r_arg0 ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 r_arg1 = arg1;
    s16 sp10;
    s16 temp_v0_3;
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_v0;
    s32 var_v0_3;
    register s32 temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_s2;
    register s32 temp_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_v0_2;
    s32 var_v0_4;
    u32 temp_a0;
    register u32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u32 temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(r_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_s2 = arg2;
    temp_v0 = r_arg0;
    temp_s5 = temp_s2;
    if (arg3 == 0) {
        temp_v0 = (u32) (temp_v0 & 0xFFFF) >> 6;
        temp_a0 = temp_v0 - 1;
        temp_a1 = (u32) (r_arg1 & 0xFFFF) >> 6;
        temp_a2 = 0;
        ASM_USE(temp_a2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        temp_s0 = temp_v0;
        temp_v0_2 = temp_a1;
        if ((func_8009A350(temp_a0, temp_a1, temp_a2, &sp10) << 0x10) != 0) {
            temp_v0 = temp_s0 << 6;
            ASM_KEEP(temp_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            temp_s0 = temp_v0 + 0x20;
            temp_a0 = temp_s0 & 0xFFE0;
            temp_v0 = temp_v0_2 << 6;
            ASM_KEEP(temp_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            temp_v0 += 0x20;
            temp_a1 = temp_v0 & 0xFFE0;
            temp_a2 = (s16) (temp_s2 - 0x20);
            temp_v0_2 = temp_v0;
            temp_v0_3 = func_800BCB04(temp_a0, temp_a1, temp_a2);
            sp10 = temp_v0_3;
            if (temp_v0_3 >= 0x201) {
                temp_s2 = temp_s0;
                ASM_KEEP_NV(temp_s0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                temp_v0 = temp_s0 - r_arg0;
                temp_v1 = (s16) temp_v0;
                var_v0 = temp_v1;
                if (temp_v1 < 0) {
                    var_v0 = 0 - var_v0;
                }
                var_a0 = 0;
                if (var_v0 >= 0x16) {
                    var_v0_2 = 0x40;
                    if (temp_v1 > 0) {
                        var_v0_2 = -0x40;
                    }
                    var_a0 = var_v0_2;
                }
                temp_v0 = temp_v0_2 - r_arg1;
                temp_v1 = (s16) temp_v0;
                var_v0_3 = temp_v1;
                if (temp_v1 < 0) {
                    var_v0_3 = 0 - var_v0_3;
                }
                if (var_v0_3 >= 0x16) {
                    var_v0_4 = 0x40;
                    if (temp_v1 > 0) {
                        var_v0_4 = -0x40;
                    }
                } else {
                    var_v0_4 = 0;
                }
                sp10 = func_800BCB04((temp_s2 + var_a0) & 0xFFFF, (temp_v0_2 + var_v0_4) & 0xFFFF, (s16) (temp_s5 - 0x20));
                return sp10 > 0x200;
            }
        }
    }
    return 0;
}
