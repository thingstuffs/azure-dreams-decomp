#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"

typedef struct ActorHopState {
    u8 pad0[0x92];
    s16 field92;
    u8 pad94[2];
    s16 field96;
    u8 pad98[3];
    u8 field9B;
} State;

typedef struct ActorHopMotion {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[4];
    s32 fieldC;
    s32 field10;
    s32 field14;
} Motion;

typedef struct ActorHopParams {
    u8 pad0[0x1C];
    u16 field1C;
    u16 field1E;
    u8 pad20[4];
    u8 field24;
    u8 field25;
} Params;

typedef struct ActorHopExtra {
    u8 pad0[0x1C];
    s32 field1C;
    u8 pad20[0x6A];
    u16 field8A;
} Extra;

extern s16 system_update_flags[8];
extern s32 rsin(s32);

/* Advance movement to the target tile, updating height and scale until complete. */
s32 update_actor_hop_and_grow(State *state, ObjectPosition *motion, SpriteFrameState *params, ActorRecord *extra) {
    s32 phase;
    s32 current_y;
    s32 height_offset;
    s32 current_x;
    s32 move_frames;
    u16 scale;
    s16 frames_left;

    phase = state->field9B;
    switch (phase) {
    case 0:
        state->field96 = 0x10;
        extra->flags1C &= 0xFFFBFFFF;
        if ((*system_update_flags & 2) != 0) {
            set_record_integer_tile_center(motion, params->tile_x, params->tile_y);
            params->scale_x = 0x1000;
            params->scale_y = 0x1000;
            state->field9B = 2;
        } else {
            state->field9B = (u8) (state->field9B + 1);
            extra->unk_8A = 0x800 / state->field96;
        }
        return 0;

    case 1:
        if ((state->field96 + 2) >= 0x10) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        } else {
            move_frames = state->field96 - 2;
            if (move_frames > 0) {
                current_y = motion->y.w.i;
                current_y -= 0x20;
                motion->velocity_x = (((params->tile_x << 6) - (current_x = motion->x.w.i - 0x20)) << 16) / move_frames;
                motion->velocity_y = (((params->tile_y << 6) - current_y) << 16) / (state->field96 - 2);
            } else {
                motion->velocity_y = 0;
                motion->velocity_x = 0;
                set_record_integer_tile_center(motion, params->tile_x, params->tile_y);
            }
        }
        if (state->field96 != 0) {
            motion->velocity_z = ((-(rsin(state->field96 << 6) >> 4) - (height_offset = state->field92 + 0x20))
                << 16) / state->field96;
        }
        scale = params->scale_x + extra->unk_8A;
        params->scale_x = scale;
        params->scale_y = scale;
        frames_left = (u16) state->field96 - 1;
        state->field96 = frames_left;
        if ((s16) frames_left < 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, params->tile_x, params->tile_y);
            state->field92 = -0x20;
            state->field9B = (u8) (state->field9B + 1);
        }
        return 0;

    case 2:
        return 1;

    default:
        return 0;
    }
}
