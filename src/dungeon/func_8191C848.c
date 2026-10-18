#include "modules/dungeon_ovl_193c848.h"

void func_80024048(void *motion, Row_8191C848_S_8191C848_3 *position, Rec_D_80082E80 *status) {
    s32 y_step_scaled;
    Row_8191C848_S_8191C848_1 *counter_state;
    counter_state = ((Row_8191C848_S_8191C848_0 *)motion)->unk_00;
    counter_state->unk_14 = (u16) (counter_state->unk_14 + 1);
    func_800478B8(status);
    if (status->unk_14.at00_u16.v & 0x6000) {
        ((Row_8191C848_S_8191C848_0_pre *)motion)[-1].unk_00 = (u16) (((Row_8191C848_S_8191C848_0_pre *)motion)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
    position->unk_02 = (u16) (position->unk_02 + ((s32) ((func_800644B8(((Row_8191C848_S_8191C848_0 *)motion)->unk_08)
        >> 4) * ((Row_8191C848_S_8191C848_0 *)motion)->unk_0A) >> 8));
    y_step_scaled = (func_80064584(((Row_8191C848_S_8191C848_0 *)motion)->unk_08) >> 4) * ((Row_8191C848_S_8191C848_0 *)motion)->unk_0A;
    position->unk_0A = (u16) (position->unk_0A - 4);
    position->unk_06 = (u16) (position->unk_06 + (y_step_scaled >> 8));
}
