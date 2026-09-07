#include "common.h"

extern s32 D_80175D78[];

void func_8016EB68(void) {
    s32 *var_a0;
    s32 var_a1;
    void *temp_v1;
    u16 temp_v0;

    var_a1 = 0;
    var_a0 = D_80175D78;
    do {
        temp_v1 = *var_a0 + 0x20;
        temp_v0 = *(u16 *)(temp_v1 + 0x12);
        
        var_a1 += 1;
        *(s16 *)(temp_v1 + 0x18) = 0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        *(u16 *)(temp_v1 + 0x12) = temp_v0 + 1;
        var_a0 += 1;
    } while (var_a1 < 0x10);
}

/* MECHANISM: Frameless leaf loop retained; an explicit u16 temp exposes the retail RMW lifetime.
   The v0 pin+keep preserves the load-delay nop and places the increment below lhu.
   A fence after the zero store leaves a0 += 4 available for the loop branch delay slot. */
