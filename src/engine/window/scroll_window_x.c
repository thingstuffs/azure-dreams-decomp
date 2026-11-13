#include "engine/window/model_prefix.h"
#include "common.h"

#include "engine/window.h"
#include "slus/data.h"




typedef struct S_8003566C_0 {
    WindowModelPrefix * unk_00;
    u8 pad_04[0x49];
    s8 unk_4D;
    u8 pad_4E[0x1A];
    void (*unk_68)(struct S_8003571C_0 *);
    u8 pad_6C[0x8];
    s32 unk_74;
} S_8003566C_0;   /* arg0 in scroll_window_x */

/* Decrease the stored value, clamp negatives to zero, and advance state below 0x100. */
void scroll_window_x(S_8003566C_0 *state) {
    WindowModelPrefix *value_data;
    WindowModelPrefix *clamp_data;

    value_data = state->unk_00;
    value_data->unk_08 = (u16) (value_data->unk_08 - 0xA0);
    clamp_data = state->unk_00;
    if ((s16) clamp_data->unk_08 < 0) {
        clamp_data->unk_08 = 0U;
    }
    if ((s16) state->unk_00->unk_08 < 0x100) {
        create_window_overlay_object(&scrolling_window_node_storage, &scrolling_window_display_storage, &message_window_object_template, state, 1, state->unk_74);
        state->unk_4D = 0;
        state->unk_68 = &step_window_value_down_to_zero;
    }
}
