#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern u8 D_80026BE4[16];
extern u8 D_800E3D20[16];


typedef struct S_81984D4C_1 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81984D4C_1;   /* timer in func_81984D4C */

typedef struct S_81984D4C_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81984D4C_2;   /* temp_v1 in func_81984D4C */

typedef struct S_81984D4C_3 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81984D4C_3;   /* flag in func_81984D4C */

typedef struct S_81984D4C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_81984D4C_4;   /* (*(void **)((u8 *)arg0 + 0xC)) in func_81984D4C */

/* Advances timers and smooths shared state toward the tracked target. */
void func_81984D4C(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    S_81984D4C_2 *target;
    GameView *state;
    u8 *timer;
    u8 *z_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    state = &gameWork.view;
    if (blend_ticks > 0) {
        state->unk_098 = (u16) ((u16)state->unk_098) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26)) - state->unk_098) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    timer = D_800E3D20;
    if (((S_81984D4C_1 *)timer)->unk_00.u != 0) {
        ((S_81984D4C_1 *)timer)->unk_00.s = (s8) (((S_81984D4C_1 *)timer)->unk_00.u - 1);
    }
    target = (*(void * volatile *)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((S_81984D4C_4 *)((*(void **)((u8 *)tracker + 0xC))))->unk_02;
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target->unk_0A;
    state->unk_0A4 = (u16) ((u16)state->unk_0A4) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4)) - state->unk_0A4) >> 2);
    state->unk_0A6 = (u16) ((u16)state->unk_0A6) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6)) - state->unk_0A6) >> 2);
    z_pending = D_80026BE4;
    if (((S_81984D4C_3 *)z_pending)->unk_00.u != 0) {
        state->unk_0A8 = (u16) ((u16)state->unk_0A8) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8)) - state->unk_0A8) >> 2);
    }
    ((S_81984D4C_3 *)z_pending)->unk_00.s = (s8) (state->unk_0A8 != (s16) (*(u16 *)((u8 *)tracker + 8)));
    state->unk_094 = (u16) ((s32) (((u16)state->unk_094) << 0x10) >> 0x12);
    state->unk_096 = (u16) ((s32) (((u16)state->unk_096) << 0x10) >> 0x12);
}

/* MECHANISM: Frameless leaf; tracker stays in a1 and D_80083178 in a2 across the CFG.
   A volatile cached read of tracker+0xC prevents CSE with the direct first-use load,
   producing retail's paired lw v0/v1 and keeping v1 live for offsets 6/0xA. */
