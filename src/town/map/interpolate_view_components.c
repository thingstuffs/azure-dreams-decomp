#include "common.h"
#include "shared/game_work.h"

typedef struct S_800A526C_1 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0xA];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
} S_800A526C_1;   /* arg0 in interpolate_view_components */


extern u8 map_transition_handler_address[16];

/* Interpolate three state components toward their targets and advance the transition when complete. */
void interpolate_view_components(S_800A526C_1 *transition)
{
    GameWork *state_base;
    s32 ticks_left;
    u16 target_component;

    state_base = &g_game_work;
    state_base->view.view_offset.parts.view_offset_x =
        ((u16)state_base->view.view_offset.parts.view_offset_x) +
        ((transition->unk_00.s - state_base->view.view_offset.parts.view_offset_x) /
         transition->unk_18);
    state_base->view.view_offset.parts.view_offset_y =
        ((u16)state_base->view.view_offset.parts.view_offset_y) +
        ((transition->unk_02.s - state_base->view.view_offset.parts.view_offset_y) /
         transition->unk_18);
    state_base->view.view_offset.parts.view_offset_z =
        ((u16)state_base->view.view_offset.parts.view_offset_z) +
        ((transition->unk_04.s - state_base->view.view_offset.parts.view_offset_z) /
         transition->unk_18);

    ticks_left = transition->unk_18 - 1;
    transition->unk_18 = ticks_left;
    if (ticks_left <= 0) {
        target_component = transition->unk_00.u;
        transition->unk_10 = target_component;
        state_base->view.view_offset.parts.view_offset_x = target_component;

        target_component = transition->unk_02.u;
        transition->unk_12 = target_component;
        state_base->view.view_offset.parts.view_offset_y = target_component;

        target_component = transition->unk_04.u;
        transition->unk_14 = target_component;
        state_base->view.view_offset.parts.view_offset_z = target_component;

        transition->unk_20 = map_transition_handler_address;
    }
}
