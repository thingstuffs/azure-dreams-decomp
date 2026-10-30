#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "sdk/libgte.h"
#include "town/minigame.h"



typedef struct S_800220A8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800220A8_2;   /* motion_state->owner in update_minigame_approach_motion */

/* Update motion through approach, oscillation, and withdrawal, flagging completion. */
void update_minigame_approach_motion(ApproachMotionObject *motion_state, ObjectPosition *motion) {
    s16 state;

    if (((S_800220A8_2 *)(motion_state->owner))->unk_18 == 2) {
        motion_state->state = 3;
    }
    state = motion_state->state;
    switch (state) {
    case 0:
        if ((motion->z.v += 0x100000) < (s32)0xFF900000) {
            return;
        }
        motion_state->phase = 0;
        motion->velocity_z = -0x40000;
        motion_state->state = 1;
        return;
    case 1:
        motion->z.v += motion->velocity_z;
        motion->velocity_z += 0x4000;
        if (motion->velocity_z != 0x40000) {
            return;
        }
        motion_state->state = 2;
        return;
    case 2:
        motion->z.v += motion->velocity_z;
        motion->velocity_z -= 0x8000;
        if (motion->velocity_z != -0x40000) {
            return;
        }
        motion_state->state = 1;
        return;
    case 0xF0: {
        u16 phase;
        s32 position;
        phase = (motion_state->phase + 1) & 0x7F;
        motion_state->phase = phase;
        motion->z.v = (rsin(phase << 6) << 7) - 0x700000;
        return;
    }
    case 3: {
        s32 position;
        position = motion->z.v;
        position += (s32)0xFFF00000;
        motion->z.v = position;
        if ((s32)0xFE000000 < position) {
            return;
        }
        (*(u16 *)((u8 *)motion_state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    }
}
