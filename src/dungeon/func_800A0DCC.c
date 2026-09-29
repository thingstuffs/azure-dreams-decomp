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

    if (*(u8 *)((u8 *)object + 0x13) != 0) {
        if (*(u8 *)((u8 *)object + 0x25) == 0) {
            selected_value = D_800DCF44;
            return selected_value;
        }
        if (!(*(s32 *)((u8 *)object + 0x1C) & 0x20000)) {
            selected_value = D_800DCF3C;
            return selected_value;
        }
    }
    state_index = 14;
    special_index = 7;
    for (; state_index >= 0; state_index--) {
        state_result = (s16)func_80042900(object, state_index);
        if (state_result > 0) {
            if (state_index == special_index) {
                selected_value = D_800DCF48;
                return selected_value;
            }
        }
        if (state_result != 0) {
            selected_value = D_800DCF08[state_index];
            return selected_value;
        }
    }
    selected_value = D_800DCF08[0];

    return selected_value;
}
