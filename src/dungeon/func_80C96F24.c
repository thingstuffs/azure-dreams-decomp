#include "modules/dungeon_ovl_cb3000.h"

void create_radial_effect_bands(CB_80174724_S_80C96F24_0 *owner, void *origin, void *entity) {
    u16 band;
    register s32 shade_offset;

    owner->unk_A4 = 0;
    band = 0;

    do {
        s32 band_index;
        s16 segment;

        {

            band_index = (s16)band;
            segment = 0;
        }
        shade_offset = band_index * 0x10;

        do {
            s16 end_radius = 0;
            s16 start_radius = 0;
            s32 last_band;
            void *effect;

            if (band_index == 0) {
                start_radius = 0x18;
            }

            last_band = 2;
            if (band_index == 1) {
                start_radius = 0x18;
                end_radius = 0x18;
            }
            if (band_index == last_band) {
                start_radius = 0;
                end_radius = 0x18;
            }

            effect = func_8003FC64(0x12);
            if (effect != 0) {
                void *render_state;
                void *effect_data;
                CB_80174724_S_80C96F24_5 *position;
                s16 init_value;
                s16 angle_index;
                s32 start_angle;
                s32 end_angle;

                effect_data = (u8 *)effect + 0x20;

                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_24 = 0x42;
                init_value = 0x17;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_26 = 0;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_2A = segment;

                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_2C =
                    init_value - ((CB_80174724_S_80C96F24_2 *)owner)->unk_A4;
                ((CB_80174724_S_80C96F24_3 *)effect)->unk_10 = create_angular_offset_effect;
                register_node(effect, advance_boss_command_stream);

                render_state = ((CB_80174724_S_80C96F24_3 *)effect)->unk_0C;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_10 = 0x20;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_14 |= 0x0C;

                {

                    position = ((CB_80174724_S_80C96F24_3 *)effect)->unk_08;
                    position->unk_00 =
                        ((CB_80174724_S_80C96F24_6 *)origin)->unk_00;
                    position->unk_04 =
                        ((CB_80174724_S_80C96F24_6 *)origin)->unk_04;
                    position->unk_08 =
                        ((CB_80174724_S_80C96F24_6 *)origin)->unk_08 + 0x200000;
                }

                render_state = ((CB_80174724_S_80C96F24_3 *)effect)->unk_0C;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_1E = 0x1000;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_1C = 0x1000;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_0E = 0x80;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_0D = 0x80;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_0C = 0x80;

                ((CB_80174724_S_80C96F24_3 *)effect)->unk_20 =
                    (func_80069EF8() & 0x1F) + 0x10 + shade_offset;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 =
                    (func_80069EF8() & 0x1F) + 0x10 + shade_offset;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 =
                    (func_80069EF8() & 0x1F) + 0x10 + shade_offset;

                {
                    s32 segment_index = (s16)segment;

                    if ((segment_index == 1) || (segment_index == 6)) {
                        ((CB_80174724_S_80C96F24_3 *)effect)->unk_20 += 0x0A;
                        ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 += 0x0A;
                        ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 += 0x0A;
                    }
                }
                if (((s16)segment == 2) || ((s16)segment == 5)) {
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_00 += 0x14;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 += 0x14;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 += 0x14;
                }
                if ((u16)(segment - 3) < 2U) {
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_00 += 0x1E;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 += 0x1E;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 += 0x1E;
                }

                {
                    u8 *template_data;
                    template_data = D_80175330;
                    *(CB_80174724_Copy12 *)((u8 *)effect_data + 0x7A) = *(CB_80174724_Copy12 *)template_data;
                }

                {
                    s16 end_radius_copy;
                    void *render_data;
                    u32 trig_angle;
                    s32 trig_value;
                    s32 product;

                    angle_index = (s16)segment;
                    end_angle = (angle_index + 1) << 9;
                    trig_angle = end_angle;
                    render_data = effect_data + 0x7A;
                    ((CB_80174724_S_80C96F24_4 *)render_state)->unk_08 = render_data;

                    product = start_radius * func_80064584(trig_angle);
                    start_angle = angle_index << 9;
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_44 = last_band;
                    product = start_radius * func_80064584(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_4A = last_band;
                    trig_value = func_80064584(end_angle);
                    end_radius_copy = end_radius;
                    product = end_radius_copy * trig_value;
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_50 = last_band;
                    product = end_radius_copy * func_80064584(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_56 = last_band;
                    product = start_radius * func_800644B8(end_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_46 = last_band;
                    product = start_radius * func_800644B8(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_4C = last_band;
                    product = end_radius_copy * func_800644B8(end_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_52 = last_band;
                    product = end_radius_copy * func_800644B8(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_58 = last_band;
                }

                {
                    s32 last_band_z;
                    s16 end_z = 0;
                    s16 start_z = end_z;

                    if (band_index == 0) {
                        start_z = -0x14;
                    }

                    last_band_z = 2;
                    if (band_index == 1) {
                        start_z = -0x2E;
                        end_z = -0x14;
                    }
                    if (band_index == last_band_z) {
                        start_z = -0x42;
                        end_z = -0x2E;
                    }
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_4E = start_z;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_48 = start_z;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_5A = end_z;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_54 = end_z;
                }
            }

            {
                s32 segment_step;
                u16 effect_count;

                segment++;
                segment_step = segment;
                effect_count = ((CB_80174724_S_80C96F24_7 *)owner)->unk_A4;
                segment_step = segment_step < 8;
                effect_count++;
                ((CB_80174724_S_80C96F24_7 *)owner)->unk_A4 = effect_count;
                if (segment_step) {
                    continue;
                }
                break;
            }
        } while (1);

        {
            s16 next_band;

            next_band = (s16)(band + 1);
            band = (u16)next_band;
            if (next_band >= 3) {
                break;
            }
        }
    } while (1);
}
