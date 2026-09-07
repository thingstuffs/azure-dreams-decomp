#include "common.h"

extern s32 D_80018FB4;
extern s32 D_80018FB8;
extern s32 D_8001925C;

extern void func_800181C8();

void func_80016D00(s32 arg0, s32 arg1, s32 arg2) {
    register s32 index ASM_REG("$2") = D_80018FB4 % 3;
    register s32 doubled ASM_REG("$3") = index << 1;
    register s32 tripled ASM_REG("$4") = index + doubled;

    if (0) {
        ASM_KEEP(index);
        ASM_KEEP(doubled);
        ASM_KEEP(tripled);
    }
    func_800181C8(
        (tripled << 3) + (u8 *)&D_80018FB8,
        &D_8001925C,
        arg0,
        arg2);
}

/* MECHANISM: The 24-byte outgoing-argument frame saves only $ra; no callee-saved holds.
   -fno-schedule-insns preserves the retail global-load-before-divide-magic order.
   Guarded short roles index:$v0, doubled:$v1, tripled:$a0 close the scale-tree coloring. */
