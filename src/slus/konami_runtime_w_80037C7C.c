#include "common.h"

#include "common.h"

typedef struct Func80037C7CState {
    s32 *field00;
    u8 pad04[0x08];
    s16 field0C;
    u8 pad0E[0x02];
    u16 field10;
    u8 pad12[0x06];
    u16 field18;
    u8 pad1A[0x0A];
    s16 field24;
    u8 pad26[0x02];
    s16 field28;
    u8 pad2A[0x02];
    u16 field2C;
    u8 pad2E[0x06];
    u16 field34;
    u8 pad36[0x0A];
    s16 field40;
} Func80037C7CState;

/* Update paired offsets and clamped extents from the input offset. */
void func_80037C7C(Func80037C7CState *state, s32 offset) {
    s16 signed_offset = (s16)offset;
    s32 input_offset = offset;

    state->field00[4] = signed_offset;
    if (signed_offset >= 0x37) {
        state->field0C = -0x38;
        state->field10 = 0x30;
    } else {
        state->field0C = -input_offset - 2;
        state->field10 = input_offset - 6;
        if ((s16)state->field10 <= 0) {
            state->field10 = 1;
        }
    }

    if ((s16)input_offset < 0x36) {
        state->field24 = -input_offset + 0x36;
    } else {
        state->field24 = 0;
    }

    offset = -input_offset;
    state->field18 = state->field10;
    state->field28 = offset - 3;
    state->field2C = input_offset + 6;
    if ((s16)state->field2C <= 0) {
        state->field2C = 1;
    }
    if ((s16)input_offset < 0x40) {
        state->field40 = offset + 0x40;
    } else {
        state->field40 = 0;
    }
    state->field34 = state->field2C;
}
