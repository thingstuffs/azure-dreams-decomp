#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C8484(void);

#ifdef NON_MATCHING
static volatile s32 dispatch_v1;
#else
register s32 dispatch_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

s32 func_800C8980(State *state, s32 value, s8 arg2) {
    s32 result;
    register s32 dividend ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (func_800C8484() != 0) {
        result = 0;
        goto done;
    }
    dividend = func_800A6D30() & 0xFFFF;
    dispatch_v1 = state->divisor;
    if (dispatch_v1 != 0) {
        s32 divreg;

        divreg = dispatch_v1;
        ASM_KEEP(divreg);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        dispatch_v1 = dividend % divreg;
        goto check;
    }
    dispatch_v1 = 0;
check:
    if (dispatch_v1 < (s16)value || (s16)value == 255) {
        dispatch_v1 = (s32)((u32)func_800A48F0(state, 4, arg2) << 16);
        result = 1;
        if (dispatch_v1 >= 0) {
            goto done;
        }
    }
    result = 0;
done:
    return result;
}
