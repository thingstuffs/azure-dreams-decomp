typedef signed char s8;
typedef int s32;

typedef s32 Callback(s32);

extern void *D_80016000;

/* Calls the callback with zero, then maps states 0, 1, and 2 to output values 1, 2, and 3. */
void func_80614A10(void)
{
    void *state_check_one;
    void *state_check_zero;
    void *state_check_two;

    (*(Callback **)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x244))(0);
    *(s32 *)((s8 *)*(void **)((s8 *)D_80016000 + 0x1C) + 0x38) = 0;
    state_check_zero = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)state_check_zero == 0) {
        *(s32 *)((s8 *)state_check_zero + 0x38) = 1;
    }
    state_check_two = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)state_check_two == 2) {
        *(s32 *)((s8 *)state_check_two + 0x38) = 3;
    }
    state_check_one = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)state_check_one == 1) {
        *(s32 *)((s8 *)state_check_one + 0x38) = 2;
    }
}
