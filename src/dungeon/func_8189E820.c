#include "modules/dungeon_ovl_18be820.h"

void func_80024020(void *state, Row_8189E820_S_8189E820_2 *motion, Row_8189E820_S_8189E820_3 *rotation)
{
    s16 next_frame;
    s32 x_pos;
    s32 x_step;
    s32 y_pos;
    s32 y_step;
    Row_8189E820_S_8189E820_1 *frame_state;

    frame_state = ((Row_8189E820_S_8189E820_0 *)state)->unk_08;
    frame_state->unk_14 =
        (u16)(frame_state->unk_14 + 1);
    x_pos = motion->unk_00;
    x_step = motion->unk_0C;
    y_pos = motion->unk_04;
    y_step = motion->unk_10;
    motion->unk_00 = x_pos + x_step;
    motion->unk_04 = y_pos + y_step;
    ((Row_8189E820_S_8189E820_0 *)state)->unk_04 =
        ((Row_8189E820_S_8189E820_0 *)state)->unk_04 + motion->unk_14;
    motion->unk_08 =
        ((Row_8189E820_S_8189E820_0 *)state)->unk_04 -
        ((func_800644B8((0x800 / (s16)((Row_8189E820_S_8189E820_0 *)state)->unk_02) *
                        ((Row_8189E820_S_8189E820_0 *)state)->unk_00,
                        y_step) >> 4) * 0xC000);
    rotation->unk_1A =
        (u16)(rotation->unk_1A + 0x300);
    next_frame = (u16)((Row_8189E820_S_8189E820_0 *)state)->unk_00 + 1;
    ((Row_8189E820_S_8189E820_0 *)state)->unk_00 = next_frame;
    if (((Row_8189E820_S_8189E820_0 *)state)->unk_02 < next_frame) {
        ((Row_8189E820_S_8189E820_0_pre *)state)[-1].unk_00 =
            (u16)(((Row_8189E820_S_8189E820_0_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
