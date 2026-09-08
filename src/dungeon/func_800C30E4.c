#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C7FFC(void);

#ifdef NON_MATCHING
static volatile s32 dispatch_v1;
#else
register s32 dispatch_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

s32 func_800C8844(State *arg0, s16 arg1, s8 arg2_in) {
    State *state = arg0;
    register s16 value ASM_REG("$17") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s8 arg2 ASM_REG("$18") = arg2_in;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 result;
    s32 dividend;

    if (func_800C7FFC() != 0) {
        result = 0;
        goto done;
    }
    dividend = func_800A6D30() & 0xFFFF;
    dispatch_v1 = state->divisor;
    if (dispatch_v1 != 0) {
        register s32 divreg ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        divreg = dispatch_v1;
        ASM_KEEP(divreg);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        dispatch_v1 = dividend % divreg;
    } else {
        dispatch_v1 = 0;
    }
    {
        register s32 shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 signed_value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

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
