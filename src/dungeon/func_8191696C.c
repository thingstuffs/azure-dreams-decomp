#include "modules/dungeon_ovl_1936800.h"

s32 begin_view_parameter_transition(s32 unused, s32 request_id, s32 request_value, s16 request_param) {
    GameView *state = &g_game_work.view;
    Row_8191696C_S_8191696C_state *dispatch = (Row_8191696C_S_8191696C_state *)&state->slot[0].unk_04;
    void *payload_start = (void *)((u8 *)&state->slot[0].unk_04 + 4);
    s16 saved_value;
    s32 prev_request_id;
    s32 change_flags;

    prev_request_id = dispatch->unkC4;
    dispatch->unkC4 = request_id;
    dispatch->unkE0 = 0;
    dispatch->field_B8 = payload_start;
    saved_value = request_value;
    change_flags = prev_request_id != request_id;
    if (dispatch->unkCC != 9) {
        change_flags |= 2;
    }
    dispatch->unkCC = 0xC;
    dispatch->unkD0 = 0;
    dispatch->unkDE = request_param;
    state->slot[0].callback = D_80024024;
    if (change_flags & 1) {
        ((s8 *)D_800E3D20)[0] = saved_value;
    }
    dispatch->unkDC = request_value;
    return change_flags;
}
