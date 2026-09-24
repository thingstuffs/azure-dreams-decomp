#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C838C(State *);

#ifdef NON_MATCHING
static volatile s32 dispatch_v1;
#else
#endif

s32 func_800C8C1C(State *arg0, s16 arg1, s8 arg2_in) {
    State *state = arg0;
    s16 value = arg1;
    s8 arg2 = arg2_in;
    s32 result;
    s32 dividend;
    s32 dispatch_v1;

    if (func_800C838C(state) != 0) {
        result = 0;
        return result;
    }
    dividend = func_800A6D30() & 0xFFFF;
    if (state->divisor != 0) {
        dispatch_v1 = dividend % state->divisor;
    } else {
        dispatch_v1 = 0;
    }
    {
        s32 signed_value;

        result = (s32)value << 16;
        signed_value = result >> 16;
        result = dispatch_v1 < signed_value;
        if (result != 0) {
            goto call;
        }
        result = 0xFF;
        if (signed_value != result) {
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
