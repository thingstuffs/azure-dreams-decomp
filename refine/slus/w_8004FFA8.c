#include "common.h"

extern s32 func_8004FF20(void *a0);
extern void func_80050EA8(void *a0);

/* Checks sub-state, restores the saved callback and cleans up on a nonzero result, then returns the result. */
s32 func_8004FFA8(void *state)
{
    s32 check_result = func_8004FF20(state);

    if (check_result != 0) {
        *(s32 *)((u8 *)state - 0x10) = *(s32 *)((u8 *)state + 0x4);
        func_80050EA8((u8 *)state - 0x20);
    }
    return check_result;
}
