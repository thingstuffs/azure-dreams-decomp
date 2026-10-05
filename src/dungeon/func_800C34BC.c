#include "common.h"

typedef struct State {
    u8 pad[3];
    u8 divisor;
} State;

extern s32 func_800A48F0(State *, s32, s8);
extern s32 func_800A6D30(void);
extern s32 func_800C838C(State *);


s32 func_800C8C1C(State *state_ptr, s16 limit_input, s8 byte_input) {
    State *state = state_ptr;
    s16 limit = limit_input;
    s8 byte_value = byte_input;
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
        s32 signed_limit;

        result = (s32)limit << 16;
        signed_limit = result >> 16;
        result = dispatch_v1 < signed_limit;
        if (result == 0) {
            result = 0xFF;
            if (signed_limit != result) {
                goto failure;
            }
        }
        dispatch_v1 =
            (s32)((u32)func_800A48F0(state, 3, byte_value) << 16);
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
