#include "common.h"

extern s32 func_80016250(s32);
extern s32 func_800171D0(void);
extern void func_800171D4(void);
extern void func_800193E0(s32);

extern s32 D_8001967C;
extern s32 D_80019760[];
extern u8 D_8001AAEC[];
extern u8 D_8001DE58[];
extern u8 D_80020C9C[];

s32 func_805D313C(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = 0;
    s32 tail_result;

    if (arg2 == 8) {
        result = func_80016250(D_80019760[D_8001967C]);
        func_800193E0(0x147A);
        func_800171D4();
    } else if (arg2 == 1) {
        if (D_8001967C != 3) {
            result = (s32)D_8001DE58;
            tail_result = func_800171D0();
            ASM_KEEP(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            return tail_result;
        } else {
            result = (s32)D_8001AAEC;
            tail_result = func_800171D0();
            ASM_KEEP(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            return tail_result;
        }
    } else if (arg2 == 3) {
        result = (s32)D_80020C9C;
    }

    return result;
}

/* MECHANISM: The 24-byte frame and s0 result preserve the retail prologue and held value.
   Explicit D4/D0 tail calls expose the original-base merge targets to LEAD 22.
   Post-call ASM_KEEP holds each D0 address in s0 while the callee result remains in v0. */
