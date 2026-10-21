#include "common.h"

#include "common.h"
#include "engine/camera.h"
#include "engine/util.h"

/* Initializes three-component interpolation state and its update callback. */
void initialize_three_component_interpolation(void *state_data, u16 *target, s32 duration, u16 *values) {
    void *state = state_data;
    s32 delta_z;

    *(s32 *)((s8 *)state + 0x14) = 0;
    *(s32 *)((s8 *)state + 0x1C) = 0;
    if (duration != 0) {
        *(s32 *)((s32)state + 0x18) = 0x400 / duration;
    } else {
        *(s32 *)((s8 *)state + 0x18) = 0x1000;
    }
    if (target != 0) {
        *(u16 *)((s8 *)state + 0xC) = target[0];
        *(u16 *)((s8 *)state + 0xE) = target[1];
        *(u16 *)((s8 *)state + 0x10) = target[2];
        *(s16 *)((s8 *)state + 4) = target[0] - values[0];
        *(s16 *)((s8 *)state + 6) = target[1] - values[1];
        delta_z = target[2] - values[2];
        *(void **)((s8 *)state + 0) = values;
        *(void (**)(void *))((s8 *)state - 4) = runtime_advance_three_component_interpolation;
        *(s16 *)((s8 *)state + 8) = delta_z;
    }
}
