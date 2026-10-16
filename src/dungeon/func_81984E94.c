#include "modules/dungeon_ovl_19a332c.h"

s32 inventoryResetSharedStateMode13(s32 unused, s32 state_key, s32 value, s16 secondary_value) {
    GameView *state = &gameWork.view;
    ovl_19a332c_81984E94_S_8191696C_state *substate = (ovl_19a332c_81984E94_S_8191696C_state *)&state->slot[0].unk_04;
    void *next_field = (void *)((u8 *)&state->slot[0].unk_04 + 4);
    s16 saved_value;
    s32 previous_key;
    s32 change_flags;

    previous_key = substate->unkC4;
    substate->unkC4 = state_key;
    substate->unkE0 = 0;
    substate->field_B8 = next_field;
    saved_value = value;
    change_flags = previous_key != state_key;
    if (substate->unkCC != 9) {
        change_flags |= 2;
    }
    substate->unkCC = 0xD;
    substate->unkD0 = 0;
    substate->unkDE = secondary_value;
    state->slot[0].callback = (void *)dungeonClearObjectBufferAndState;
    if (change_flags & 1) {
        D_800E3D20[0] = saved_value;
    }
    substate->unkDC = value;
    return change_flags;
}
