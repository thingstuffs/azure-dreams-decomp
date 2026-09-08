#include "common.h"

extern s32 func_80042900(void *, s8);

extern s32 D_800DCF08[];
extern s32 D_800DCF3C;
extern s32 D_800DCF44;
extern s32 D_800DCF48;

/* Selects a value from object flags and the highest matching state index. */
s32 func_800A652C(void *object) {
    s32 state_result;
    s32 state_index;
    s32 special_index;
    s32 selected_value;

    if (*(u8 *)((u8 *)object + 0x13) == 0) {
        state_index = 14;
        goto init_loop;
    }
    if (*(u8 *)((u8 *)object + 0x25) == 0) {
        selected_value = D_800DCF44;
        goto done;
    }
    state_index = 14;
    if (*(s32 *)((u8 *)object + 0x1C) & 0x20000) {
        goto init_loop;
    }
    selected_value = D_800DCF3C;
    goto done;

return_special:
    selected_value = D_800DCF48;
    goto done;

return_indexed:
    selected_value = D_800DCF08[state_index];
    goto done;

init_loop:
    special_index = 7;
loop:
    state_result = (s16)func_80042900(object, state_index);
    if (state_result > 0) {
        if (state_index == special_index) {
            goto return_special;
        }
    }
    if (state_result != 0) {
        goto return_indexed;
    }
    state_index--;
    if (state_index >= 0) {
        goto loop;
    }
    selected_value = D_800DCF08[0];

done:
    return selected_value;
}

