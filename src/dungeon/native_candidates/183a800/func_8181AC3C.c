#include "modules/dungeon_ovl_183a800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "modules/dungeon_native_abi.h"

/* Effect record: the object header precedes it; velocity is added to position every frame. */


/* Render entry advanced by func_800478B8; only its flags are read here. */



/* Accumulate motion, process the update mode, and mark expired or flagged state. */
void func_8002443C(MotionState *state, s32 *sum, UpdateFlags *flags) {
    s32 update_count;
    s32 more_updates;
    u16 next_tick;

    state->frames_left = state->frames_left - 1;
    state->x = state->x + state->dx;
    state->y = state->y + state->dy;
    state->z = state->z + state->dz;
    sum[0] = sum[0] + state->x;
    sum[1] = sum[1] + state->y;
    D_80025914 = 1;
    sum[2] = sum[2] + state->z;

    switch (state->mode) {
    case 0:
        func_800478B8(flags);
        break;
    case 1:
        if (state->period > 0) {
            update_count = 0;
            do {
                func_800478B8(flags);
                update_count = update_count + 1;
                more_updates = update_count < state->period;
            } while (more_updates);
        }
        break;
    case 2:
        next_tick = state->tick + 1;
        state->tick = next_tick;
        if ((s16) next_tick >= state->period) {
            func_800478B8(flags);
            state->tick = 0;
        }
        break;
    default:
        break;
    }

    if ((s16) state->frames_left <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    if (flags->flags & 0x8000) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
