#include "common.h"

extern void func_800C46A8(void *arg0);
extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[][8];
extern s32 D_800C5FDC[];
extern s32 D_800D5590[];

void func_800C5F70(void *arg0, s32 arg1, s32 arg2) {
    register void *call_obj ASM_REG("$4");
    register s32 call_arg ASM_REG("$5");

    D_80082660[*((s32 *)arg0 + 0x18)][0] = 0;
    func_800C46A8(arg0);
    call_obj = arg0;
    ASM_KEEP(call_obj);
    call_arg = arg2;
    ASM_KEEP(call_arg);
    func_800C2E84(call_obj, call_arg, D_800D5590);
    *((s32 **)arg0 + 0x15) = D_800C5FDC;
}

/* MECHANISM: The seed already had retail's 0x20 frame and s0/s1/ra hold contract.
   Guarded $a0 then $a1 call-register staging keeps both moves ahead of D_800D5590's lui.
   This closes the equal-length reorder-only residue without changing CFG or word count. */
