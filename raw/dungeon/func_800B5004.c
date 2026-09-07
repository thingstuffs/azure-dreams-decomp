#include "common.h"

/* Externals (never defined here -- the overlay gate's linker resolves them). */
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_800BA384;
extern s32 D_800BA6B8;

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_800BA764(u16 arg0, u16 arg1, s16 arg2, s32 arg3) {
    void *temp_v0;
    void *temp_v1;
    u32 t0;
    u32 t1;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != 0) {
        FIELD(temp_v0, s32 **, 0x10) = &D_800BA6B8;
        func_8004491C(temp_v0, &D_800BA384);
        temp_v1 = FIELD(temp_v0, void **, 8);
        t0 = (u32)arg0 & 0xFFFFU;
        FIELD(temp_v1, s16 *, 2) = (t0 * 64) + 0x20;
        t1 = (u32)arg1 & 0xFFFFU;
        FIELD(temp_v1, s16 *, 6) = (t1 * 64) + 0x20;
        FIELD(temp_v1, s16 *, 0xA) = arg2;
        FIELD(temp_v0, s32 *, 0x50) = arg3;
    }
    return temp_v0;
}

/* MECHANISM
 * 1. PARM PROMOTION drives the prologue order: declaring arg0/arg1 as u16 pushes their
 *    entry copies into gcc's assign_parms conversion_insns sequence, emitted AFTER the
 *    unpromoted parms -- reproducing retail's sw s3/move a2, sw s4/move a3 BEFORE s1/s2.
 * 2. ANTI-FOLD for the two `andi rX,sN,0xffff`: masking into a separate u32 temp
 *    (t0 = (u32)argN & 0xFFFFU) before the shift keeps the mask out of the narrowing
 *    store's fold, which otherwise deletes it ((s16)((x & 0xFFFF) << 6) folds to x << 6).
 * 3. `* 64` (not an in-place <<= 6) keeps retail's andi/sll/lw/addiu/sh interleave per
 *    store; the `lw 8($s0)` sinks into the first load-delay slot naturally.
 */
