#include "engine/camera/interpolation.h"
#include "shared/game_work.h"
#include "common.h"

#include "engine/camera.h"
#include "engine/util.h"

/* Initializes three-component interpolation state and its update callback. */
void initialize_three_component_interpolation(void *state_data, u16 *target, s32 duration, u16 *values) {
    CameraInterpolationBody *state = state_data;
    s32 delta_z;

    state->progress = 0;
    state->unk_1C = 0;
    if (duration != 0) {
        state->step = 0x400 / duration;
    } else {
        state->step = 0x1000;
    }
    if (target != 0) {
        state->target[0] = target[0];
        state->target[1] = target[1];
        state->target[2] = target[2];
        state->delta[0].s = target[0] - values[0];
        state->delta[1].s = target[1] - values[1];
        delta_z = target[2] - values[2];
        state->output = values;
        ((ViewSlot *)((u8 *)state - 4))->callback = runtime_advance_three_component_interpolation;
        state->delta[2].s = delta_z;
    }
}
