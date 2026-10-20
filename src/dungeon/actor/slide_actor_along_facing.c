#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct {
    u8 pad_00[0x8C];
    void *next;
    u8 pad_90[6];
    s16 count;
    u8 pad_98[2];
    s8 kind;
    u8 status;
} CcaState_800D29D8;

typedef struct {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[4];
    s32 dx;
    s32 dy;
    s32 dz;
} CcaMotion_800D29D8;

typedef struct {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0x0E];
    u8 x;
    u8 y;
} CcaInfo_800D29D8;

typedef struct {
    u8 pad_00[0x28];
    u8 active;
    u8 pad_29[0x41];
    u16 code;
} CcaAnim_800D29D8;

extern void advance_actor_status_turn(s32, s32, s32, u8 *);

extern void set_record_integer_tile_center(CcaMotion_800D29D8 *, u8, u8);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(CcaAnim_800D29D8 *);

/* Decelerate motion, then align to the target tile and advance the state. */
void slide_actor_along_facing(CcaState_800D29D8 *state, CcaMotion_800D29D8 *motion, CcaInfo_800D29D8 *info, CcaAnim_800D29D8 *anim) {
    s32 phase;

    phase = state->status;
    switch (phase) {
    case 0:
        apply_clamped_actor_value_delta(anim);
        motion->dx = (s32)(*(s16 *)((u8 *)dir_step_x + ((anim->code >> 8) & 0xE)) << 15);
        motion->dy = (s32)(*(s16 *)((u8 *)dir_step_y + ((anim->code >> 8) & 0xE)) << 15);
        state->status = state->status + 1;
        if (anim->active != 0) {
            if (info->flags & 0x8000) {
                state->count = 0;
                state->status = 2;
                return;
            }
            state->count = 8;
        } else {
            motion->dz = 0;
            motion->dy = 0;
            motion->dx = 0;
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

        velocity_x = motion->dx;
        biased_dx = velocity_x;
        motion->dx = velocity_x - (biased_dx / 4);
        velocity_y = motion->dy;
        biased_dy = velocity_y;
        motion->dy = velocity_y - (biased_dy / 4);
        frames_left = state->count - 1;
        state->count = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            return;
        }
        if (anim->active == 0) {
            motion->dz = 0;
            motion->dy = 0;
            motion->dx = 0;
            begin_actor_display_action(state, motion, info, 0);
            return;
        }
        state->count = 8;
        state->status = state->status + 1;
        return;
    }

    case 2:
    {
        s16 frames_left;
        u16 next_frames;

        frames_left = state->count;
        if (frames_left != 0) {
            s32 origin_x;
            s32 origin_y;

            motion->dx = (s32)(((((s32)info->x << 6) - (origin_x = motion->x - 0x20)) << 15) / frames_left);
            origin_y = motion->y - 0x20;
            motion->dy = (s32)(((((s32)info->y << 6) - origin_y) << 15) / state->count);
        }
        next_frames = state->count - 1;
        state->count = next_frames;
        if ((s32)(next_frames << 16) > 0) {
            return;
        }
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        set_record_integer_tile_center(motion, info->x, info->y);
        if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)anim - 0x20)) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        state->next = advance_actor_status_turn;
        state->kind = 0xE;
    }
    }

    return;
}
