#include "engine/window/model_prefix.h"
#include "common.h"

#include "engine/window.h"

typedef struct S_8003571C_0 {
    WindowModelPrefix * unk_00;
    u8 pad_04[0x64];
    void (*unk_68)(struct S_80035760_0 *);
} S_8003571C_0;   /* arg0 in step_window_value_down_to_zero */



/* Decreases the state field at offset 0x08 by 0xA0, clamping below zero and advancing the handler. */
void step_window_value_down_to_zero(S_8003571C_0 *object) {
    WindowModelPrefix *state;
    WindowModelPrefix *updated_state;

    state = object->unk_00;
    state->unk_08 = (u16) (state->unk_08 - 0xA0);
    updated_state = object->unk_00;
    if ((s16) updated_state->unk_08 < 0) {
        updated_state->unk_08 = 0U;
        object->unk_68 = &runtime_reset_state_and_advance_callback;
    }
}
