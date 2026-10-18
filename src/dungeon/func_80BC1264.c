#include "modules/dungeon_ovl_be1084.h"

void advance_effect_toward_target(void *effect, void *position) {
    s16 fade_level;
    s32 scaled_red;
    s32 scaled_green;
    s32 x_distance;
    s32 y_distance;
    s32 scaled_blue;

    ((S_80BC1264_0 *)position)->unk_00.at00.v = (s32) (((S_80BC1264_0 *)position)->unk_00.at00.v
        + ((S_80BC1264_1 *)effect)->unk_40);
    ((S_80BC1264_0 *)position)->unk_04.at00.v = (s32) (((S_80BC1264_0 *)position)->unk_04.at00.v
        + ((S_80BC1264_1 *)effect)->unk_44);
    ((S_80BC1264_0 *)position)->unk_08 = (s32) (((S_80BC1264_0 *)position)->unk_08 + ((S_80BC1264_1 *)effect)->unk_48);
    ((S_80BC1264_1 *)effect)->unk_40 = (s32) (((S_80BC1264_1 *)effect)->unk_40 + ((S_80BC1264_1 *)effect)->unk_4C);
    ((S_80BC1264_1 *)effect)->unk_44 = (s32) (((S_80BC1264_1 *)effect)->unk_44 + ((S_80BC1264_1 *)effect)->unk_50);
    ((S_80BC1264_1 *)effect)->unk_48 = (s32) (((S_80BC1264_1 *)effect)->unk_48 + ((S_80BC1264_1 *)effect)->unk_54);
    x_distance = abs(((S_80BC1264_1 *)effect)->unk_36 - ((S_80BC1264_0 *)position)->unk_00.at02.v);
    if (x_distance < 0x10) {
        y_distance = abs(((S_80BC1264_1 *)effect)->unk_38 - ((S_80BC1264_0 *)position)->unk_04.at02.v);
        if (y_distance < 0x10) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80BC1264_1_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
        }
    }
    scaled_red = ((S_80BC1264_1 *)effect)->unk_00 * ((S_80BC1264_1 *)effect)->unk_32;
    ((S_80BC1264_1 *)effect)->unk_04.at00.v = (s8) (scaled_red / 256);
    scaled_green = ((S_80BC1264_1 *)effect)->unk_01 * ((S_80BC1264_1 *)effect)->unk_32;
    ((S_80BC1264_1 *)effect)->unk_04.at01.v = (s8) (scaled_green / 256);
    scaled_blue = ((S_80BC1264_1 *)effect)->unk_02 * ((S_80BC1264_1 *)effect)->unk_32;
    ((S_80BC1264_1 *)effect)->unk_04.at02.v = (s8) (scaled_blue / 256);
    fade_level = (u16) ((S_80BC1264_1 *)effect)->unk_32 - 8;
    ((S_80BC1264_1 *)effect)->unk_32 = fade_level;
    ((S_80BC1264_1 *)effect)->unk_08 = (s32) ((S_80BC1264_1 *)effect)->unk_04.at00u.v;
    if ((fade_level << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80BC1264_1_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
