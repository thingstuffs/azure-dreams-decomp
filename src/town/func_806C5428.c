#include "common.h"

typedef s32 Callback(s32);

extern void *D_80016000;

/* Calls the callback with zero, then maps states 0-2 to results 1-3, defaulting to zero. */
void func_80016428(void)
{
    void *state_one;
    void *state_two;
    void *state_zero;

    (*(Callback **)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x244))(0);
    *(s32 *)((s8 *)*(void **)((s8 *)D_80016000 + 0x1C) + 0x38) = 0;
    state_zero = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)state_zero == 0) {
        *(s32 *)((s8 *)state_zero + 0x38) = 1;
    }
    state_one = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)state_one == 1) {
        *(s32 *)((s8 *)state_one + 0x38) = 2;
    }
    state_two = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)state_two == 2) {
        *(s32 *)((s8 *)state_two + 0x38) = 3;
    }
}
