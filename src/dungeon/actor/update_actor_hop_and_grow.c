#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"
#include "sdk/libgte.h"





extern s16 system_update_flags[8];

/* Advance movement to the target tile, updating height and scale until complete. */
s32 update_actor_hop_and_grow(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *params, ActorRecord *extra) {
    s32 phase;
    s32 current_y;
    s32 height_offset;
    s32 current_x;
    s32 move_frames;
    u16 scale;
    s16 frames_left;

    phase = state->action_phase;
    switch (phase) {
    case 0:
        state->action_timer = 0x10;
        extra->flags1C &= 0xFFFBFFFF;
        if ((*system_update_flags & 2) != 0) {
            set_record_integer_tile_center(motion, params->tile_x, params->tile_y);
            params->scale_x = 0x1000;
            params->scale_y = 0x1000;
            state->action_phase = 2;
        } else {
            state->action_phase = (u8) (state->action_phase + 1);
            extra->unk_8A = 0x800 / state->action_timer;
        }
        return 0;

    case 1:
        if ((state->action_timer + 2) >= 0x10) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        } else {
            move_frames = state->action_timer - 2;
            if (move_frames > 0) {
                current_y = motion->y.w.i;
                current_y -= 0x20;
                motion->velocity_x = (((params->tile_x << 6) - (current_x = motion->x.w.i - 0x20)) << 16) / move_frames;
                motion->velocity_y = (((params->tile_y << 6) - current_y) << 16) / (state->action_timer - 2);
            } else {
                motion->velocity_y = 0;
                motion->velocity_x = 0;
                set_record_integer_tile_center(motion, params->tile_x, params->tile_y);
            }
        }
        if (state->action_timer != 0) {
            motion->velocity_z = ((-(rsin(state->action_timer << 6) >> 4) - (height_offset = state->unk_90.parts.high + 0x20))
                << 16) / state->action_timer;
        }
        scale = params->scale_x + extra->unk_8A;
        params->scale_x = scale;
        params->scale_y = scale;
        frames_left = state->action_timer - 1;
        state->action_timer = frames_left;
        if ((s16) frames_left < 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, params->tile_x, params->tile_y);
            state->unk_90.parts.high = -0x20;
            state->action_phase = (u8) (state->action_phase + 1);
        }
        return 0;

    case 2:
        return 1;

    default:
        return 0;
    }
}
