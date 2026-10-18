/* Relink of matched dungeon/func_80A4B134; every changed retail word is a paired relocation. */
#define update_fading_four_strip_effect func_8016E934
#define D_80175910 D_8016F910
#define advance_record_countdown D_8016E8F0
#include "modules/dungeon_resource06_slot0.h"
extern s32 func_8016E89C(void *, void *, void *);
extern void func_8016E214(void *, s16, s32, s16, s16, s16, s16);
extern s32 func_80069EF8(void);

void func_8016E934(u8 *effect, R06_80174934_Vec3w *origin, u8 *render_data)
{
    s16 phase;
    u16 phase_bits;
    s16 strip_index;
    s16 vertex_index;
    s16 next_vertex;
    s16 row_index;
    s16 next_row;
    s16 axis_index;
    s16 next_axis;
    s16 frames_left;
    s16 top;
    s16 bottom;
    s32 fade_level;
    s32 random_offset;
    s32 particle_variant;
    s32 particle_strength;
    u8 *strip_obj;
    u8 *init_obj;
    u8 *strip_data;
    u8 *render_ctl;
    u8 *position;
    u8 *frame_data;
    void *callback;
    u32 *vertex_color;

    phase_bits = ((R06_80174934_S_80174934_0 *)effect)->unk_16.u;
    phase = ((R06_80174934_S_80174934_0 *)effect)->unk_16.s;
    switch (phase) {
    case 0:
        render_data[0xC] = (u8)((effect[4] *
            (0x32 - ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s)) / 10);
        render_data[0xD] = (u8)((effect[5] *
            (0x32 - ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s)) / 10);
        fade_level = 0x32 - ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s;
        render_data[0xE] = (u8)((effect[6] * fade_level) / 10);
        if (((R06_80174934_S_80174934_0 *)effect)->unk_1A.s < 0x29) {
            ((R06_80174934_S_80174934_0 *)effect)->unk_16.p =
                ((R06_80174934_S_80174934_0 *)effect)->unk_16.u + 1;
        }
        break;
    case 1:
        if (((R06_80174934_S_80174934_0 *)effect)->unk_1A.s < 0xC) {
            ((R06_80174934_S_80174934_0 *)effect)->unk_16.s = phase_bits + 1;
        }

        if (func_80069EF8() & 1) {
            particle_variant = func_80069EF8() & 7;
            particle_strength = func_80069EF8() & 0xFF;
            particle_strength = particle_strength | 0x80;
            random_offset = func_80069EF8();
            func_8016E214(effect - 0x20, particle_variant, 0xF0, particle_strength,
                ((R06_80174934_S_80174934_0 *)effect)->unk_64, ((R06_80174934_S_80174934_0 *)effect)->unk_66,
                (s16)(-0x70 - (random_offset & 0x1F)));
        } else {
            particle_variant = func_80069EF8() & 7;
            particle_strength = func_80069EF8() & 0xFF;
            particle_strength = particle_strength | 0x80;
            random_offset = func_80069EF8();
            func_8016E214(effect - 0x20, particle_variant, 0xF0, particle_strength,
                ((R06_80174934_S_80174934_0 *)effect)->unk_64, ((R06_80174934_S_80174934_0 *)effect)->unk_66,
                (s16)(-0x40 - (random_offset & 0x1F)));
        }
        break;
    case 2:
        render_data[0xC] = (u8)((effect[4] * ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s) / 10);
        render_data[0xD] = (u8)((effect[5] * ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s) / 10);
        render_data[0xE] = (u8)((effect[6] * ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s) / 10);
        break;
    }

    ((R06_80174934_S_80174934_0 *)effect)->unk_20 = ((R06_80174934_S_80174934_0 *)effect)->unk_20 + 1;
    for (strip_index = 0; strip_index < 4; strip_index++) {
        strip_obj = func_8003FC64(0x12);
        if (strip_obj != 0) {
            init_obj = strip_obj;
            callback = ((u8 *)func_8016E89C);
            strip_data = strip_obj + 0x20;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_1A = 1;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_1C = 1;
            ((R06_80174934_S_80174934_2 *)strip_obj)->unk_10 = ((u8 *)advance_record_countdown);
            func_8004491C(init_obj, callback);

            render_ctl = ((R06_80174934_S_80174934_2 *)strip_obj)->unk_0C;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_10 = 0x20;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_14 |= 0xC;

            position = ((R06_80174934_S_80174934_2 *)strip_obj)->unk_08;
            ((R06_80174934_S_80174934_4 *)position)->unk_00 = origin->x;
            ((R06_80174934_S_80174934_4 *)position)->unk_04 = origin->y;
            ((R06_80174934_S_80174934_4 *)position)->unk_08 = origin->z;

            render_ctl = ((R06_80174934_S_80174934_2 *)strip_obj)->unk_0C;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_1E = 0x1000;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_1C = 0x1000;
            render_ctl[0xE] = 0x80;
            render_ctl[0xD] = 0x80;
            render_ctl[0xC] = 0x80;

            vertex_index = 0;
            do {
                vertex_color = (u32 *)strip_data + vertex_index;
                ((u8 *)vertex_color)[4] = render_data[0xC];
                ((u8 *)vertex_color)[5] = render_data[0xD];
                next_vertex = vertex_index + 1;
                vertex_index = next_vertex;
                ((u8 *)vertex_color)[6] = render_data[0xE];
            } while (next_vertex < 4);

            if (strip_index == 3) {
                strip_data[0xA] = 0;
                strip_data[9] = 0;
                strip_data[8] = 0;
                strip_data[6] = 0;
                strip_data[5] = 0;
                strip_data[4] = 0;
            }

            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_06 = 0;
            memcpy(strip_data + 0x28, ((u8 *)D_8016F910), 12);
            frame_data = strip_data + 0x28;
            ((R06_80174934_S_80174934_3 *)render_ctl)->unk_08 = frame_data;
            frame_data[8] = (u8)(frame_data[8] + ((R06_80174934_S_80174934_0 *)effect)->unk_1E * 4);
            frame_data = ((R06_80174934_S_80174934_3 *)render_ctl)->unk_08;
            frame_data[9] = (u8)(frame_data[9] + ((((R06_80174934_S_80174934_0 *)effect)->unk_20 & 3) * 8));

            row_index = 0;
            do {
                axis_index = 0;
                do {
                    ((R06_80174934_Rows *)strip_data)->row[row_index][axis_index] =
                        ((R06_80174934_Rows *)effect)->row[row_index][axis_index];
                    next_axis = axis_index + 1;
                    axis_index = next_axis;
                } while (next_axis < 3);
                next_row = row_index + 1;
                row_index = next_row;
            } while (next_row < 4);

            top = 0 - ((strip_index + 1) * 0x10);
            bottom = 0 - (strip_index * 0x10);
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_6E = top;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_68 = top;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_7A = bottom;
            ((R06_80174934_S_80174934_1 *)strip_data)->unk_74 = bottom;
        }
    }

    frames_left = ((R06_80174934_S_80174934_0 *)effect)->unk_1A.u - 1;
    ((R06_80174934_S_80174934_0 *)effect)->unk_1A.s = frames_left;
    if (frames_left <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
    return;
}
