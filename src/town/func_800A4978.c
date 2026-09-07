#include "common.h"
#include "m2c_compat.h"

s32 func_800A2000();
extern void func_800A2154(void) __attribute__((noreturn));
extern M2C_UNK D_800A2180;
extern M2C_UNK D_800A21EC;

s32 func_800A20D8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    register s32 held_arg0 ASM_REG("$19") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register M2C_UNK held_arg1 ASM_REG("$20") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register M2C_UNK held_arg2 ASM_REG("$21") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 var_s0 ASM_REG("$16") = arg3;   /* MATCH pin: retail immediate-load split depends on it */
    M2C_UNK *ptr_2180;
    M2C_UNK *ptr_21EC;

    ptr_2180 = &D_800A2180;
    ptr_21EC = &D_800A21EC;
    ASM_KEEP(var_s0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_s0 -= 1;
loop_1:
    ASM_KEEP(held_arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(held_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(held_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (func_800A2000(held_arg0, held_arg1, held_arg2, var_s0, ptr_2180, ptr_21EC) != 0) {
        goto call_succeeded;
    }
    var_s0 += 1;
    ASM_TAILSLOT_PIN(var_s0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_800A2154();
call_succeeded:
    if (var_s0 != 0) {
        var_s0 -= 1;
        goto loop_1;
    }
    ASM_CLOBBER("$16");   /* MATCH pin: retail immediate-load split depends on it */
    var_s0 += 1;
    ASM_KEEP(var_s0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    return var_s0;
}
