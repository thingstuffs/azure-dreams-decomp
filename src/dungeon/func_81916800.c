#include "modules/dungeon_ovl_1936800.h"

void interpolate_view_parameters(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    Row_81916800_S_81916800_2 *target_values;
    GameView *blend_state;
    u8 *countdown;
    u8 *third_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    blend_state = &g_game_work.view;
    if (blend_ticks > 0) {
        blend_state->unk_098 = (u16) ((u16)blend_state->unk_098) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26))
            - blend_state->unk_098) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    countdown = ((u8 *)D_800E3D20);
    if (((Row_81916800_S_81916800_1 *)countdown)->unk_00.u != 0) {
        ((Row_81916800_S_81916800_1 *)countdown)->unk_00.s = (s8) (((Row_81916800_S_81916800_1 *)countdown)->unk_00.u - 1);
    }
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((Row_81916800_S_81916800_4 *)(*(void **)((u8 *)tracker + 0xC)))->unk_02;
    target_values = (*(void **)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target_values->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target_values->unk_0A;
    blend_state->unk_0A4 = (u16) ((u16)blend_state->unk_0A4) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4))
        - blend_state->unk_0A4) >> 2);
    blend_state->unk_0A6 = (u16) ((u16)blend_state->unk_0A6) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6))
        - blend_state->unk_0A6) >> 2);
    third_pending = D_80025B1C;
    if (((Row_81916800_S_81916800_3 *)third_pending)->unk_00.u != 0) {
        blend_state->unk_0A8 = (u16) ((u16)blend_state->unk_0A8) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8))
            - blend_state->unk_0A8) >> 2);
    }
    ((Row_81916800_S_81916800_3 *)third_pending)->unk_00.s = (s8) (blend_state->unk_0A8 != (s16) (*(u16 *)((u8 *)tracker + 8)));
    blend_state->unk_094 = (u16) ((s32) (((u16)blend_state->unk_094) << 0x10) >> 0x12);
    blend_state->unk_096 = (u16) ((s32) (((u16)blend_state->unk_096) << 0x10) >> 0x12);
}
