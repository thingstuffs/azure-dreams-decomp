/* Textured resource strips (G00571).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A6420, CL:town/func_800A6A78, PD:town/engine:80100D88, PD:town/engine:80100D8A.
 */
#include "town/map/textured_resource_strips_g00571.h"
#include "shared/object_node.h"

/* Process linked states until a nonzero signed 16-bit result or the end of the chain. */
s32 process_linked_state_chain(void *initial_state) {
    u8 *state = initial_state;
    u8 *carrier2;
    s32 carrier1;
    u16 result;

    for (;;) {
        result = emit_bidirectional_angular_segments((S_800A3B80_3 *)state, carrier1, carrier2);
        if ((result << 0x10) != 0) {
            return (s16)result;
        }

        carrier2 = *(u8 **)(state - 8);
        if (carrier2 == 0) {
            return (s16)result;
        }

        state = carrier2 + 0x20;
        carrier1 = *(s32 *)(carrier2 + 8);
        carrier2 = (u8 *)(u32)*(s32 *)(carrier2 + 0xC);
    }
}

/* Emits segments in both angular directions and updates the town output pointer. */
s32 emit_bidirectional_angular_segments(S_800A3B80_3 *object, s32 unused, void *context)
{

    Scratch *scratch;
    s16 coord_y;
    s32 coord_x;
    s32 coord_value;
    s32 angle_or_coord;
    s32 result;
    s32 stepped;
    s32 view_angle;
    GameWork *global_base;
    void *town;
    void *output;
    void *next_output;
    S_800A3B80_5 *end_town;
    S_800A3B80_1 *context_view;
    S_800A3B80_2 *context_data;
    u16 origin_y;
    u16 origin_x;
    s32 forward_angle;
    s32 reverse_angle;
    s32 next_angle;

    scratch = (Scratch *)0x1F800000;
    global_base = &g_game_work;
    town = g_game_work.draw_buffer;
    output = ((S_800A3B80_0 *)town)->unk_8D0;
    scratch->data20 = (u8 *)town + 0x8B0;
    origin_y = D_80100D88;
    origin_x = D_80100D8A;
    context_view = context;
    context_data = context_view->unk_08;
    scratch->data118 = context_data;
    context_view->unk_0F = context_data->unk_01;

    angle_or_coord = object->unk_06;
    view_angle = ((u16)g_game_work.view.camera_rotation.parts.viewAngle);
    angle_or_coord += 0xC00;
    view_angle = (view_angle + 0x80) & 0xF00;
    angle_or_coord -= view_angle;
    reverse_angle = angle_or_coord;
    forward_angle = angle_or_coord;
    angle_or_coord <<= 16;
    angle_or_coord >>= 16;
    coord_value = rcos(angle_or_coord) * 6;
    coord_y = coord_value - origin_y;
    coord_value = rsin(angle_or_coord) * 6;
    coord_x = coord_value - origin_x;

forward_segment:
    scratch->data80 = coord_y;
    scratch->data70 = coord_y;
    {
        s32 shifted = coord_x << 16;

        angle_or_coord = shifted >> 16;
    }
    if (object->unk_0C != 0) {
        coord_value = angle_or_coord -
            (rsin(((s32)(forward_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    } else {
        coord_value = angle_or_coord +
            (rsin(((s32)(forward_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    }
    stepped = forward_angle + 0x80;
    forward_angle = stepped;
    stepped <<= 16;
    next_angle = stepped >> 16;
    scratch->data82 = coord_value;
    scratch->data72 = coord_value;
    coord_value = rcos(next_angle);
    angle_or_coord = coord_value << 1;
    angle_or_coord += coord_value;
    angle_or_coord <<= 1;
    angle_or_coord -= origin_y;
    coord_y = angle_or_coord;
    coord_value = rsin(next_angle) * 6;
    scratch->data88 = angle_or_coord;
    scratch->data78 = angle_or_coord;
    coord_value -= origin_x;
    coord_x = coord_value;
    coord_value <<= 16;
    angle_or_coord = coord_value >> 16;
    if (object->unk_0C != 0) {
        result = angle_or_coord -
            (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    } else {
        result = angle_or_coord +
            (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    }
    scratch->data8A = result;
    scratch->data7A = result;
    next_output = project_visible_textured_strips(object, context, scratch, output, 0);
    if (next_output != 0) {
        output = next_output;

        scratch->data80 = coord_y;
        scratch->data70 = coord_y;
        {
            s32 shifted = coord_x << 16;

            angle_or_coord = shifted >> 16;
        }
        if (object->unk_0C != 0) {
            coord_value = angle_or_coord -
                (rsin(((s32)(forward_angle << 16) >> 14) +
                               (object->unk_00 << 5)) >> 1);
        } else {
            coord_value = angle_or_coord +
                (rsin(((s32)(forward_angle << 16) >> 14) +
                               (object->unk_00 << 5)) >> 1);
        }
        stepped = forward_angle + 0x80;
        forward_angle = stepped;
        stepped <<= 16;
        next_angle = stepped >> 16;
        scratch->data82 = coord_value;
        scratch->data72 = coord_value;
        coord_value = rcos(next_angle);
        angle_or_coord = coord_value << 1;
        angle_or_coord += coord_value;
        angle_or_coord <<= 1;
        angle_or_coord -= origin_y;
        coord_y = angle_or_coord;
        coord_value = rsin(next_angle) * 6;
        scratch->data88 = angle_or_coord;
        scratch->data78 = angle_or_coord;
        coord_value -= origin_x;
        coord_x = coord_value;
        coord_value <<= 16;
        angle_or_coord = coord_value >> 16;
        if (object->unk_0C != 0) {
            result = angle_or_coord -
                (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
        } else {
            result = angle_or_coord +
                (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
        }
        scratch->data8A = result;
        scratch->data7A = result;
        next_output = project_visible_textured_strips(object, context, scratch, output, 1);
        if (next_output != 0) {
            output = next_output;
            goto forward_segment;
        }
    }
    angle_or_coord = reverse_angle;
    angle_or_coord <<= 16;
    angle_or_coord >>= 16;
    coord_value = rcos(angle_or_coord) * 6;
    coord_y = coord_value - origin_y;
    coord_value = rsin(angle_or_coord) * 6;
    coord_x = coord_value - origin_x;

reverse_segment:
    scratch->data88 = coord_y;
    scratch->data78 = coord_y;
    {
        s32 shifted = coord_x << 16;

        angle_or_coord = shifted >> 16;
    }
    if (object->unk_0C != 0) {
        coord_value = angle_or_coord -
            (rsin(((s32)(reverse_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    } else {
        coord_value = angle_or_coord +
            (rsin(((s32)(reverse_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    }
    stepped = reverse_angle - 0x80;
    reverse_angle = stepped;
    stepped <<= 16;
    next_angle = stepped >> 16;
    scratch->data8A = coord_value;
    scratch->data7A = coord_value;
    coord_value = rcos(next_angle);
    angle_or_coord = coord_value << 1;
    angle_or_coord += coord_value;
    angle_or_coord <<= 1;
    angle_or_coord -= origin_y;
    coord_y = angle_or_coord;
    coord_value = rsin(next_angle) * 6;
    scratch->data80 = angle_or_coord;
    scratch->data70 = angle_or_coord;
    coord_value -= origin_x;
    coord_x = coord_value;
    coord_value <<= 16;
    angle_or_coord = coord_value >> 16;
    if (object->unk_0C != 0) {
        result = angle_or_coord -
            (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    } else {
        result = angle_or_coord +
            (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    }
    scratch->data82 = result;
    scratch->data72 = result;
    next_output = project_visible_textured_strips(object, context, scratch, output, 1);
    if (next_output != 0) {
        output = next_output;

        scratch->data88 = coord_y;
        scratch->data78 = coord_y;
        {
            s32 shifted = coord_x << 16;

            angle_or_coord = shifted >> 16;
        }
        if (object->unk_0C != 0) {
            coord_value = angle_or_coord -
                (rsin(((s32)(reverse_angle << 16) >> 14) +
                               (object->unk_00 << 5)) >> 1);
        } else {
            coord_value = angle_or_coord +
                (rsin(((s32)(reverse_angle << 16) >> 14) +
                               (object->unk_00 << 5)) >> 1);
        }
        stepped = reverse_angle - 0x80;
        reverse_angle = stepped;
        stepped <<= 16;
        next_angle = stepped >> 16;
        scratch->data8A = coord_value;
        scratch->data7A = coord_value;
        coord_value = rcos(next_angle);
        angle_or_coord = coord_value << 1;
        angle_or_coord += coord_value;
        angle_or_coord <<= 1;
        angle_or_coord -= origin_y;
        coord_y = angle_or_coord;
        coord_value = rsin(next_angle) * 6;
        scratch->data80 = angle_or_coord;
        scratch->data70 = angle_or_coord;
        coord_value -= origin_x;
        coord_x = coord_value;
        coord_value <<= 16;
        angle_or_coord = coord_value >> 16;
        if (object->unk_0C != 0) {
            result = angle_or_coord -
                (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
        } else {
            result = angle_or_coord +
                (rsin((next_angle * 4) + (object->unk_00 << 5)) >> 1);
        }
        scratch->data82 = result;
        scratch->data72 = result;
        next_output = project_visible_textured_strips(object, context, scratch, output, 0);
        if (next_output != 0) {
            output = next_output;
            goto reverse_segment;
        }
    }
    end_town = global_base->draw_buffer;
    end_town->unk_8D0 = output;
    return 0;
}

/* Projects and draws visible textured strips, returning the next free primitive. */
void *project_visible_textured_strips(void *origin, void *render_flags, void *draw_state, void *prim_buffer, u16 texture_index) {
    s32 buckets[2];
    u16 texture_id;
    u16 base_shade;
    u16 screen_y;
    s16 strip_shade;
    s32 strip_offset;
    s16 shade;
    s32 uv_top;
    register s32 uv_value;
    register s32 uv_value_2;
    s32 bucket_offset;
    s32 bucket;
    s32 uv_left;
    s32 uv_height;
    s32 coord_value;
    s32 bottom_x;
    s32 top_y;
    s32 bottom_y;
    s32 third_visible;
    s32 first_three_visible;
    s32 first_pair_visible;
    s32 corner_visible;
    u16 origin_x;
    u16 uv_bottom;
    u16 uv_right;
    s32 right_u;
    u16 bottom_right_uv;
    u16 right_x;
    u16 left_x;
    u32 bucket_index;
    void *right_quad;
    void *draw_mode;
    void *right_colors;
    void *buffer_end;
    void *packet_cursor;
    void *entry_cursor;
    s32 half_index;
    s32 texture_entry;
    s32 strip_index;
    s32 *bucket_list;
    s32 *bucket_slot;
    s32 bucket_addr;
    s32 visible_count;

    visible_count = 0;
    strip_index = 0;
    texture_id = texture_index;
    bucket_list = buckets;
    origin_x = ((S_800A41D8_0 *)origin)->unk_08;
    left_x = origin_x - 0x6200;
    right_x = origin_x - 0x5400;
    base_shade = ((S_800A41D8_0 *)origin)->unk_16;
    ((S_800A41D8_1 *)draw_state)->unk_7C = left_x;
    ((S_800A41D8_1 *)draw_state)->unk_74 = left_x;
    ((S_800A41D8_1 *)draw_state)->unk_8C = right_x;
    ((S_800A41D8_1 *)draw_state)->unk_84 = right_x;
    do {
        ((S_800A41D8_1 *)draw_state)->unk_74 = (u16) (((S_800A41D8_1 *)draw_state)->unk_74 + 0xE00);
        ((S_800A41D8_1 *)draw_state)->unk_7C = (u16) (((S_800A41D8_1 *)draw_state)->unk_7C + 0xE00);
        ((S_800A41D8_1 *)draw_state)->unk_84 = (u16) (((S_800A41D8_1 *)draw_state)->unk_84 + 0xE00);
        ((S_800A41D8_1 *)draw_state)->unk_8C = (u16) (((S_800A41D8_1 *)draw_state)->unk_8C + 0xE00);
        if (func_80065610(draw_state + 0x70, draw_state + 0x78, draw_state + 0x80, draw_state + 0x88,
            draw_state + 0xF0, draw_state + 0xF4, draw_state + 0xF8, draw_state + 0xFC, draw_state + 0x90,
            draw_state + 0xC0, draw_state + 0x94) > 0) {
            first_pair_visible = 0;
            if ((u32) ((((S_800A41D8_1 *)draw_state)->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)draw_state)->unk_F0.at02.v + 0x20;
                first_pair_visible = screen_y < 0x121U;
            }
            corner_visible = 0;
            if ((u32) ((((S_800A41D8_1 *)draw_state)->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)draw_state)->unk_F4.at02.v + 0x20;
                corner_visible = screen_y < 0x121U;
            }
            third_visible = 0;
            first_pair_visible |= corner_visible;
            if ((u32) ((((S_800A41D8_1 *)draw_state)->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)draw_state)->unk_F8.at02.v + 0x20;
                third_visible = screen_y < 0x121U;
            }
            corner_visible = 0;
            first_three_visible = first_pair_visible | third_visible;
            if ((u32) ((((S_800A41D8_1 *)draw_state)->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)draw_state)->unk_FC.at02.v + 0x20;
                corner_visible = screen_y < 0x121U;
            }
            if ((first_three_visible | corner_visible) != 0) {
                right_quad = prim_buffer + 0x28;
                ((S_800A41D8_2 *)prim_buffer)->unk_08 = ((S_800A41D8_1 *)draw_state)->unk_F0.at00u.v;
                ((S_800A41D8_2 *)prim_buffer)->unk_18 = ((S_800A41D8_1 *)draw_state)->unk_F8.at00u.v;
                ((S_800A41D8_2 *)prim_buffer)->unk_38 = ((S_800A41D8_1 *)draw_state)->unk_F4.at00u.v;
                ((S_800A41D8_2 *)prim_buffer)->unk_48 = ((S_800A41D8_1 *)draw_state)->unk_FC.at00u.v;
                coord_value = (s32) ((s16) ((S_800A41D8_1 *)draw_state)->unk_F0.at00.v
                    + (s16) ((S_800A41D8_1 *)draw_state)->unk_F4.at00.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_08 = (s16) coord_value;
                ((S_800A41D8_2 *)prim_buffer)->unk_10 = (s16) coord_value;
                bottom_x = (s32) ((s16) ((S_800A41D8_1 *)draw_state)->unk_F8.at00.v
                    + (s16) ((S_800A41D8_1 *)draw_state)->unk_FC.at00.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_18 = (s16) bottom_x;
                ((S_800A41D8_2 *)prim_buffer)->unk_20 = (s16) bottom_x;
                top_y = (s32) ((s16) ((S_800A41D8_1 *)draw_state)->unk_F0.at02.v
                    + (s16) ((S_800A41D8_1 *)draw_state)->unk_F4.at02.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_0A = (s16) top_y;
                ((S_800A41D8_2 *)prim_buffer)->unk_12 = (s16) top_y;
                bottom_y = (s32) ((s16) ((S_800A41D8_1 *)draw_state)->unk_F8.at02.v
                    + (s16) ((S_800A41D8_1 *)draw_state)->unk_FC.at02.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_1A = (s16) bottom_y;
                ((S_800A41D8_2 *)prim_buffer)->unk_22 = (s16) bottom_y;
                strip_offset = (s16) ((S_800A41D8_1 *)draw_state)->unk_74 % 3584;
                ((S_800A41D8_1 *)draw_state)->unk_90 = (s32) strip_offset;
                coord_value = (strip_offset / 256);
                ((S_800A41D8_1 *)draw_state)->unk_90 = coord_value;
                strip_shade = (base_shade + (strip_index * 0xE)) - 0x40;
                shade = 0x80;
                if (strip_shade < 0x81) {
                    shade = strip_shade;
                    if (strip_shade < 0) {
                        shade = 0;
                    }
                }
                half_index = 0;
                right_colors = prim_buffer + 0x28;
                ((S_800A41D8_2 *)prim_buffer)->unk_06 = (s8) shade;
                ((S_800A41D8_4 *)right_colors)->unk_06 = (s8) shade;
                ((S_800A41D8_2 *)prim_buffer)->unk_05 = (s8) shade;
                ((S_800A41D8_4 *)right_colors)->unk_05 = (s8) shade;
                ((S_800A41D8_2 *)prim_buffer)->unk_04 = (s8) shade;
                ((S_800A41D8_2 *)prim_buffer)->unk_2C = (s8) shade;
                texture_entry = ((S_800A41D8_1 *)draw_state)->unk_118 + ((((strip_index & 1) * 2) + ((s32) (texture_id
                    << 0x10) >> 0xE)) * 0xC);
                do {
                    SetPolyFT4(prim_buffer);
                    ((S_800A41D8_5 *)prim_buffer)->unk_07 =
                        (u8) (((S_800A41D8_5 *)prim_buffer)->unk_07
                        | (((S_800A41D8_6 *)render_flags)->unk_0F & 2));
                    ((S_800A41D8_1 *)draw_state)->unk_08.n = (s32) ((S_800A41D8_7 *)texture_entry)->unk_08;
                    ((S_800A41D8_1 *)draw_state)->unk_0C.n = (s32) ((S_800A41D8_7 *)texture_entry)->unk_09;
                    uv_left = ((S_800A41D8_1 *)draw_state)->unk_08.v;
                    uv_top = ((S_800A41D8_1 *)draw_state)->unk_0C.v;
                    ((S_800A41D8_1 *)draw_state)->unk_10 = (s32) ((S_800A41D8_7 *)texture_entry)->unk_0A;
                    uv_value = uv_top;
                    ((S_800A41D8_1 *)draw_state)->unk_14.n = (s32) ((S_800A41D8_7 *)texture_entry)->unk_0B;
                    uv_top <<= 8;
                    ((S_800A41D8_1 *)draw_state)->unk_0C.n = uv_top;
                    uv_height = ((S_800A41D8_1 *)draw_state)->unk_14.v;
                    uv_value += uv_height;
                    uv_value <<= 8;
                    ((S_800A41D8_1 *)draw_state)->unk_14.n = uv_value;
                    ((S_800A41D8_1 *)draw_state)->unk_10 = (s32) (((S_800A41D8_1 *)draw_state)->unk_10 + uv_left);
                    uv_value_2 = ((S_800A41D8_1 *)draw_state)->unk_08.v;
                    ((S_800A41D8_2 *)prim_buffer)->uv_0 = (s32) ((uv_top + uv_value_2)
                        | (((S_800A41D8_7 *)texture_entry)->unk_06 << 0x10));
                    ((S_800A41D8_2 *)prim_buffer)->uv_1 = (s32) ((((S_800A41D8_1 *)draw_state)->unk_0C.n
                        + ((S_800A41D8_1 *)draw_state)->unk_10) | (((S_800A41D8_7 *)texture_entry)->unk_04 << 0x10));
                    ((S_800A41D8_2 *)prim_buffer)->uv_2 = (s16) ((u16) ((S_800A41D8_1 *)draw_state)->unk_14.n
                        + (u16) ((S_800A41D8_1 *)draw_state)->unk_08.n);
                    right_u = (u8)(((S_800A41D8_5 *)prim_buffer)->unk_14 - 1);
                    uv_bottom = (u16) ((S_800A41D8_1 *)draw_state)->unk_14.n;
                    uv_right = (u16) ((S_800A41D8_1 *)draw_state)->unk_10;
                    bottom_right_uv = uv_bottom + uv_right;
                    ((S_800A41D8_2 *)prim_buffer)->uv_3 = (s16) bottom_right_uv;
                    do {
                        ((S_800A41D8_5 *)prim_buffer)->unk_14 = (u8) right_u;
                    } while (0);
                    ((S_800A41D8_5 *)prim_buffer)->unk_24 =
                        (u8) (((S_800A41D8_5 *)prim_buffer)->unk_24 - 1);
                    ((S_800A41D8_5 *)prim_buffer)->unk_1D =
                        (u8) (((S_800A41D8_5 *)prim_buffer)->unk_1D - 1);
                    ((S_800A41D8_5 *)prim_buffer)->unk_25 = (u8) (((S_800A41D8_5 *)prim_buffer)->unk_25 - 1);
                    AddPrim(((S_800A41D8_1 *)draw_state)->unk_20
                        + (((u32) ((s32) (0 - ((texture_entry - ((S_800A41D8_1 *)draw_state)->unk_118) * 0x55555555))
                        >> 2) / 12U) * 4), prim_buffer);
                    bucket_index = (u32) ((s32) (0 - ((texture_entry
                        - ((S_800A41D8_1 *)draw_state)->unk_118) * 0x55555555)) >> 2) / 12U;
                    prim_buffer += 0x28;
                    bucket_offset = half_index * 4;
                    half_index += 1;
                    bucket_slot = (s32 *)(bucket_offset + (s32) bucket_list);
                    texture_entry += 0xC;
                    bucket_addr = ((S_800A41D8_1 *)draw_state)->unk_20;
                    bucket_addr += bucket_index * 4;
                    *bucket_slot = bucket_addr;
                } while (half_index < 2);
                packet_cursor = prim_buffer;
                half_index = 0;
                entry_cursor = bucket_list;
                do {
                    SetDrawMode(packet_cursor, 1, 0, GetTPage(0, 0, 0x140, 0) & 0xFFFF, 0);
                    draw_mode = packet_cursor;
                    packet_cursor += 0xC;
                    bucket = *(s32 *)entry_cursor;
                    entry_cursor += 4;
                    half_index += 1;
                    AddPrim(bucket, draw_mode);
                } while (half_index < 2);
                prim_buffer = packet_cursor;
                visible_count += 1;
            }
        }
        strip_index += 1;
    } while (strip_index < 0xE);
    buffer_end = 0;
    if (visible_count != 0) {
        buffer_end = prim_buffer;
    }
    return buffer_end;
}

/* Creates an object with the selected resource and initializes its display and state. */
void create_resource_display_object(s16 resource_index) {

    ObjectNodeHeader *object;
    S_800A47A8_3 *object_state;
    S_800A47A8_1 *component;
    SpriteFrameState *scale;

    object = allocate_flagged_object_node(0x12);
    if (object != NULL) {
        object->unk_10 = D_800A3918;
        register_node(object, D_800A3B1C);
        object->sprite->source = D_800D0C40[resource_index];
        component = object->sprite;
        component->unk_0E = 0xE0;
        component->unk_0D = 0xE0;
        component->unk_0C = 0xE0;
        scale = object->sprite;
        scale->scale_y = 0x1000;
        scale->scale_x = 0x1000;
        component = object->position;
        ((LargeS16 *)&D_80100D88)->value = 0;
        component->unk_02 = 0;
        component = object->position;
        ((LargeS16 *)&D_80100D8A)->value = 0;
        component->unk_06 = 0;
        component = object->position;
        component->unk_0A = 0x4000;
        object_state = ((void *)object) + 0x20;
        object_state->unk_0C = resource_index;
        object_state->unk_02 = 0;
        object_state->unk_12 = 0;
        object_state->unk_14 = 0x80;
    }
}
