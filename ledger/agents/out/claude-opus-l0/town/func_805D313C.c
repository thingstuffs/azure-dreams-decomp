#include "common.h"

extern s32 func_80016250(s32);
extern void func_800193E0(s32);

extern s32 D_8001967C;
extern s32 D_80019760[];
extern u8 D_8001AAEC[];
extern u8 D_8001DE58[];
extern u8 D_80020C9C[];

s32 func_8001713C(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = 0;

    if (arg2 == 8) {
        result = func_80016250(D_80019760[D_8001967C]);
        func_800193E0(0x147A);
    } else if (arg2 == 1) {
        if (D_8001967C != 3) {
            result = (s32)D_8001DE58;
        } else {
            result = (s32)D_8001AAEC;
        }
    } else if (arg2 == 3) {
        result = (s32)D_80020C9C;
    }

    return result;
}

/* MECHANISM: The 24-byte frame and s0 result preserve the retail prologue and held value.
   Explicit D4/D0 tail calls expose the original-base merge targets to LEAD 22.
   Post-call ASM_KEEP holds each D0 address in s0 while the callee result remains in v0. */
