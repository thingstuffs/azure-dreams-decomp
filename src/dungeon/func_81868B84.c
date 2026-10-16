#include "modules/dungeon_ovl_188898c.h"

void func_80024384(void *effect, void *position) {
    s32 radial_product;
    s32 fade_angle;
    s32 grow_angle;
    s32 grow_point;
    s32 fade_angle_fixed;
    s32 grow_angle_fixed;
    u16 angular_speed;
    void *effect_data;
    s16 state;

    effect_data = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C;
    ((ovl_188898c_81868B84_S_81868B84_1 *)effect_data)->unk_14 = (u16) (((ovl_188898c_81868B84_S_81868B84_1 *)effect_data)->unk_14 + 1);
    ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s + 1);
    state = *(s16 *)effect;
    switch (state) {
    case 0:
        ((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v =
            (u16) (((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v - 4);
        createRandomizedGrayscaleEffect(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C, position, ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10);
        if (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.u < 8) {
            return;
        }
        {
            s32 next_state;
            next_state = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 + 1;
            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = 0U;

            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = next_state;
        }
        return;
    case 1:
        grow_point = 0;
        grow_angle_fixed = grow_point;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 + 6);
        angular_speed = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0A + 0x10;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0A = angular_speed;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + angular_speed);
        do {
            grow_angle = grow_angle_fixed >> 0x10;
            radial_product = (func_800644B8((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + grow_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_0C.at02_u16.v + (radial_product >> 8));
            radial_product = (func_80064584((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + grow_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_10.at02_u16.v + (radial_product >> 8));
            if ((dungeonCheckLeftTileAndCenterHeight(((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v,
                ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v,
                (s16) ((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v) << 0x10) == 0) {
                createRandomizedGrayscaleEffect(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C, position, ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10);
            }
            grow_angle_fixed += 0x05550000;
            grow_point += 1;
        } while (grow_point < 3);
        if (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.u < 0x20) {
            return;
        }
        {
            s32 next_state;
            next_state = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 + 1;
            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = 0U;

            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = next_state;
        }
        return;
    case 2:
        grow_point = 0;
        fade_angle_fixed = grow_point;
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06 + 6);
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 = (u16) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0A);
        do {
            fade_angle = fade_angle_fixed >> 0x10;
            radial_product = (func_800644B8((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + fade_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_0C.at02_u16.v + (radial_product >> 8));
            radial_product = (func_80064584((s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_08 + fade_angle)
                >> 4) * (s16) ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_06;
            ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v =
                (u16) (((Rec_func_80024264_arg1 *)position)->unk_10.at02_u16.v + (radial_product >> 8));
            if ((dungeonCheckLeftTileAndCenterHeight(((Rec_func_80024264_arg1 *)position)->unk_00.at02_u16.v,
                ((Rec_func_80024264_arg1 *)position)->unk_04.at02_u16.v,
                (s16) ((Rec_func_80024264_arg1 *)position)->unk_08.at02_u16.v) << 0x10) == 0) {
                createRandomizedGrayscaleEffect(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C, position, ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10);
            }
            fade_angle_fixed += 0x05550000;
            grow_point += 1;
        } while (grow_point < 3);
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10 = (u8) (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_10 - 8);
        if (((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.u < 8) {
            return;
        }
        {
            s32 next_state;
            next_state = ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 + 1;
            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_02.s = 0U;

            ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = next_state;
        }
        return;
    case 3:

        ((ovl_188898c_81868B84_S_81868B84_3 *)(((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_0C))->unk_16 = 1;
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((ovl_188898c_81868B84_S_81868B84_0_pre *)effect)[-1].unk_00 | 0x8000);
        {
            ObjectFlagBlock *global_flags;
            global_flags = &objectFlagBlock;
            global_flags->flags |= 0x8000;
        }
        return;
    default:
        ((ovl_188898c_81868B84_S_81868B84_0 *)effect)->unk_00 = 3;
    }
}
