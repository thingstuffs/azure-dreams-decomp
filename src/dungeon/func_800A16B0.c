#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;

s16 func_800A6E10(s16 arg0, s16 arg1) {
    M2C_UNK *var_a2;
    M2C_UNK *var_v1;
    s16 var_t0;
    s32 var_a3;
    s32 check_arg0;
    s32 check_arg1;
    u8 *page;
    register s32 initial ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    initial = 0;
    ASM_KEEP(initial);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    var_a3 = initial;
    var_t0 = initial;
    check_arg0 = arg0;
    check_arg1 = arg1;
#ifdef NON_MATCHING
    var_v1 = &D_800E36C8;
    var_a2 = &D_800E3548;
#else
    ASM_USE(check_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_v1 = (M2C_UNK *)(page + 0x36C8);
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_a2 = (M2C_UNK *)(page + 0x3548);
#endif
    do {
        if ((*((u8 *) var_a2 + 1) != 0) && (*((u8 *) var_v1) == check_arg0) && (*((u8 *) var_v1 + 1) == check_arg1)) {
            var_t0 += 1;
        }
        var_v1 += 3;
        var_a3 += 1;
        var_a2 += 1;
    } while (var_a3 < 0x40);
    return var_t0;
}
