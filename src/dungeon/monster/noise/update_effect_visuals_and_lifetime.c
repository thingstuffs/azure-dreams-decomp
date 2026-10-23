#include "dungeon/monster/manoeva.h"
#include "modules/dungeon_ovl_7f43f800_p01.h"
#include "shared/object_flags.h"

/* Update effect brightness, size and position, then decrement its lifetime. */
void update_effect_visuals_and_lifetime(void *state, void *position, void *effect_arg)
{
    T_80170AD0_StackWork coord_work;
    void *effect_coords;
    void *effect;
    s16 ticks_left;
    s16 next_ticks;
    s32 brightness;
    s32 scaled_offset;
    s32 position_value;
    s32 reference_value;
    s32 effect_size;
    void *reference_coords;

    effect_coords = position;

    ticks_left = ((T_80170AD0_S_80170AD0_0 *)state)->unk_96.s;
    effect = effect_arg;
    if (ticks_left < 0x15) {
        brightness = (ticks_left << 7) / 20;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_0C = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_0D =
            ((T_80170AD0_S_80170AD0_1 *)effect)->unk_0E = brightness;
    }

    ticks_left = ((T_80170AD0_S_80170AD0_0 *)state)->unk_96.s;
    if (ticks_left >= 0x2B) {
        effect_size = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E + 0x2BC;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E = effect_size;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1C = effect_size;
    } else if (ticks_left >= 0x28) {
        effect_size = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E + 0x226;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E = effect_size;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1C = effect_size;
    } else if (ticks_left >= 0x26) {
        effect_size = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E + 0x190;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E = effect_size;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1C = effect_size;
    } else if (ticks_left >= 0x24) {
        effect_size = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E + 0xC8;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E = effect_size;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1C = effect_size;
    } else if (ticks_left >= 0x1A) {
        effect_size = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E + 0x64;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E = effect_size;
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1C = effect_size;
    }

    {
        void *effect_params;

        effect_params = ((T_80170AD0_S_80170AD0_1 *)effect)->unk_08;
        scaled_offset = (((T_80170AD0_S_80170AD0_2 *)effect_params)->unk_0B + ((T_80170AD0_S_80170AD0_2 *)effect_params)->unk_03) *
                  ((T_80170AD0_S_80170AD0_1 *)effect)->unk_1E;
    }
    if (scaled_offset < 0) {
        scaled_offset += 0xFFF;
    }
    scaled_offset >>= 12;
    ((T_80170AD0_S_80170AD0_1 *)effect)->unk_22 = ((s32)(-scaled_offset)) / 2;

    if (((T_80170AD0_S_80170AD0_0 *)state)->unk_A2 == 0) {
        coord_work.xyz[0] = ((T_80170AD0_S_80170AD0_3 *)effect_coords)->unk_02;
        coord_work.xyz[1] = ((T_80170AD0_S_80170AD0_3 *)effect_coords)->unk_06;
        coord_work.xyz[2] = ((T_80170AD0_S_80170AD0_3 *)effect_coords)->unk_0A;
        position_value = RotTransPers(coord_work.xyz, &coord_work.out18, &coord_work.out20, &coord_work.out24);

        reference_coords = ((T_80170AD0_S_80170AD0_0 *)state)->unk_A8;
        coord_work.xyz[0] = ((T_80170AD0_S_80170AD0_4 *)reference_coords)->unk_02;
        coord_work.xyz[1] = ((T_80170AD0_S_80170AD0_4 *)reference_coords)->unk_06;
        coord_work.xyz[2] = ((T_80170AD0_S_80170AD0_4 *)reference_coords)->unk_0A;
        reference_value = RotTransPers(coord_work.xyz, &coord_work.out18, &coord_work.out20, &coord_work.out24);
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_06 = position_value - reference_value -
            (view_direction_depth_biases[((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80170AD0_S_80170AD0_0 *)state)->unk_94 + 0x100) >> 9) & 7] * 2);
    } else {
        ((T_80170AD0_S_80170AD0_1 *)effect)->unk_06 = 4;
    }
    advance_sprite_animation_and_textures(effect);
    next_ticks = ((T_80170AD0_S_80170AD0_0 *)state)->unk_96.u - 1;
    ((T_80170AD0_S_80170AD0_0 *)state)->unk_96.u = next_ticks;
    if ((next_ticks << 16) <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
