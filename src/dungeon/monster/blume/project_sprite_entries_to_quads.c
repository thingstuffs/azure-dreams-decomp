#include "dungeon/monster/blume/project_sprite_entries_to_quads.h"
#include "dungeon/monster/garuda.h"
#include "dungeon/monster/blume.h"


/*
 * Projects flipped sprite quads with depth and screen checks, dispatches custom drawing entries,
 * and queues packets.
 */
void project_sprite_entries_to_quads(T_80170874_S_80DB9000_1 *sprite_size, T_80170874_S_80DB9000_2 *position, T_80170874_S_80DB9000_3 *sprite, s16 depth_bias) {
    s32 screen_y3;
    register s32 view_rot_z;
    register s32 view_rot_x;
    register s32 view_rot_y;
    s16 top_y;
    s16 bottom_y;
    s16 flipped_left_x;
    s16 left_x;
    s16 right_x;
    s16 flipped_top_y;
    s32 first_three_visible;
    s32 first_two_visible;
    s32 *ot_entry;
    u32 packet_addr;
    s32 corner2_visible;
    s32 corner0_visible;
    s32 corner1_visible;
    s32 corner3_visible;
    u32 view_y_angle;
    u16 field_value;
    u32 tex_word;
    u32 scale_y;
    u32 depth;
    u32 ot_index;
    u32 neg_width;
    u32 depth_scaled;
    register u32 coord_offset;
    u32 uv_right;
    T_80170874_S_80DB9000_6 *state;
    s16 screen_offset;
    s16 screen_offset_2;
    register u32 coord_value;
    s32 packet_code;
    u8 right_u;
    u8 bottom_v;
    s32 blend_code;
    void *(*draw_callback)(void *, void *, void *, void *, void *);
    T_80170874_S_80DB9000_7 *render_data;
    GameWork *render_state;
    T_80170874_S_80DB9000_9 *packet;
    register T_80170874_S_80DB9000_4 *scratch_page;
    scratch_page = (T_80170874_S_80DB9000_4 *)0x1F800000;

    state = (T_80170874_S_80DB9000_6 *)g_game_work.draw_buffer;
    scratch_page->unk_90 = 0;
    scratch_page->unk_CC = 0;
    scratch_page->unk_C4 = 0;
    scratch_page->unk_BC = 0;
    scratch_page->unk_B4 = 0;
    scratch_page->unk_24 = (u8 *)state + 0xB0;
    scratch_page->unk_04 = position->unk_02;
    scratch_page->unk_06 = position->unk_06;
    scratch_page->unk_08 = position->unk_0A;
    packet = state->unk_8D0;
    render_state = &g_game_work;
    scratch_page->unk_100 = RotTransPers(&scratch_page->unk_04, &scratch_page->origin.word, &scratch_page->transform_p, &scratch_page->transform_flags);
    sprite->unk_14 = (u16)(sprite->unk_14 | 0x8000);
    depth = scratch_page->unk_100;
    depth_scaled = depth * 4;
    depth -= 0xA;
    ot_index = depth - depth_bias;
    render_data = (T_80170874_S_80DB9000_7 *)&sprite_projection_matrix;
    render_data->unk_1C = (s32)depth_scaled;
    scratch_page->unk_100 = ot_index;
    if (ot_index < 0x1D6U) {
        PushMatrix();
        screen_offset_2 = scratch_page->origin.parts.x;
        screen_offset_2 -= 0xA0;
        scratch_page->origin.parts.x = screen_offset_2;
        screen_offset = scratch_page->origin.parts.y;
        view_rot_x = render_state->view.camera_rotation.parts.camera_rotation_x;
        view_rot_y = render_state->view.camera_rotation.parts.camera_rotation_y;
        view_rot_z = render_state->view.camera_rotation.parts.viewAngle;
        screen_offset -= 0x78;
        scratch_page->origin.parts.y = screen_offset;
        scratch_page->unk_34 = view_rot_x;
        scratch_page->unk_38.u32 = view_rot_y;
        scratch_page->unk_3C.u32 = view_rot_z;
        field_value = sprite->unk_16;
        view_y_angle = scratch_page->unk_38.u16;
        scratch_page->unk_A4 = field_value;
        coord_offset = sprite->unk_1A;
        coord_value = ((u16)render_state->view.view_rotation_offset.parts.view_rotation_offset_z);
        coord_offset -= view_y_angle;
        coord_value += coord_offset;
        scratch_page->unk_A8 = coord_value;
        coord_offset = sprite->unk_18;
        coord_value = scratch_page->unk_3C.u16;
        coord_offset -= 0x100;
        coord_value = (coord_value + 0x100) & 0x1FF;
        coord_offset += coord_value;
        scratch_page->unk_A6 = coord_offset;
        tex_word = sprite->unk_20;
        scratch_page->unk_88 = tex_word;
        scratch_page->unk_AC = tex_word;
        coord_value = sprite->unk_22;
        scratch_page->unk_8C = coord_value;
        scratch_page->unk_AE = coord_value;
        RotMatrix((u8 *)0x1F8000A4, (u8 *)0x1F800074, view_y_angle, view_rot_z);
        scratch_page->unk_34 = sprite->unk_1C;
        scale_y = sprite->unk_1E;
        scratch_page->unk_3C.u32 = 0x1000;
        scratch_page->unk_38.u32 = scale_y;
        ScaleMatrix((u8 *)0x1F800074, (u8 *)0x1F800034);
        CompMatrix(render_data, (u8 *)0x1F800074, (u8 *)0x1F800054);
        SetTransMatrix((u8 *)0x1F800054);
        SetRotMatrix((u8 *)0x1F800054);
        render_data = sprite->unk_08;
        scratch_page->unk_28 = sprite->unk_14;
        for (;;) {
        if (!(render_data->unk_00 & 0x20)) {
            scratch_page->unk_0C = render_data->unk_08.u8.unk_00;
            scratch_page->unk_10 = render_data->unk_08.u8.unk_01;
            scratch_page->unk_14 = render_data->unk_08.u8.unk_02;
            scratch_page->unk_18 = render_data->unk_08.u8.unk_03;
            if ((render_data->unk_00 ^ scratch_page->unk_28) & 1) {
                flipped_left_x = (0 - ((s32)(0 - sprite_size->unk_4E.s16) / 2)) - scratch_page->unk_AC;
                scratch_page->unk_C0 = flipped_left_x;
                scratch_page->unk_B0 = flipped_left_x;
                right_x = flipped_left_x - sprite_size->unk_4E.u16;
            } else {
                neg_width = 0 - sprite_size->unk_4E.s16;
                left_x = ((s32)(neg_width + (neg_width >> 0x1F)) >> 1) - scratch_page->unk_AC;
                scratch_page->unk_C0 = left_x;
                scratch_page->unk_B0 = left_x;
                coord_offset = (u16)sprite_size->unk_4E.s16;
                right_x = left_x + coord_offset;
            }
            scratch_page->unk_C8 = right_x;
            scratch_page->unk_B8 = right_x;
            if ((render_data->unk_00 ^ scratch_page->unk_28) & 2) {
                flipped_top_y = sprite_size->unk_50 - scratch_page->unk_AE;
                scratch_page->unk_BA = flipped_top_y;
                scratch_page->unk_B2 = flipped_top_y;
                bottom_y = flipped_top_y - sprite_size->unk_50;
                scratch_page->unk_CA = bottom_y;
                scratch_page->unk_C2 = bottom_y;
            } else {
                top_y = (0 - sprite_size->unk_50) - scratch_page->unk_AE;
                scratch_page->unk_BA = top_y;
                scratch_page->unk_B2 = top_y;
                coord_offset = sprite_size->unk_50;
                bottom_y = top_y + coord_offset;
                scratch_page->unk_CA = bottom_y;
                scratch_page->unk_C2 = bottom_y;
            }
            RotTransPers4(&scratch_page->unk_B0, &scratch_page->unk_B8, &scratch_page->unk_C0,
                &scratch_page->unk_C8, &scratch_page->screen[0].word, &scratch_page->screen[1].word,
                &scratch_page->screen[2].word, &scratch_page->screen[3].word, &scratch_page->transform_p,
                &scratch_page->transform_flags);
            packet->unk_08 = scratch_page->screen[0].parts.x + scratch_page->origin.parts.x;
            packet->unk_0A = scratch_page->screen[0].parts.y + scratch_page->origin.parts.y;
            packet->unk_10 = scratch_page->screen[1].parts.x + scratch_page->origin.parts.x;
            packet->unk_12 = scratch_page->screen[1].parts.y + scratch_page->origin.parts.y;
            packet->unk_18 = scratch_page->screen[2].parts.x + scratch_page->origin.parts.x;
            packet->unk_1A = scratch_page->screen[2].parts.y + scratch_page->origin.parts.y;
            corner0_visible = 0;
            packet->unk_20 = scratch_page->screen[3].parts.x + scratch_page->origin.parts.x;
            screen_y3 = scratch_page->screen[3].parts.y + scratch_page->origin.parts.y;
            packet->unk_22 = screen_y3;
            if ((u32)((packet->unk_08 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((packet->unk_0A + 0x20) & 0xFFFF);
                corner0_visible = y_bound < 0x121U;
            }
            corner1_visible = 0;
            if ((u32)((packet->unk_10 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((packet->unk_12 + 0x20) & 0xFFFF);
                corner1_visible = y_bound < 0x121U;
            }
            corner2_visible = 0;
            first_two_visible = corner0_visible | corner1_visible;
            if ((u32)((packet->unk_18 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((packet->unk_1A + 0x20) & 0xFFFF);
                corner2_visible = y_bound < 0x121U;
            }
            corner3_visible = 0;
            first_three_visible = first_two_visible | corner2_visible;
            if ((u32)((packet->unk_20 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((screen_y3 + 0x20) & 0xFFFF);
                corner3_visible = y_bound < 0x121U;
            }
            if ((first_three_visible | corner3_visible) != 0) {
                packet->unk_00.s8.unk_03 = 9;
                sprite->unk_14 = (u16)(sprite->unk_14 & 0x7FFF);
                {
                    u32 texel_count = scratch_page->unk_14;
                    u32 texel_base = scratch_page->unk_0C;
                    texel_count -= 1;
                    uv_right = texel_count + texel_base;
                }
                scratch_page->unk_14 = uv_right;
                if (uv_right & 0x100) {
                    blend_code = uv_right - 1;
                    scratch_page->unk_14 = blend_code;
                }
                {
                    u32 texel_count = scratch_page->unk_18;
                    u32 texel_base = scratch_page->unk_10;
                    texel_count -= 1;
                    uv_right = texel_count + texel_base;
                }
                scratch_page->unk_18 = uv_right;
                if (uv_right & 0x100) {
                    blend_code = uv_right - 1;
                    scratch_page->unk_18 = blend_code;
                }
                scratch_page->unk_18 <<= 8;
                scratch_page->unk_10 <<= 8;
                if (scratch_page->unk_28 & 0x100) {
                    packet->unk_0E = sprite->unk_12;
                } else {
                    packet->unk_0E = (s16)(sprite->unk_12 + render_data->unk_06);
                }
                packet->unk_0C = (s16)((u16)scratch_page->unk_10 + (u16)scratch_page->unk_0C);
                packet->unk_14.s16 = (s16)((u16)scratch_page->unk_10 + (u16)scratch_page->unk_14);
                if (sprite->unk_10 != 0) {
                    field_value = (render_data->unk_04 & 0xFF9F) + sprite->unk_10;
                } else {
                    field_value = render_data->unk_04;
                }
                packet->unk_16 = field_value;
                packet->unk_1C.s16 = (s16)((u16)scratch_page->unk_18 | (u16)scratch_page->unk_0C);
                packet->unk_24.s16 = (u16)scratch_page->unk_18 | (u16)scratch_page->unk_14;
                if ((s16)packet->unk_08 > (s16)packet->unk_20) {
                    right_u = packet->unk_24.u8.unk_24;
                    packet->unk_24.u8.unk_24 = (u8)(right_u + 0xFF);
                    packet->unk_14.u8 = right_u;
                }
                if ((s16)packet->unk_0A > packet->unk_22) {
                    bottom_v = packet->unk_24.u8.unk_25;
                    packet->unk_24.u8.unk_25 = (u8)(bottom_v + 0xFF);
                    packet->unk_1C.u8.unk_1D = bottom_v;
                }
                packet_code = render_data->unk_01;
                sprite->unk_0C.u8.unk_0F = packet_code;
                uv_right = scratch_page->unk_28;
                if (uv_right & 8) {
                    blend_code = uv_right & 4;
                    if (blend_code) {
                        blend_code = packet_code | 2;
                    } else {
                        blend_code = packet_code & 0xFD;
                    }
                    sprite->unk_0C.u8.unk_0F = blend_code;
                }
                packet_addr = (u32)packet & 0xFFFFFF;
                packet->unk_04 = (s32)sprite->unk_0C.s32;
                {
                    u32 *ot = (u32 *)((scratch_page->unk_100 * 4) + scratch_page->unk_24);
                    setaddr(packet, getaddr(ot));
                }
                ot_entry = (s32 *)((scratch_page->unk_100 * 4) + scratch_page->unk_24);
                packet = (T_80170874_S_80DB9000_9 *)((u8 *)packet + 0x28);
                *ot_entry = (*ot_entry & 0xFF000000) | packet_addr;
            }
        } else {
            draw_callback = (void *(*)(void *, void *, void *, void *, void *))render_data->unk_08.void_ptr;
            if (draw_callback != NULL) {
                packet = draw_callback(sprite_size, position, sprite, render_data, packet);
            }
        }
        if ((s8)render_data->unk_00 < 0) {
            break;
        }
        render_data = (T_80170874_S_80DB9000_7 *)((u8 *)render_data + 0xC);
        }
        PopMatrix();
    }
    ((T_80170874_S_80DB9000_6 *)render_state->draw_buffer)->unk_8D0 = packet;
}
