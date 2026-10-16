#include "modules/dungeon_ovl_7e6e1800.h"

void func_80024E5C(void *effect, void *motion, void *sprite) {
    s32 delta_x;
    s16 reduced_scale;
    u8 *height_table;
    s32 travel_distance;
    s16 travel_frames;
    s16 next_burst;
    s16 next_pair;
    s16 next_triple;
    s16 next_quad;
    s16 next_trail;
    s16 impact_state;
    s16 trail_index;
    s16 burst_index;
    s16 pair_index;
    s16 triple_index;
    s16 quad_index;
    s32 velocity_y;
    s32 target_y;
    s32 velocity_z;
    s32 target_z;
    s32 current_x;
    s32 end_frame;
    s32 target_x_or_z_step;
    s32 distance_x;
    s32 completion_state;
    s32 near_target;
    u16 next_color;
    u16 start_frame;
    u16 frames_left;
    u16 impact_frame;
    u16 scale;
    u16 burst_frame;
    u16 color_cycle;
    u16 initial_state;
    u16 clamped_scale;
    u8 effect_id;
    void *target_position;

    initial_state = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u;
    (*(s16 *)D_80025B60) = 1;
    if (initial_state < 3U) {
        ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0E.s = 0x3C;
        ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0D.s = 0x3C;
        ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0C.s = 0x3C;
        color_cycle = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_72;
        next_color = color_cycle + 1;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 = next_color;
        if (!(next_color & 7)) {
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 = (u16) (color_cycle + 2);
        }
        if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 & 1) {
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0C.u = 0x80;
        }
        if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 & 2) {
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0D.u = 0x80;
        }
        if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_72 & 4) {
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_0E.u = 0x80;
        }
    }
    if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.s == 0) {
        start_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = (u16) (start_frame + 1);
        if ((s16) start_frame >= 6) {
            effect_id = D_80025B38[0];
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_2C = D_80025B38;
            func_80047784(sprite, effect_id, 0);
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0U;
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u + 1);
            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at02.v = (u16) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at02.v - 0x5A);
        }
    }
    completion_state = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.s;
    if (completion_state == 1) {
        if ((func_800A4778(((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at02.v, ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at02.v,
            (s16) ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at02.v, ((Row_8192365C_S_80024E5C_0 *)effect)->unk_88) << 0x10) == 0) {
            if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_60 != 0) {
                target_position = ((Row_8192365C_S_80024E5C_4_pre *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_88))[-1].unk_00;
                ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_06 = 8;
                if (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s == 0) {
                    delta_x = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_00.at02.v;
                    delta_x -= ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at02u.v;
                    distance_x = abs(delta_x);
                    if (distance_x < 0) {
                        distance_x += 0x3F;
                    }
                    travel_distance = abs(((Row_8192365C_S_80024E5C_3 *)target_position)->unk_04.at02.v -
                                          ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at02u.v);
                    if (travel_distance < 0) {
                        travel_distance += 0x3F;
                    }
                    travel_distance = (distance_x >> 6) + (travel_distance >> 6);
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = (u16) (((s32) (travel_distance << 0x10) >> 0xF) + 0xB);
                }
                height_table = D_800DDC40;
                travel_frames = (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u;
                target_z = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_08
                - (((u8) *(((Row_8192365C_S_80024E5C_4 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_88))->unk_13 + height_table) >> 1)
                    << 0x10);
                near_target = travel_frames < 0xE;
                target_x_or_z_step = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_00.at00.v;
                target_y = ((Row_8192365C_S_80024E5C_3 *)target_position)->unk_04.at00.v;
                if (near_target == 0) {
                    current_x = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step - current_x) / (s32) (travel_frames
                        - 0xB));
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                        - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u
                        - 0xB));
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = (target_z
                        - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v) / (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s - 0xB);
                } else {
                    if (travel_frames >= 0xB) {
                        current_x = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v;
                        ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step
                            - current_x) / (s32) (travel_frames - 9));
                        ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                            - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u
                            - 9));
                        ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = (target_z
                            - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v) / (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s - 9);
                    } else {
                        if (travel_frames >= 5) {
                            s32 divisor;
                            s32 z_step;
                            current_x = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v;
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step
                                - current_x) / (s32) (travel_frames - 4));
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u
                                - 4));
                            z_step = target_z - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v;
                            divisor = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s - 4;
                            z_step /= divisor;
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = z_step;
                        } else {
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = (s32) ((s32) (target_x_or_z_step
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v) / travel_frames);
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v) / (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u);
                            ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = (s32) ((s32) (target_z
                                - ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v) / (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u);
                        }
                    }
                }
                velocity_y = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10;
                velocity_z = ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14;
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v
                    + ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v + velocity_y);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v + velocity_z);
                frames_left = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u - 1;
                ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = frames_left;
                if ((frames_left << 0x10) == 0) {
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u = 2U;
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_62 = 6;
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0U;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_14 = 0;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_10 = 0;
                    ((Row_8192365C_S_80024E5C_2 *)motion)->unk_0C = 0;
                    ((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 = 0x1E;
                }
            } else {
                ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0xAU;
                ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5C = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_5C - 1);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_00.at00.v
                    + ((Row_8192365C_S_80024E5C_0 *)effect)->unk_98);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_04.at00.v
                    + ((Row_8192365C_S_80024E5C_0 *)effect)->unk_9C);
                ((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v = (s32) (((Row_8192365C_S_80024E5C_2 *)motion)->unk_08.at00.v
                    + ((Row_8192365C_S_80024E5C_0 *)effect)->unk_A0);
                if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5C <= 0) {
                    ((Row_8192365C_S_80024E5C_5 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
                    (*(u16 *)((u8 *)effect + (-2))) = (u16) (((Row_8192365C_S_80024E5C_0_pre *)effect)[-1].unk_00 | 0x8000);
                    objectFlagBlock.flags |= 0x8000;
                    return;
                }
            }
            if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 5) {
                trail_index = 0;
                do {
                    func_80024D34(effect, motion, sprite);
                    next_trail = trail_index + 1;
                    trail_index = next_trail;
                } while (next_trail < 4);
            }
        } else {
            ((Row_8192365C_S_80024E5C_5 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
            (*(u16 *)((u8 *)effect + (-2))) = (u16) (((Row_8192365C_S_80024E5C_0_pre *)effect)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags |= 0x8000;
            return;
        }
    }
update_impact:
    impact_state = (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u;
    if (impact_state == 2) {
        impact_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u + 1;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = impact_frame;
        if ((s16) impact_frame == impact_state) {
            func_80024AEC(effect, motion, sprite);
            func_800A56E0(0x300);
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0xA) {
            scale = ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_1C;
            if (scale != 0) {
                reduced_scale = scale - 0xC8;
                clamped_scale = reduced_scale;
                if (reduced_scale < 0) {
                    clamped_scale = 0;
                }
                ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_1C = clamped_scale;
                ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_1E = clamped_scale;
            }
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x1E) {
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 + 3);
            func_800247B8(effect, motion, sprite);
            if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x28) {
                func_800247B8(effect, motion, sprite);
            }
            if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x2D) {
                func_800247B8(effect, motion, sprite);
            }
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u >= 0x32) {
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u = 3U;
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = 0U;
            ((Row_8192365C_S_80024E5C_1 *)sprite)->unk_14 = (u16) (((Row_8192365C_S_80024E5C_1 *)sprite)->unk_14 | 0x80);
        }
    }
    if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_58.u == 3) {
        burst_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u + 1;
        ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u = burst_frame;
        if ((s16) burst_frame < 0x12) {
            burst_index = 0;
            ((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 = (u16) (((Row_8192365C_S_80024E5C_0 *)effect)->unk_56 - 3);
            do {
                func_800247B8(effect, motion, sprite);
                next_burst = burst_index + 1;
                burst_index = next_burst;
            } while (next_burst < 5);
        }
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u == 0x10) {
            pair_index = 0;
            do {
                func_800247B8(effect, motion, sprite);
                next_pair = pair_index + 1;
                pair_index = next_pair;
            } while (next_pair < 2);
        }
        triple_index = 0;
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u == 0x11) {
            do {
                func_800247B8(effect, motion, sprite);
                next_triple = triple_index + 1;
                triple_index = next_triple;
            } while (next_triple < 3);
        }
        quad_index = 0;
        if ((s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u == 0x12) {
            do {
                func_800247B8(effect, motion, sprite);
                next_quad = quad_index + 1;
                quad_index = next_quad;
            } while (next_quad < 4);
        }
        end_frame = (s16) ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.u;
        completion_state = 1;
        if (end_frame == 1) {
            func_800D4AB0(effect, motion, sprite);
            end_frame = ((Row_8192365C_S_80024E5C_0 *)effect)->unk_5A.s;
        }
        if (end_frame >= 0x1B) {
            ((Row_8192365C_S_80024E5C_5 *)(((Row_8192365C_S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
            (*(u16 *)((u8 *)effect + (-2))) = (u16) (((Row_8192365C_S_80024E5C_0_pre *)effect)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags |= 0x8000;
            return;
        }
    }
    func_800478B8(sprite);
}
