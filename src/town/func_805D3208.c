#include "common.h"

extern s32 func_80016250(u32);
extern void func_80017284(void) __attribute__((noreturn));
extern void func_800193E0(s32);

extern s32 D_8001967C[];
extern s32 D_80019770[];
extern u8 D_8001AAEC[];
extern u8 D_8001DE58[];

s32 func_805D3208(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = 0;

    if (arg2 == 8) {
        register s32 tail_result ASM_REG("$3");   /* MATCH pin: retail delay-slot contents depend on it */

        func_800193E0(0x147A);
        tail_result = func_80016250(D_80019770[D_8001967C[0]]);
        ASM_TAILSLOT_PIN(tail_result);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80017284();
    } else if (arg2 == 1) {
        if (D_8001967C[0] != 3) {
            register u32 page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
            register s32 tail_result ASM_REG("$3");   /* MATCH pin: retail delay-slot contents depend on it */

            page = 0x80020000;
            ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            tail_result = page - 0x21A8;
            ASM_TAILSLOT_PIN(tail_result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80017284();
        } else {
            result = (s32)D_8001AAEC;
        }
    }

    return result;
}

/* MECHANISM: The 0x18 ra-only frame and seed CFG stay intact, except the masked
   local jump is restored as the second noreturn func_80017284 edge. LEAD-28
   sinks both pinned $v1 values into the tail-j slots; a seam fence plus held
   $v0 page base preserves the nop/lui/addiu split for D_8001DE58. */
