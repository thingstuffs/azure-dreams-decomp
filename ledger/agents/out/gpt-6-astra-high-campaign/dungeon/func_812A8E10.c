#include "common.h"

typedef struct { u8 pad0[0x8C]; void *field8c; u8 pad90[6]; s16 count96; u8 pad98[3]; u8 state9b; } S_A;
typedef struct { u8 pad0[2]; s16 x2; u8 pad4[2]; s16 y6; u8 pad8[4]; s32 dxC; s32 dy10; s32 dz14; } S_B;
typedef struct { u8 pad0[0x14]; u16 flags14; u8 pad16[0x0E]; u8 x24; u8 y25; } S_C;
typedef struct { u8 pad0[0x28]; u8 flag28; u8 pad29[0x41]; u16 index6A; } S_D;

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_80083460[3];
extern u8 D_80171FA4[];
extern void func_800A2B04(S_B *, u8, u8);
extern void func_800AD4D0(S_D *);

/* Updates staged motion and snaps to the target tile when the countdown ends. */
void func_80174610(S_A *motion_state, S_B *motion, S_C *target, S_D *actor) {
    s16 ticks_left;
    s32 target_pos;
    s32 current_pos;
    u16 next_count;
    s32 *selection_state;
    s32 active_flag;
    s32 state;

    state = motion_state->state9b;
    active_flag = 1;
    switch (state) {
    case 0:
        goto init_motion;
    case 1:
        goto slow_motion;
    case 2:
        goto reach_target;
    default:
        goto done;
    }

init_motion:
        func_800AD4D0(actor);
        motion_state->state9b = (u8)(motion_state->state9b + 1);
        if (actor->flag28 == 0) {
            actor->flag28 = (u8)active_flag;
        }
        if (target->flags14 & 0x8000) {
            motion_state->count96 = 0;
            motion_state->state9b = 2;
            goto done;
        }
        motion->dxC = (-(*(s16 *)(D_8006CCD8 + (((u16)actor->index6A >> 8) & 0xE)))) << 0xF;
        motion->dy10 = (-(*(s16 *)(D_8006CCE8 + (((u16)actor->index6A >> 8) & 0xE)))) << 0xF;
        motion_state->count96 = 8;
slow_motion:
        motion->dxC += (*(s16 *)(D_8006CCD8 + (((u16)actor->index6A >> 8) & 0xE))) << 0xA;
        motion->dy10 += (*(s16 *)(D_8006CCE8 + (((u16)actor->index6A >> 8) & 0xE))) << 0xA;
        next_count = (u16)motion_state->count96 - 1;
        motion_state->count96 = (s16)next_count;
        if ((next_count << 0x10) <= 0) {
            if (actor->flag28 == 0) {
                actor->flag28 = 1;
            }
            motion_state->count96 = 8;
            motion_state->state9b = (u8)(motion_state->state9b + 1);
            goto done;
        }
        goto done;
reach_target:
        ticks_left = motion_state->count96;
        if (ticks_left != 0) {
            target_pos = (s32)target->x24 << 6;
            current_pos = motion->x2;
            current_pos -= 0x20;
            motion->dxC = ((target_pos - current_pos) << 0xF) / ticks_left;
            target_pos = (s32)target->y25 << 6;
            current_pos = motion->y6;
            current_pos -= 0x20;
            motion->dy10 = ((target_pos - current_pos) << 0xF) / motion_state->count96;
        }
        next_count = (u16)motion_state->count96 - 1;
        motion_state->count96 = (s16)next_count;
        if ((next_count << 0x10) <= 0) {
            motion->dz14 = 0;
            motion->dy10 = 0;
            motion->dxC = 0;
            func_800A2B04(motion, target->x24, target->y25);
            selection_state = D_80083460;
            if (selection_state[4] == (s32)((u8 *)actor - 0x20)) {
                selection_state[4] &= 0x7FFFFFFF;
                motion_state->field8c = D_80171FA4;
            } else {
                motion_state->field8c = D_80171FA4;
            }
        }
        goto done;
done:
    return;
}
