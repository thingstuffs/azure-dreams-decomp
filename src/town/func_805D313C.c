#include "common.h"

extern s32 func_80016250(s32);
extern void func_800193E0(s32);

extern s32 D_8001967C;
extern s32 D_80019760[];
extern u8 D_8001AAEC[];
extern u8 D_8001DE58[];
extern u8 D_80020C9C[];

s32 func_8001713C(s32 unused0, s32 unused1, s32 selector) {
    s32 result = 0;

    if (selector == 8) {
        result = func_80016250(D_80019760[D_8001967C]);
        func_800193E0(0x147A);
    } else if (selector == 1) {
        if (D_8001967C != 3) {
            result = (s32)D_8001DE58;
        } else {
            result = (s32)D_8001AAEC;
        }
    } else if (selector == 3) {
        result = (s32)D_80020C9C;
    }

    return result;
}

/* MECHANISM: the row's two tail targets (true base +0x94 / +0x98) are its own epilogue;
   the plain `result` chain returning through one exit reproduces both entries. The former
   D4/D0 pseudo-calls and their ASM_KEEP pins were removed 2026-09-22 (byte-exact). */
