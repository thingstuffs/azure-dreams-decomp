#include "common.h"

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

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_80083460[];
extern u8 D_800D20D8[];

extern void func_800A2B04(CcaMotion *, u8, u8);
extern void func_800AAA54(CcaState *, CcaMotion *, CcaInfo *, s32);
extern void func_800AD4D0(CcaAnim *);

/* Decelerate motion, then align to the target tile and advance the state. */
void func_800D21CC(CcaState *state, CcaMotion *motion, CcaInfo *info, CcaAnim *anim) {
    s32 phase;

    phase = state->status;
    if (phase == 1) {
        goto decelerate;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto start;
        }
        goto done;
    }
    if (phase == 2) {
        goto align_to_tile;
    }
    goto done;

start:
    func_800AD4D0(anim);
    motion->dx = (s32)(*(s16 *)((u8 *)D_8006CCD8 + ((anim->code >> 8) & 0xE)) << 15);
    motion->dy = (s32)(*(s16 *)((u8 *)D_8006CCE8 + ((anim->code >> 8) & 0xE)) << 15);
    state->status = state->status + 1;
    if (anim->active != 0) {
        if (info->flags & 0x8000) {
            state->count = 0;
            state->status = 2;
            goto done;
        }
        state->count = 8;
        goto decelerate;
    }
    motion->dz = 0;
    motion->dy = 0;
    motion->dx = 0;
    func_800AAA54(state, motion, info, 0);
    goto done;

decelerate:
    {
        s32 velocity_x;
        s32 biased_dx;
        s32 velocity_y;
        s32 biased_dy;
        u16 frames_left;

        velocity_x = motion->dx;
        biased_dx = velocity_x;
        if (velocity_x < 0) {
            biased_dx = velocity_x + 3;
        }
        motion->dx = velocity_x - (biased_dx >> 2);
        velocity_y = motion->dy;
        biased_dy = velocity_y;
        if (velocity_y < 0) {
            biased_dy = velocity_y + 3;
        }
        motion->dy = velocity_y - (biased_dy >> 2);
        frames_left = state->count - 1;
        state->count = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            goto done;
        }
        if (anim->active == 0) {
            motion->dz = 0;
            motion->dy = 0;
            motion->dx = 0;
            func_800AAA54(state, motion, info, 0);
            goto done;
        }
        state->count = 8;
        state->status = state->status + 1;
        goto done;
    }

align_to_tile:
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
            goto done;
        }
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, info->x, info->y);
        if (D_80083460[4] == (s32)((u8 *)anim - 0x20)) {
            D_80083460[4] &= 0x7FFFFFFF;
        }
        state->next = D_800D20D8;
        state->kind = 0xE;
    }

done:
    return;
}
