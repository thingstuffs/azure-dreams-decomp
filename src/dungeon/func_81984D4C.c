#include "modules/dungeon_ovl_19a332c.h"

void dungeonClearObjectBufferAndState(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    ovl_19a332c_81984D4C_S_81984D4C_2 *target;
    GameView *state;
    u8 *timer;
    u8 *z_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    state = &gameWork.view;
    if (blend_ticks > 0) {
        state->unk_098 = (u16) ((u16)state->unk_098) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26))
            - state->unk_098) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    timer = D_800E3D20;
    if (((ovl_19a332c_81984D4C_S_81984D4C_1 *)timer)->unk_00.u != 0) {
        ((ovl_19a332c_81984D4C_S_81984D4C_1 *)timer)->unk_00.s = (s8) (((ovl_19a332c_81984D4C_S_81984D4C_1 *)timer)->unk_00.u - 1);
    }
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((ovl_19a332c_81984D4C_S_81984D4C_4 *)((*(void **)((u8 *)tracker + 0xC))))->unk_02;
    target = (*(void **)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target->unk_0A;
    state->unk_0A4 = (u16) ((u16)state->unk_0A4) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4)) - state->unk_0A4) >> 2);
    state->unk_0A6 = (u16) ((u16)state->unk_0A6) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6)) - state->unk_0A6) >> 2);
    z_pending = D_80026BE4;
    if (((ovl_19a332c_81984D4C_S_81984D4C_3 *)z_pending)->unk_00.u != 0) {
        state->unk_0A8 = (u16) ((u16)state->unk_0A8) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8)) - state->unk_0A8)
            >> 2);
    }
    ((ovl_19a332c_81984D4C_S_81984D4C_3 *)z_pending)->unk_00.s = (s8) (state->unk_0A8 != (s16) (*(u16 *)((u8 *)tracker + 8)));
    state->unk_094 = (u16) ((s32) (((u16)state->unk_094) << 0x10) >> 0x12);
    state->unk_096 = (u16) ((s32) (((u16)state->unk_096) << 0x10) >> 0x12);
}

/* MECHANISM: Frameless leaf; tracker stays in a1 and D_80083178 in a2 across the CFG.
   The tracker+0xC pointer is read a second time, after the first-use load and the store to
   tracker+4: the u16 store invalidates the earlier read (cse invalidate_memory), giving retail's
   paired lw v0/v1 and keeping v1 live for offsets 6/0xA. */
