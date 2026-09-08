#include "common.h"

extern s32 func_80018964(s32);
extern void func_800188E4(s32);
extern void *D_80016000[];
extern void *D_800190C0[];

/* Conditionally updates flag 0x619, then dispatches D_800190C0 to the callback. */
void func_8059E728(void) {
    if (func_80018964(0x11FE) != 0) {
        func_800188E4(0x619);
    }
    ((void (*)(void *))(*(void ***)((s8 *)D_80016000[0] + 0x20))[0x86])(D_800190C0);
}

/* MECHANISM: The call-shaped body naturally gives the 0x18 frame with only ra saved.
   The direct pointer/vtable load chain preserves the two dependent load-delay nops.
   Town's 2.7.2-cdk-G0 schedule places the page base and indirect-call argument exactly. */
