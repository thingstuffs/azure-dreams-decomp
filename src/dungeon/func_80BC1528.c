#include "modules/dungeon_ovl_be1084.h"

void create_parent_return_effect(
    void *parent_obj, s16 effect_param, s32 initial_value, s16 duration,
    s16 offset_x, s16 offset_y, s16 offset_z)
{
    S_80BC1528_1 *parent = parent_obj;
    void *effect;
    S_80BC1528_2 *effect_data;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 rounded_step_x;
    s32 rounded_step_z;

    effect = func_8003FD64(0x211, parent);
    if (effect != 0) {
        ((S_80BC1528_0 *)effect)->unk_10 = advance_effect_toward_target;

        ((S_80BC1528_3 *)(((S_80BC1528_0 *)effect)->unk_08))->unk_02 =
            ((S_80BC1528_4 *)(parent->unk_08))->unk_02 + offset_x;
        ((S_80BC1528_3 *)(((S_80BC1528_0 *)effect)->unk_08))->unk_06 =
            ((S_80BC1528_4 *)(parent->unk_08))->unk_06 + offset_y;
        ((S_80BC1528_3 *)(((S_80BC1528_0 *)effect)->unk_08))->unk_0A =
            ((S_80BC1528_4 *)(parent->unk_08))->unk_0A + offset_z - 100;

        effect_data = (u8 *)effect + 0x20;
        effect_data->unk_36 = ((S_80BC1528_4 *)(parent->unk_08))->unk_02;
        effect_data->unk_38 = ((S_80BC1528_4 *)(parent->unk_08))->unk_06;
        effect_data->unk_3A = ((S_80BC1528_4 *)(parent->unk_08))->unk_0A;

        step_x = -(offset_x << 16) / (duration / 8);
        effect_data->unk_40 = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        effect_data->unk_44 = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        effect_data->unk_48 = step_z / 2;

        rounded_step_x = -(offset_x << 16) / (duration / 8);
        if (rounded_step_x < 0) {
            rounded_step_x += 3;
        }
        effect_data->unk_4C = rounded_step_x >> 2;

        rounded_step_z = step_y;
        if (rounded_step_z < 0) {
            rounded_step_z += 3;
        }
        effect_data->unk_50 = rounded_step_z >> 2;

        rounded_step_z = step_z;
        effect_data->unk_54 = (rounded_step_z / 4);

        effect_data->unk_14 = effect_param;
        effect_data->unk_32 = duration;
        func_8004491C(effect, build_projected_tile_packets, step_x);
        rounded_step_x = initial_value;
        ((S_80BC1528_0 *)effect)->unk_20 = rounded_step_x;
        effect_data->unk_08 = initial_value;
    }

}
