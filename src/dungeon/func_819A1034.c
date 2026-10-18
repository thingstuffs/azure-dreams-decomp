#include "modules/dungeon_ovl_19c088c.h"

void func_80024834(void *fade_data)
{
    void *fade;
    s32 color_index;
    u16 ticks_left;

    fade = fade_data;
    ticks_left = ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.s;
    (*(s16 *)D_800261B0) = 1;
    ticks_left--;
    ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.s = ticks_left;
    for (color_index = 0; color_index < 4; color_index++) {
        ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_0C =
            ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_1C * ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u /
            ((Row_819A1034_S_819A1034_0 *)fade)->unk_3C;
        ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_0D =
            ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_1D * ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u /
            ((Row_819A1034_S_819A1034_0 *)fade)->unk_3C;
        ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_0E =
            ((Row_819A1034_S_819A1034_2 *)((u8 *)fade + color_index * 4))->unk_1E * ((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u /
            ((Row_819A1034_S_819A1034_0 *)fade)->unk_3C;
    }
    if (((Row_819A1034_S_819A1034_0 *)fade)->unk_3A.u <= 0) {
        (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
