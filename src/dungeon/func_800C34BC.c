#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C838C(void);

#ifdef NON_MATCHING
static volatile s32 dispatch_v1;
#else
register s32 dispatch_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif

s32 func_800C8C1C(State *arg0, s16 arg1, s8 arg2_in) {
    State *state = arg0;
    register s16 value ASM_REG("$17") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    s8 arg2 = arg2_in;
    s32 result;
    s32 dividend;

    if (func_800C838C() != 0) {
        result = 0;
        goto done;
    }
    dividend = func_800A6D30() & 0xFFFF;
    dispatch_v1 = state->divisor;
    {
        register s32 shifted ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register s32 signed_value ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        if (dispatch_v1 != 0) {
            register s32 divreg ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

            divreg = dispatch_v1;
            ASM_KEEP(divreg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            dispatch_v1 = dividend % divreg;
            shifted = (s32)value << 16;
            goto join;
        }
        dispatch_v1 = 0;
        shifted = (s32)value << 16;
join:
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
            (s32)((u32)func_800A48F0(state, 3, arg2) << 16);
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
