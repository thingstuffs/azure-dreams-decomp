#include "common.h"

extern void func_800A9A0C(void *);
extern void func_800AAA54(s32, s32, s32, s32);
extern void func_800AA6B4(s32, s32, s32, s32);
extern void *D_80083470;

/* Processes active status, counts completed transitions, and dispatches follow-up work. */
void func_800D20D8(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state) {
    s16 previous_status;

    if ((s8)state[0x6D] > 0) {
        previous_status = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        func_800A9A0C(state);
        if (previous_status != 0 && *(s8 *)(state + 0x6D) == 0) {
            state[0x28]--;
        }
        if (state[0x28] == 0) {
            D_80083470 = state - 0x20;
            func_800AAA54(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        func_800AA6B4(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
    }
}
