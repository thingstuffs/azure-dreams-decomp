#include "common.h"
#include "m2c_compat.h"

s32 func_800A2000();
extern M2C_UNK D_800A2180;
extern M2C_UNK D_800A21EC;

s32 func_800A20D8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    register s32 held_arg0 ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register M2C_UNK held_arg1 ASM_REG("$20") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register M2C_UNK held_arg2 ASM_REG("$21") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 var_s0 ASM_REG("$16") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    M2C_UNK *ptr_2180;
    M2C_UNK *ptr_21EC;

    ptr_2180 = &D_800A2180;
    ptr_21EC = &D_800A21EC;
    ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    var_s0 -= 1;
loop_1:
    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (func_800A2000(held_arg0, held_arg1, held_arg2, var_s0, ptr_2180, ptr_21EC) != 0) {
        goto call_succeeded;
    }
    var_s0 += 1;
    goto done;
call_succeeded:
    if (var_s0 != 0) {
        var_s0 -= 1;
        goto loop_1;
    }
    ASM_CLOBBER("$16");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    var_s0 += 1;
    ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
done:
    return var_s0;
}
