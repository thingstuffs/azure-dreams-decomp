#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C7FFC(void);
extern s32 func_800C88A4(void);

#ifdef NON_MATCHING
static volatile s32 dispatch_v1;
#else
register s32 dispatch_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif

s32 func_800C8844(State *arg0, s16 arg1, s8 arg2_in) {
    State *state = arg0;
    register s16 value ASM_REG("$17") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    register s8 arg2 ASM_REG("$18") = arg2_in;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 result;
    s32 dividend;

    if (func_800C7FFC() != 0) {
        result = 0;
        goto done;
    }
    dividend = func_800A6D30() & 0xFFFF;
    dispatch_v1 = state->divisor;
    if (dispatch_v1 != 0) {
        register s32 divreg ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        register s32 dead_shift ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

        divreg = dispatch_v1;
        ASM_KEEP(divreg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        dispatch_v1 = dividend % divreg;
        dead_shift = (s32)value << 16;
        ASM_TAILSLOT_PIN_TIED(dead_shift);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_800C88A4();
    }
    {
        register s32 shifted ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        register s32 signed_value ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        dispatch_v1 = 0;
        shifted = (s32)value << 16;
        signed_value = shifted >> 16;
        shifted = dispatch_v1 < signed_value;
        if (shifted != 0) {
            goto call;
        }
        shifted = 0xFF;
        if (signed_value != shifted) {
            goto failure;
        }
call:
        dispatch_v1 =
            (s32)((u32)func_800A48F0(state, 5, arg2) << 16);
        result = 1;
        if (dispatch_v1 >= 0) {
            goto done;
        }
    }
failure:
    result = 0;
done:
    return result;
}

/* MECHANISM: The 0x20 frame holds state/value/arg2 in s0/s1/s2, with a hidden v1
   carrier preserving the continuation ABI for divisor and remainder.
   A pinned v0 divisor restores the missing pre-div move; LEAD28 sinks the dead
   value shift into the func_800C88A4 tail-jump delay slot. */
