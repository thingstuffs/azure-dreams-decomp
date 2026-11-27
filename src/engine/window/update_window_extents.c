#include "common.h"

#include "engine/window.h"

typedef struct Func80037C7CState {
    s32 *owner;
    u8 pad04[0x08];
    s16 textured_x;
    u8 pad0E[0x02];
    u16 textured_width;
    u8 pad12[0x06];
    u16 tex_width;
    u8 pad1A[0x0A];
    s16 tex_x;
    u8 pad26[0x02];
    s16 solid_x;
    u8 pad2A[0x02];
    u16 solid_width;
    u8 pad2E[0x06];
    u16 secondary_tex_width;
    u8 pad36[0x0A];
    s16 secondary_tex_x;
} Func80037C7CState;

/* Update paired offsets and clamped extents from the input offset. */
void update_window_extents(Func80037C7CState *state, s32 offset) {
    s16 signed_offset = (s16)offset;
    s32 input_offset = offset;

    state->owner[4] = signed_offset;
    if (signed_offset >= 0x37) {
        state->textured_x = -0x38;
        state->textured_width = 0x30;
    } else {
        state->textured_x = -input_offset - 2;
        state->textured_width = input_offset - 6;
        if ((s16)state->textured_width <= 0) {
            state->textured_width = 1;
        }
    }

    if ((s16)input_offset < 0x36) {
        state->tex_x = -input_offset + 0x36;
    } else {
        state->tex_x = 0;
    }

    offset = -input_offset;
    state->tex_width = state->textured_width;
    state->solid_x = offset - 3;
    state->solid_width = input_offset + 6;
    if ((s16)state->solid_width <= 0) {
        state->solid_width = 1;
    }
    if ((s16)input_offset < 0x40) {
        state->secondary_tex_x = offset + 0x40;
    } else {
        state->secondary_tex_x = 0;
    }
    state->secondary_tex_width = state->solid_width;
}
