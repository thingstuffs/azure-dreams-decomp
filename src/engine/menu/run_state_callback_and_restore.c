#include "common.h"

extern s32 call_state_callback(void *a0);
extern void func_80050EA8(void *a0);

/* Checks sub-state, restores the saved callback and cleans up on a nonzero result, then returns the result. */
s32 run_state_callback_and_restore(void *state)
{
    s32 check_result = call_state_callback(state);

    if (check_result != 0) {
        *(s32 *)((u8 *)state - 0x10) = *(s32 *)((u8 *)state + 0x4);
        func_80050EA8((u8 *)state - 0x20);
    }
    return check_result;
}
