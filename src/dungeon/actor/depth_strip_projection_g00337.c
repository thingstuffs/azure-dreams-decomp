/* Depth strip projection (G00337). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800AA854. */
#include "dungeon/actor/depth_strip_projection_g00337.h"

/* Processes circular segments in both directions and saves the last successful result. */
s32 process_circular_segments(Arg0_800AFBFC *shape, s32 unused, Arg2_800AFBFC *segment) {
    s32 last_result = 0;
    s32 result;
    s16 angle;
    s16 next_angle;
    s16 angle_step;
    s16 start_x;
    s32 end_y;
    s16 coord;
    s16 *scratch = (s16 *)0x1F800000;
    GameWork *gw = &g_game_work;
    State_80083160 *state;
    s16 start_angle;
    void *segment_data;
    s32 rotation;
    u16 flags;
    s32 segment_byte;
    s32 offset_x;
    s32 offset_y;

    state = ((State_80083160 *)gw->draw_buffer);
    last_result = state->value;
    ((ScratchHeader_800AFBFC *)scratch)->state_data = (u8 *)state + 0x8b0;
    segment_data = segment->temp;
    ((ScratchHeader_800AFBFC *)scratch)->segment_data = segment_data;
    offset_x = ((u16)gw->view.view_offset.parts.view_offset_x);
    offset_y = ((u16)gw->view.view_offset.parts.view_offset_y);
    segment_byte = ((u8 *)segment_data)[1];
    flags = segment->flags;
    segment->byte = segment_byte;
    if (flags & 8) {
        if (flags & 4) {
            segment->byte = segment_byte | 2;
        } else {
            segment->byte = segment_byte & 0xfd;
        }
    }

    angle = shape->value;
    rotation = ((u16)gw->view.camera_rotation.parts.viewAngle);
    angle += 0xc00;
    angle -= (rotation + 0x80) & 0xf00;
    angle_step = angle;
    start_angle = angle;

    {
        s32 raw_x;
        s32 raw_y;
        s32 call_value;
        void *call_segment;
        s16 *call_scratch;
        s32 scaled_coord;
        s32 end_x;
        start_x = rcos(angle) * 6 - offset_x;
        scaled_coord = rsin(angle) * 6;
        coord = scaled_coord - offset_y;
        for (;;) {
            next_angle = angle_step;
            next_angle += 0x80;
            angle = next_angle;
            scratch[0x80 / 2] = start_x;
            scratch[0x70 / 2] = start_x;
            scratch[0x82 / 2] = coord;
            scratch[0x72 / 2] = coord;
            raw_x = rcos(angle);
            call_value = angle;
            coord = (raw_x * 6) - offset_x;
            raw_y = rsin(call_value);
            call_scratch = scratch;
            call_value = (s32)shape;
            call_segment = segment;
            end_y = (raw_y * 6) - offset_y;
            scratch[0x88 / 2] = coord;
            scratch[0x78 / 2] = coord;
            scratch[0x8a / 2] = end_y;
            scratch[0x7a / 2] = end_y;
            result = project_depth_strips_and_quads((void *)call_value, call_segment, call_scratch, last_result, 0);
            next_angle += 0x80;
            if (result == 0)
                break;
            last_result = result;
            angle_step = next_angle;
            scratch[0x80 / 2] = coord;
            scratch[0x70 / 2] = coord;
            scratch[0x82 / 2] = end_y;
            scratch[0x72 / 2] = end_y;
            end_x = rcos(next_angle) * 6 - offset_x;
            start_x = end_x;
            scaled_coord = rsin(next_angle) * 6 - offset_y;
            coord = scaled_coord;
            scratch[0x88 / 2] = end_x;
            scratch[0x78 / 2] = end_x;
            scratch[0x8a / 2] = scaled_coord;
            scratch[0x7a / 2] = scaled_coord;
            result = project_depth_strips_and_quads(shape, segment, scratch, last_result, 1);
            if (result == 0)
                break;
            last_result = result;
        }
    }

    {
        s32 raw_x;
        s32 raw_y;
        s32 call_value;
        void *call_segment;
        s16 *call_scratch;
        s32 call_previous;
        s32 scaled_coord;
        s32 end_x;
        angle = start_angle;
        start_x = rcos(angle) * 6 - offset_x;
        coord = rsin(angle) * 6 - offset_y;

        for (;;) {
            s32 segment_end_y;
            next_angle = start_angle;
            next_angle -= 0x80;
            angle = next_angle;
            scratch[0x88 / 2] = start_x;
            scratch[0x78 / 2] = start_x;
            scratch[0x8a / 2] = coord;
            scratch[0x7a / 2] = coord;
            raw_x = rcos(angle);
            call_value = angle;
            coord = raw_x * 6 - offset_x;
            raw_y = rsin(call_value);
            call_scratch = scratch;
            call_previous = last_result;
            scaled_coord = raw_y * 6;
            segment_end_y = scaled_coord - offset_y;
            call_value = (s32)shape;
            call_segment = segment;
            scratch[0x80 / 2] = coord;
            scratch[0x70 / 2] = coord;
            scratch[0x82 / 2] = segment_end_y;
            scratch[0x72 / 2] = segment_end_y;
            result = project_depth_strips_and_quads((void *)call_value, call_segment, call_scratch, call_previous, 1);
            next_angle -= 0x80;
            if (result == 0)
                break;
            last_result = result;
            start_angle = next_angle;
            scratch[0x88 / 2] = coord;
            scratch[0x78 / 2] = coord;
            scratch[0x8a / 2] = segment_end_y;
            scratch[0x7a / 2] = segment_end_y;
            end_x = rcos(next_angle) * 6 - offset_x;
            start_x = end_x;
            scaled_coord = rsin(next_angle) * 6 - offset_y;
            coord = scaled_coord;
            call_scratch = scratch;
            call_value = (s32)shape;
            call_segment = segment;
            call_previous = last_result;
            scratch[0x80 / 2] = end_x;
            scratch[0x70 / 2] = end_x;
            scratch[0x82 / 2] = scaled_coord;
            scratch[0x72 / 2] = scaled_coord;
            next_angle = 0;
            result = project_depth_strips_and_quads((void *)call_value, call_segment, call_scratch, call_previous, next_angle);
            if (result == 0)
                break;
            last_result = result;
        }
    }
    {
        State_80083160 *final_state;
        final_state = ((State_80083160 *)gw->draw_buffer);
        result = 0;
        final_state->value = last_result;
    }
    return result;
}

/* Projects depth strips and queues visible textured quad pairs with distance shading. */
s32 project_depth_strips_and_quads(S_800AFFB4_0 *origin, void *unused, S_800AFFB4_1 *render_data_in, u8 *packet_buffer, s16 texture_arg) {
    s32 depth_step;
    u32 cached_v;
    s32 shade_uv;
    s32 shade_uv_2;
    s32 info_byte;
    s32 shade_u;
    s32 clamp_vertex;
    s32 texture_height;
    s32 coord_bits;
    s32 vertex_value;
    s32 entry_v;
    s32 x_in_bounds;
    s32 near_mid_x;
    s32 texture_right;
    s32 far_mid_x;
    s32 near_mid_y;
    s32 far_mid_y;
    s32 visible_left;
    s32 visible_near;
    s32 visible_strips;
    TwelveByteEntry *texture_entry;
    s32 quad_index;
    s32 strip_index;
    s32 visible_right;
    u16 screen_y;
    u16 texture_index;
    u16 shade_offset;

    (void)unused;
    visible_strips = 0;
    texture_index = texture_arg;
    shade_offset = origin->unk_08.s >= 0xE00;
    entry_v = origin->unk_08.u;
    coord_bits = entry_v - 0x6200;
    vertex_value = entry_v - 0x5400;
    render_data_in->unk_7C = coord_bits;
    render_data_in->unk_74 = coord_bits;
    render_data_in->unk_8C = vertex_value;
    render_data_in->unk_84 = vertex_value;
    for (strip_index = 0; strip_index < 0xE; strip_index++) {
        render_data_in->unk_74 += 0xE00;
        render_data_in->unk_7C += 0xE00;
        render_data_in->unk_84 += 0xE00;
        render_data_in->unk_8C += 0xE00;
        if (func_80065610((u8 *)render_data_in + 0x70, (u8 *)render_data_in + 0x78,
                (u8 *)render_data_in + 0x80, (u8 *)render_data_in + 0x88,
                (u8 *)render_data_in + 0xF0, (u8 *)render_data_in + 0xF4,
                (u8 *)render_data_in + 0xF8, (u8 *)render_data_in + 0xFC,
                (u8 *)render_data_in + 0x90, (u8 *)render_data_in + 0xC0,
                (u8 *)render_data_in + 0x94) > 0) {
            visible_near = 0;
            if ((u32)((render_data_in->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = render_data_in->unk_F0.at02.v + 0x20;
                visible_near = screen_y < 0x121U;
            }
            visible_right = 0;
            if ((u32)((render_data_in->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = render_data_in->unk_F4.at02.v + 0x20;
                visible_right = screen_y < 0x121U;
            }
            visible_left = 0;
            x_in_bounds = (u32)((render_data_in->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U;
            visible_near |= visible_right;
            if (x_in_bounds) {
                screen_y = render_data_in->unk_F8.at02.v + 0x20;
                visible_left = screen_y < 0x121U;
            }
            visible_right = 0;
            x_in_bounds = (u32)((render_data_in->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U;
            shade_uv_2 = visible_near | visible_left;
            visible_left = shade_uv_2;
            if (x_in_bounds) {
                screen_y = render_data_in->unk_FC.at02.v + 0x20;
                visible_right = screen_y < 0x121U;
            }
            if ((visible_left | visible_right) != 0) {
                ((StripPacket *)packet_buffer)->near_quad.unk_04 = render_data_in->unk_F0.at00u.v;
                ((StripPacket *)packet_buffer)->near_quad.unk_1C = render_data_in->unk_F8.at00u.v;
                ((StripPacket *)packet_buffer)->near_quad.unk_44 = render_data_in->unk_F4.at00u.v;
                ((StripPacket *)packet_buffer)->far_quad.unk_10 = render_data_in->unk_FC.at00u.v;
                near_mid_x = (render_data_in->unk_F0.at00p.v
                    + render_data_in->unk_F4.at00p.v) >> 1;
                ((StripPacket *)packet_buffer)->near_quad.unk_38 = near_mid_x;
                ((StripPacket *)packet_buffer)->near_quad.unk_10 = near_mid_x;
                far_mid_x = (render_data_in->unk_F8.at00p.v
                    + render_data_in->unk_FC.at00p.v) >> 1;
                ((StripPacket *)packet_buffer)->far_quad.unk_04 = far_mid_x;
                ((StripPacket *)packet_buffer)->near_quad.unk_28 = far_mid_x;
                near_mid_y = (render_data_in->unk_F0.at02u.v
                    + render_data_in->unk_F4.at02u.v) >> 1;
                ((StripPacket *)packet_buffer)->near_quad.unk_3A = near_mid_y;
                ((StripPacket *)packet_buffer)->near_quad.unk_12 = near_mid_y;
                far_mid_y = (render_data_in->unk_F8.at02u.v
                    + render_data_in->unk_FC.at02u.v) >> 1;
                ((StripPacket *)packet_buffer)->far_quad.unk_06 = far_mid_y;
                ((StripPacket *)packet_buffer)->near_quad.unk_2A = far_mid_y;
                depth_step = (s16)render_data_in->unk_74 % 3584;
                render_data_in->unk_90.s32 = depth_step;
                if (depth_step < 0) {
                    depth_step += 0xFF;
                }
                depth_step >>= 8;
                render_data_in->unk_90.s32 = depth_step;
                screen_y = shade_offset;
                if (screen_y != 0) {
                    render_data_in->unk_90.s32 = depth_step + 0x10;
                }
                shade_uv = 0x80;
                vertex_value = render_data_in->unk_90.u16;
                coord_bits = strip_index << 4;
                vertex_value += coord_bits;
                shade_u = 0xE0 - vertex_value;
                texture_height = (s16)shade_u;
                clamp_vertex = shade_u;
                if (texture_height < 0x81) {
                    shade_uv = shade_u;
                    if (texture_height < 0) {
                        shade_uv = 0;
                    }
                }
                coord_bits = clamp_vertex - 0x10;
                clamp_vertex = coord_bits;
                coord_bits <<= 0x10;
                ((StripPacket *)packet_buffer)->near_quad.unk_02 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_0E = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_42 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_36 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_01 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_0D = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_41 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_35 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_00 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_0C = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_40 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_34 = shade_uv;
                shade_uv = coord_bits >> 0x10;
                if (shade_uv >= 0x81) {
                    clamp_vertex = 0x80;
                } else {
                    if (shade_uv < 0) {
                        clamp_vertex = 0;
                    }
                }
                quad_index = 0;
                ((StripPacket *)packet_buffer)->near_quad.unk_1A = clamp_vertex;
                ((StripPacket *)packet_buffer)->near_quad.unk_26 = clamp_vertex;
                ((StripPacket *)packet_buffer)->far_quad.unk_0E = clamp_vertex;
                ((StripPacket *)packet_buffer)->far_quad.unk_02 = clamp_vertex;
                ((StripPacket *)packet_buffer)->near_quad.unk_19 = clamp_vertex;
                ((StripPacket *)packet_buffer)->near_quad.unk_25 = clamp_vertex;
                ((StripPacket *)packet_buffer)->far_quad.unk_0D = clamp_vertex;
                ((StripPacket *)packet_buffer)->far_quad.unk_01 = clamp_vertex;
                ((StripPacket *)packet_buffer)->near_quad.unk_18 = clamp_vertex;
                ((StripPacket *)packet_buffer)->near_quad.unk_24 = clamp_vertex;
                ((StripPacket *)packet_buffer)->far_quad.unk_0C = clamp_vertex;
                ((StripPacket *)packet_buffer)->far_quad.unk_00 = clamp_vertex;
                texture_entry = (TwelveByteEntry *)render_data_in->unk_118 + (((strip_index & 1) << 1) + ((s16)texture_index << 2));
                do {
                    SetPolyGT4(packet_buffer);
                    info_byte = ((S_800AFFB4_3 *)((u8 *)texture_entry + 4))->unk_04;
                    render_data_in->unk_08.s32 = info_byte;
                    info_byte = ((S_800AFFB4_3 *)((u8 *)texture_entry + 4))->unk_05;
                    render_data_in->unk_0C = info_byte;
                    shade_u = render_data_in->unk_08.s32;
                    info_byte = ((S_800AFFB4_3 *)((u8 *)texture_entry + 4))->unk_06;
                    render_data_in->unk_10.s32 = info_byte;
                    cached_v = render_data_in->unk_0C;
                    shade_uv = cached_v;
                    info_byte = ((S_800AFFB4_3 *)((u8 *)texture_entry + 4))->unk_07;
                    render_data_in->unk_14.s32 = info_byte;
                    vertex_value = cached_v;
                    shade_uv <<= 8;
                    render_data_in->unk_0C = shade_uv;
                    texture_height = render_data_in->unk_14.s32;
                    texture_right = render_data_in->unk_10.s32 + shade_u;
                    vertex_value += texture_height;
                    vertex_value <<= 8;
                    render_data_in->unk_14.s32 = vertex_value;
                    vertex_value = render_data_in->unk_08.s32;
                    shade_u = (s32)packet_buffer;
                    render_data_in->unk_10.s32 = texture_right;
                    coord_bits = ((S_800AFFB4_3 *)((u8 *)texture_entry + 4))->unk_02;
                    shade_uv += vertex_value;
                    coord_bits <<= 0x10;
                    shade_uv |= coord_bits;
                    ((StripQuad *)packet_buffer)->uv0 = shade_uv;
                    coord_bits = render_data_in->unk_0C;
                    shade_uv = render_data_in->unk_10.s32;
                    vertex_value = ((S_800AFFB4_3 *)((u8 *)texture_entry + 4))->unk_00;
                    coord_bits += shade_uv;
                    vertex_value <<= 0x10;
                    coord_bits |= vertex_value;
                    ((StripQuad *)packet_buffer)->uv1.word = coord_bits;
                    coord_bits = render_data_in->unk_14.u16;
                    vertex_value = render_data_in->unk_08.u16;
                    coord_bits += vertex_value;
                    ((StripQuad *)packet_buffer)->uv2.half = coord_bits;
                    vertex_value = render_data_in->unk_14.u16;
                    coord_bits = ((StripQuad *)packet_buffer)->uv1.u;
                    shade_uv = render_data_in->unk_10.u16;
                    coord_bits -= 1;
                    vertex_value += shade_uv;
                    ((StripQuad *)packet_buffer)->uv1.u = coord_bits;
                    ((StripQuad *)packet_buffer)->uv3.half = vertex_value;
                    coord_bits = ((StripQuad *)packet_buffer)->uv3.b.u;
                    vertex_value = ((StripQuad *)packet_buffer)->uv2.b.v;
                    coord_bits -= 1;
                    vertex_value -= 1;
                    ((StripQuad *)packet_buffer)->uv3.b.u = coord_bits;
                    ((StripQuad *)packet_buffer)->uv2.b.v = vertex_value;
                    coord_bits = ((StripQuad *)packet_buffer)->uv3.b.v;
                    coord_bits -= 1;
                    ((StripQuad *)packet_buffer)->uv3.b.v = coord_bits;
                    shade_uv = (u32)(texture_entry - (TwelveByteEntry *)render_data_in->unk_118) / 12;
                    texture_entry += 1;
                    AddPrim(render_data_in->unk_20 + ((u32)shade_uv * 4),
                        (void *)shade_u, texture_height);
                    packet_buffer += 0x34;
                    quad_index += 1;
                } while (quad_index < 2);
                visible_strips += 1;
            }
        }
    }
    coord_bits = 0;
    if (visible_strips != 0) {
        coord_bits = (s32)packet_buffer;
    }
    return coord_bits;
}
