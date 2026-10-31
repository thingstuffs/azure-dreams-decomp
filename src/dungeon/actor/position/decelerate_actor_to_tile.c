#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"

typedef struct {
    u8 pad_00[0x8C];
    void *next;
    u8 pad_90[6];
    s16 count;
    u8 pad_98[2];
    s8 kind;
    u8 status;
} CcaState;

typedef struct {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[4];
    s32 dx;
    s32 dy;
    s32 dz;
} CcaMotion;

typedef struct {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0x0E];
    u8 x;
    u8 y;
} CcaInfo;

typedef struct {
    u8 pad_00[0x28];
    u8 active;
    u8 pad_29[0x41];
    u16 code;
} CcaAnim;

extern u8 D_800D20D8[];

/* Decelerate motion, then align to the target tile and advance the state. */
void decelerate_actor_to_tile(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *info, ActorRecord *anim) {
    s32 phase;

    phase = state->action_phase.u;
    switch (phase) {
    case 0:
        apply_clamped_actor_value_delta(anim);
        motion->velocity_x = (s32)(*(s16 *)((u8 *)dir_step_x + ((anim->movement_facing >> 8) & 0xE)) << 15);
        motion->velocity_y = (s32)(*(s16 *)((u8 *)dir_step_y + ((anim->movement_facing >> 8) & 0xE)) << 15);
        state->action_phase.u = state->action_phase.u + 1;
        if (anim->hp != 0) {
            if (info->flags & 0x8000) {
                state->action_timer.s = 0;
                state->action_phase.u = 2;
                return;
            }
            state->action_timer.s = 8;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(state, motion, info, 0);
            return;
        }
                /* fall through */
    case 1:
    {
        s32 velocity_x;
        s32 biased_dx;
        s32 velocity_y;
        s32 biased_dy;
        u16 frames_left;

        velocity_x = motion->velocity_x;
        biased_dx = velocity_x;
        motion->velocity_x = velocity_x - (biased_dx / 4);
        velocity_y = motion->velocity_y;
        biased_dy = velocity_y;
        motion->velocity_y = velocity_y - (biased_dy / 4);
        frames_left = state->action_timer.s - 1;
        state->action_timer.s = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            return;
        }
        if (anim->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(state, motion, info, 0);
            return;
        }
        state->action_timer.s = 8;
        state->action_phase.u = state->action_phase.u + 1;
        return;
    }

    case 2:
    {
        s16 frames_left;
        u16 next_frames;

        frames_left = state->action_timer.s;
        if (frames_left != 0) {
            s32 origin_x;
            s32 origin_y;

            motion->velocity_x = (s32)(((((s32)info->tile_x << 6) - (origin_x = motion->x.w.i - 0x20)) << 15) / frames_left);
            origin_y = motion->y.w.i - 0x20;
            motion->velocity_y = (s32)(((((s32)info->tile_y << 6) - origin_y) << 15) / state->action_timer.s);
        }
        next_frames = state->action_timer.s - 1;
        state->action_timer.s = next_frames;
        if ((s32)(next_frames << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, info->tile_x, info->tile_y);
        if ((g_dungeon_status.pending_display_owner) == (u8 *)anim - 0x20) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        state->unk_8C.address = D_800D20D8;
        state->action_id.s = 0xE;
    }
    }

    return;
}
