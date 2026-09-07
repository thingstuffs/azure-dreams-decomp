#include "common.h"

void *func_805D3AC8(void *arg0) {
    s32 var_a2 = 0;
    register s32 var_a1 ASM_REG("$5") = 1;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 var_a3 = 0x19;
    register void *var_v1 ASM_REG("$3") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s8 *temp_v0;

    do {
        *((s8 *)var_v1 + 0) = var_a1;
        *((s8 *)var_v1 + 1) = var_a3;
        *((s8 *)var_v1 + 3) = 0;
        *((s8 *)var_v1 + 2) = 0;
        var_v1 += 4;
        var_a1 += 1;
        var_a2 += 1;
    } while (var_a1 < 0x10);

    temp_v0 = (s8 *)((u32)(var_a2 * 4) + (u32)arg0);
    temp_v0[1] = 0;
    temp_v0[0] = 0;
    return arg0;
}

/* MECHANISM: Frameless leaf; a2 stays natural while a1/a3/v1/v0 hold the retail roles.
   Naming the invariant a3 before the pointer init fixes the opening emission order.
   An ordered u32 tail sum preserves retail's addu v0,v0,a0 operand order. */
