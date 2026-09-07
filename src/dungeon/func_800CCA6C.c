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

void func_800D21CC(CcaState *state, CcaMotion *motion, CcaInfo *info, CcaAnim *anim) {
    s32 status;

    status = state->status;
    if (status == 1) {
        goto update;
    }
    if (status < 2) {
        if (status == 0) {
            goto start;
        }
        goto done;
    }
    if (status == 2) {
        goto state2;
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
        goto update;
    }
    motion->dz = 0;
    motion->dy = 0;
    motion->dx = 0;
    func_800AAA54(state, motion, info, 0);
    goto done;

update:
    {
        s32 dx;
        s32 dx_adjusted;
        s32 dy;
        s32 dy_adjusted;
        u16 count;

        dx = motion->dx;
        dx_adjusted = dx;
        if (dx < 0) {
            dx_adjusted = dx + 3;
        }
        motion->dx = dx - (dx_adjusted >> 2);
        dy = motion->dy;
        dy_adjusted = dy;
        if (dy < 0) {
            dy_adjusted = dy + 3;
        }
        motion->dy = dy - (dy_adjusted >> 2);
        count = state->count - 1;
        state->count = count;
        if ((s32)(count << 16) > 0) {
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

state2:
    {
        s16 count;
        u16 next_count;

        count = state->count;
        if (count != 0) {
            s32 x;
            s32 y;

            motion->dx = (s32)(((((s32)info->x << 6) - (x = motion->x - 0x20)) << 15) / count);
            y = motion->y - 0x20;
            motion->dy = (s32)(((((s32)info->y << 6) - y) << 15) / state->count);
        }
        next_count = state->count - 1;
        state->count = next_count;
        if ((s32)(next_count << 16) > 0) {
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
