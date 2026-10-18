#include "modules/dungeon_ovl_188298c.h"

void create_radius_directional_effects(s32 effect_param, void *origin_arg, s16 radius_arg, u8 *blocked_dirs) {
    s16 target_y;
    s16 target_x;
    s32 source_y;
    s32 source_x;
    s32 direction;
    ovl_188298c_81862C28_S_81862C28_1 *effect_data;
    ovl_188298c_81862C28_S_81862C28_0 *effect;
    s16 tile_x;
    s16 tile_dy;
    s16 origin_z;

    if (radius_arg == 0) {
        effect = func_8003FC64(0x212);
        if (effect != 0) {
            effect_data = effect->unk_0C;
            effect->unk_10 = advance_counter_and_propagate_target_flags;
            effect->unk_20 = effect_param;
            effect->unk_24 = 0;
            effect_data->unk_0E = 0x80;
            effect_data->unk_0D = 0x80;
            effect_data->unk_0C = 0x80;
            func_8003DB94(effect_data, D_800DE9D0, 0);
            effect_data->unk_1C = 0x1000;
            effect_data->unk_1E = 0x3000;
            effect_data->unk_12 = 0x7E0B;
            effect_data->unk_10 |= 0x20;
            effect_data->unk_14 |= 0x10C;
            func_8004491C(effect, func_80045340);
            effect_data = effect->unk_08;
            effect_data->unk_02.s = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_02.s;
            effect_data->unk_06.s = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_06.s;
            effect_data->unk_0A = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_0A.s;
        }
    } else {
        for (direction = 0; direction < 8; direction++) {
            effect_data = blocked_dirs + direction;
            if (effect_data->unk_00 == 0) {
                source_x = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_02.u;
                tile_x = (source_x / 64) + ((u16)dir_step_x[direction] * (u16)radius_arg);
                source_y = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_06.u;
                tile_dy = (source_y / 64) + (u16)dir_step_y[direction] * (u16)radius_arg;
                origin_z = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_0A.u;
                target_x = ((tile_x << 0x10) >> 0xA) + 0x20;
                target_y = ((tile_dy << 0x10) >> 0xA) + 0x20;
                if ((check_left_tile_and_center_height(target_x & 0xFFE0, target_y & 0xFFE0, origin_z) << 0x10) != 0) {
                    effect_data->unk_00 = 1;
                    continue;
                }
                effect = func_8003FC64(0x212);
                if (effect != 0) {
                    effect_data = effect->unk_0C;
                    effect->unk_10 = advance_counter_and_propagate_target_flags;
                    effect->unk_20 = effect_param;
                    effect->unk_24 = 0;
                    effect_data->unk_0E = 0x40;
                    effect_data->unk_0D = 0x40;
                    effect_data->unk_0C = 0x40;
                    func_8003DB94(effect_data, D_800DE9D0, 0);
                    effect_data->unk_1C = 0x1000;
                    effect_data->unk_1E = 0x1800;
                    effect_data->unk_12 = 0x7E0B;
                    effect_data->unk_10 |= 0x20;
                    effect_data->unk_14 |= 0x10C;
                    func_8004491C(effect, func_80045340);
                    effect_data = effect->unk_08;
                    effect_data->unk_02.u = target_x;
                    effect_data->unk_06.u = target_y;
                    effect_data->unk_0A = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_0A.s;
                    effect_data->unk_0A = get_surface_height_at_record(effect_data);
                }
            }
        }
    }
}
