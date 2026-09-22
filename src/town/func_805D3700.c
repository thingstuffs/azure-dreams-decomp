#include "common.h"

extern u8 D_800198A4[];
extern u8 D_80019A6C[];
extern s32 D_80019B8C[3];

extern void func_800193E0(s32);
extern s32 func_800194D8(s32);

/* Return the cached blob when the cue is already playing, otherwise start it and return the state's row. */
s32 func_805D3700(void) {
    s32 *indexp;
    u8 *base;
    s32 offset;
    s32 result;

    indexp = D_80019B8C;
    if (func_800194D8(*indexp + 0x147A) != 0) {
        result = (s32)D_80019A6C;
    } else {
        func_800193E0(*indexp + 0x147A);
        base = D_800198A4;
        offset = *indexp * 0x18;
        result = *(s32 *)(base + offset);
    }
    return result;
}

/* MECHANISM: A 12-byte D_80019B8C declaration holds its page in retail's sole s0 save.
   The noreturn path plus a guarded v0 tail-slot pin splits D_80019A6C across the
   branch/jump delays; cdk-G0 preserves the retail reload and epilogue-load order. */
