#include "modules/dungeon_ovl_19c088c.h"

void advance_object_motion_and_animation(void *effect) {
    s32 blend_ticks;
    s32 elapsed_ticks;
    s32 color_index;
    u16 ticks_left;
    void *color_ptr;

    ticks_left = ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A - 1;
    ((s16 *)D_800261B0)[0] = 1;
    blend_ticks = ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E;
    ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A = ticks_left;
    elapsed_ticks = ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C - (s16) ticks_left;
    if (blend_ticks >= elapsed_ticks) {
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_54 = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_60
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_6C * elapsed_ticks) / blend_ticks));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_56 = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_62
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_6E * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_58 = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_64
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_70 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_5A = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_66
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_72 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_5C = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_68
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_74 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
        ((Row_819A1118_S_819A1118_0 *)effect)->unk_5E = (s16) (((Row_819A1118_S_819A1118_0 *)effect)->unk_6A
            + ((s32) (((Row_819A1118_S_819A1118_0 *)effect)->unk_76 * (((Row_819A1118_S_819A1118_0 *)effect)->unk_3C
            - (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A)) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3E));
    }
    for (color_index = 0; color_index < 4; color_index++) {
        color_ptr = (u8 *)effect + color_index * 4;
        ((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_0C =
            (s8) ((s32) (((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_1C * (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C);
        ((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_0D =
            (s8) ((s32) (((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_1D * (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C);
        ((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_0E =
            (s8) ((s32) (((Row_819A1118_S_819A1118_1 *)color_ptr)->unk_1E * (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A) / (s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3C);
    }
    if ((s16) ((Row_819A1118_S_819A1118_0 *)effect)->unk_3A <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((Row_819A1118_S_819A1118_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
