#include "common.h"

s32 func_800644B8();                             /* extern */

typedef struct S_800A6B70_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6B70_0;   /* arg0 in update_sine_pulse_color */

typedef struct S_800A6B70_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800A6B70_1;   /* arg2 in update_sine_pulse_color */

/* Advances the phase and sets all three color channels to the same intensity. */
void update_sine_pulse_color(S_800A6B70_0 *phase_state, s32 unused, S_800A6B70_1 *color) {
    s32 phase;
    s8 intensity;

    phase = phase_state->unk_0C + 1;
    phase_state->unk_0C = phase;
    intensity = (func_800644B8(phase << 6) >> 7) + 0x60;
    color->unk_0E = intensity;
    color->unk_0D = intensity;
    color->unk_0C = intensity;
}
