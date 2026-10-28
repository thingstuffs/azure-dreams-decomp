#include "shared/sprite_frame_state.h"
#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Textured strip rendering, shaded particles, timed fades, and a traveling effect sequence. */
#include "shared/object_node.h"
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"
#include "shared/object_flags.h"
void (*const dungeon_1924800_entry)(S_func_81905FD0_1 *, S_func_81905FD0_2 *, S_func_81905FD0_3 *) = update_traveling;
const u16 strip_texture_rect[4] = {832,256,96,84};
const u16 strip_small_texture_rect[4] = {832,340,4,4};
const s16 strip_direction_steps[8][2] = {{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,-32},{0,-32},{32,-32}};

#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/* Apply a chance-based effect that halves the entity counter and reports the result. */
void try_halve_actor_counter(u8 *entity, s32 chance, void *unused_context) {
    s32 roll;
    void *effect_result;
    s32 chance_value;
    s32 removed_count;
    s32 roll_remainder;
    s32 passes_chance;
    u8 *effect_input;

    if (try_trigger_target_record_effect(entity, 2, unused_context) != 0) {
        return;
    }

    roll = generate_random_value() & 0xffff;
    if (entity[3] != 0) {
        roll_remainder = roll % entity[3];   /* retail rejoins the common path at +0xBC here */
    } else {
        roll_remainder = 0;
    }
    chance_value = chance & 0xff;
    passes_chance = roll_remainder < (chance_value << 5);
    effect_input = (u8 *)roll;
    if (!passes_chance) {
        effect_input = entity;
        if (chance_value != 0xff) {
            adjust_source_value_and_finalize(effect_input, counter_halve_failed_message);
            create_actor_value_popup(0x53, entity, -1, 1);
            return;
        }
    }
    if (entity[0x27] >= 2) {
        removed_count = (entity[0x27] + 1) >> 1;
        entity[0x27] -= removed_count;
        {
            void *message_arg;
            s32 format_code;
            void *result_arg;

            message_arg = get_unused_text_buffer(effect_input, chance_value);
            format_code = 8;
            result_arg = message_arg;
            effect_result = result_arg;
            message_arg = write_text_byte_and_advance(format_code, result_arg);
            message_arg = append_entity_display_text(entity, message_arg);
            message_arg = expand_text_control_codes(counter_halved_message, message_arg);
            clear_byte_and_advance(message_arg);
        }
        display_text_with_fullwidth_adjustment(effect_result);
        create_actor_value_popup(0x53, entity, removed_count, 1);   /* retail jumps to the shared call at +0x16C */
        return;
    }

    effect_input = entity;
    adjust_source_value_and_finalize(effect_input, counter_halve_failed_message);
    create_actor_value_popup(0x53, entity, -1, 1);
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"
/* cfail-repair: tf7-phase1-cache-v3 */

#define D_FIELD(type_ptr, offset) (*(type_ptr)(((u8 *)(&g_game_work)) + (offset)))
#define D_LITERAL(type_ptr, offset) (*(type_ptr)((u8 *)0x80083160 + (offset)))

/* Build textured sprite strips and append their packets to the ordering table. */
void build_textured_sprite_strips(void *screen_pos, void *sprite, s32 *ordering_table, s32 draw_mode) {
    u16 saved_draw_mode;
    s32 callback_arg;
    s32 matrix_arg;
    s32 origin_byte;
    s32 restore_mode;
    s32 angle_bias;
    Blk40 *row_quad;
    GpuContext *render_state;
    void *callback_sprite;
    s32 callback_param;
    void *callback_frame;
    void *callback_data;
    s16 strip_bottom;
    u16 base_tpage;
    FnPtr draw_callback;
    Blk40 *first_quad;
    s32 *mode_link;
    s32 *right_row_link;
    s32 *restore_link;
    s32 *first_link;
    s32 *second_link;
    s32 *left_row_link;
    u8 *restore_packet;
    S_func_81904990_7 *packet;
    s32 row_v_offset;
    s32 first_addr;
    s32 second_addr;
    s32 left_row_addr;
    s32 right_row_addr;
    s32 mode_bits;
    s32 u_end;
    s32 v_end;
    s32 wrapped_v_offset;
    s32 row_index;
    u16 angle_or_pivot;
    u32 clut_override;
    u16 tpage_offset;
    u8 prim_code;
    u8 right_u;
    u8 bottom_v;
    S_func_81904990_2 *frame;
    S_func_81904990_3 *frame_header;
    S_func_81904990_6 *setup_arg;
    S_func_81904990_8 *view_matrix;
    s16 quad_words;
    s32 tail_value;
    s32 tail_uv;
    s32 addr_mask;
    s32 length_mask;
    S_func_81904990_4 *scratch;
    GameWork *state_page;

    setup_arg = screen_pos;
    frame = ((S_func_81904990_1 *)((u8 *)sprite - 0x18))->unk_04;
    {
        void **state_ptr;
        state_page = &g_game_work;
        state_ptr = (void **)state_page;
        callback_arg = ((S_func_81904990_1 *)((u8 *)sprite - 0x18))->unk_00;
        render_state = *state_ptr;
    }
    frame_header = frame->unk_08;
    scratch = (S_func_81904990_4 *)0x1F800000;
    scratch->unk_EC = NULL;
    scratch->unk_8C = 0;
    scratch->unk_84 = 0;
    scratch->unk_7C = 0;
    scratch->unk_74 = 0;
    packet = (S_func_81904990_7 *)render_state->packetCursor;
    scratch->unk_20 = ordering_table;
    scratch->unk_C0 = NULL;
    scratch->unk_B8 = (s16) (setup_arg->unk_00 - 0xA0);
    scratch->unk_BA = (u16) (setup_arg->unk_02 - 0x78);
    saved_draw_mode = (u16) draw_mode;
    mode_bits = draw_mode << 0x10;
    matrix_arg = 0;
    if (mode_bits != 0) {
        func_80067EF4(packet, 0, 0, mode_bits);
        {
            s32 link_mask = 0xFFFFFF;
            matrix_arg = 0xFF000000;
            packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & 0xFF000000) | (*scratch->unk_20 & link_mask);
        }
        mode_link = scratch->unk_20;
        setup_arg = (void *) ((s32) packet & 0xFFFFFF);
        packet = (S_func_81904990_7 *)((u8 *)packet + 12);
        *mode_link = (*mode_link & 0xFF000000) | (s32) setup_arg;
    }
    quad_words = 9;
    addr_mask = 0xFFFFFF;
    length_mask = 0xFF000000;
    view_matrix = (S_func_81904990_8 *)effect_view_matrix;
    view_matrix->unk_1C = (s32) state_page->view.projection_distance;
    PushMatrix((s32) setup_arg, matrix_arg);
    {
        s32 view_x;
        s32 view_y;
        s32 view_z;
        view_x = state_page->view.camera_rotation.parts.camera_rotation_x;
        view_y = state_page->view.camera_rotation.parts.camera_rotation_y;
        view_z = state_page->view.camera_rotation.parts.viewAngle;
        scratch->unk_30 = view_x;
        scratch->unk_34 = view_y;
        scratch->unk_38 = view_z;
    }
    scratch->unk_100 = (u16) frame->unk_16;
    scratch->unk_104 = (s16) (frame->unk_1A - (u16) scratch->unk_34);
    angle_or_pivot = (((u16) scratch->unk_38 + 0x100) & 0x1FF);
    angle_bias = frame->unk_18 - 0x100;
    scratch->unk_102 = angle_or_pivot + angle_bias;
    {
        s32 pivot_x;
        s32 pivot_y;
        pivot_x = frame->unk_20;
        scratch->unk_E4 = pivot_x;
        scratch->unk_108 = pivot_x;
        pivot_y = frame->unk_22;
        scratch->unk_E8 = pivot_y;
        scratch->unk_10A = pivot_y;
    }
    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);
    {
        s32 scale_x;
        s32 scale_y;
        scale_x = frame->unk_1C;
        scratch->unk_30 = scale_x;
        scale_y = frame->unk_1E;
        scratch->unk_38 = (s32)0x1000;
        scratch->unk_34 = scale_y;
    }
    ScaleMatrix((void *)0x1F8000D0, (void *)0x1F800030);
    CompMatrix(view_matrix, (void *)0x1F8000D0, (void *)0x1F800050);
    SetTransMatrix((void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);
    scratch->unk_24 = (u16) frame->unk_14;
    for (;;) {
        if (!(frame_header->unk_00 & 0x20)) {
            scratch->unk_08 = (s32) frame_header->unk_08.as_u8_08;
            scratch->unk_0C = (s32) frame_header->unk_08.as_u8_09.unk_09;
            scratch->unk_10.as_s32_10 = (s32) frame_header->unk_08.as_u8_0A.unk_0A;
            scratch->unk_14.as_s32_14 = (s32) frame_header->unk_08.as_u8_0B.unk_0B;
            {
                s16 edge;
                if ((frame_header->unk_00 ^ scratch->unk_24) & 1) {
                    edge = -(s8)frame_header->unk_02 - scratch->unk_108;
                    scratch->unk_80 = edge;
                    scratch->unk_70 = edge;
                    edge -= scratch->unk_10.as_u16_10;
                    scratch->unk_88 = edge;
                    scratch->unk_78 = edge;
                } else {
                    edge = (s8)frame_header->unk_02 - scratch->unk_108;
                    scratch->unk_80 = edge;
                    scratch->unk_70 = edge;
                    edge += (u16) scratch->unk_10.as_s32_10;
                    scratch->unk_88 = edge;
                    scratch->unk_78 = edge;
                }
            }
            {
                s16 edge;
                if ((frame_header->unk_00 ^ scratch->unk_24) & 2) {
                    edge = -(s8)frame_header->unk_03 - scratch->unk_10A;
                    scratch->unk_7A = edge;
                    scratch->unk_72 = edge;
                    edge -= scratch->unk_14.as_u16_14;
                    scratch->unk_8A = edge;
                    scratch->unk_82 = edge;
                } else {
                    edge = (s8)frame_header->unk_03 - scratch->unk_10A;
                    scratch->unk_7A = edge;
                    scratch->unk_72 = edge;
                    edge += (u16) scratch->unk_14.as_s32_14;
                    scratch->unk_8A = edge;
                    scratch->unk_82 = edge;
                }
            }
            RotTransPers4(&scratch->unk_70, &scratch->unk_78, &scratch->unk_80, &scratch->unk_88,
                &scratch->unk_F0, &scratch->unk_F4, &scratch->unk_F8, &scratch->unk_FC,
                (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);
            packet->unk_08.as_s16_08 = (s16) (scratch->unk_F0 + scratch->unk_B8);
            packet->unk_0A = (s16) (scratch->unk_F2 + scratch->unk_BA);
            packet->unk_10.as_s16_10 = (s16) (scratch->unk_F4 + scratch->unk_B8);
            packet->unk_12 = (s16) (scratch->unk_F6 + scratch->unk_BA);
            packet->unk_18.as_s16_18 = (s16) (scratch->unk_F8 + scratch->unk_B8);
            packet->unk_1A = (s16) (scratch->unk_FA + scratch->unk_BA);
            packet->unk_20.as_s16_20 = (s16) (scratch->unk_FC + scratch->unk_B8);
            packet->unk_22 = (s16) (scratch->unk_FE + scratch->unk_BA);
            packet->unk_00.as_s8_03.unk_03 = quad_words;
            {
                s32 width = scratch->unk_10.as_s32_10;
                s32 u_start = scratch->unk_08;
                width = width - 1;
                {
                    s32 last_u = width + u_start;
                    u_end = last_u;
                }
            }
            scratch->unk_10.as_s32_10 = u_end;
            if (u_end & 0x100) {
                scratch->unk_10.as_s32_10 = u_end - 1;
            }
            {
                s32 height = scratch->unk_14.as_s32_14;
                s32 v_start = scratch->unk_0C;
                height = height - 1;
                {
                    s32 last_v = height + v_start;
                    v_end = last_v;
                }
            }
            scratch->unk_14.as_s32_14 = v_end;
            if (v_end & 0x100) {
                scratch->unk_14.as_s32_14 = v_end - 1;
            }
            scratch->unk_14.as_s32_14 <<= 8;
            scratch->unk_0C <<= 8;
            clut_override = frame->unk_12;
            {
                s32 clut_value;

                if (clut_override != 0) {
                    if (scratch->unk_24 & 0x100) {
                        packet->unk_0E = clut_override;
                    } else {
                        clut_value = clut_override + frame_header->unk_06;
                        packet->unk_0E = clut_value;
                    }
                } else {
                    clut_value = (u16) frame_header->unk_06;
                    packet->unk_0E = clut_value;
                }
            }
            packet->unk_0C.as_s16_0C = (s16) ((u16) scratch->unk_0C + (u16) scratch->unk_08);
            packet->unk_14.as_s16_14 = (s16) ((u16) scratch->unk_0C + (u16) scratch->unk_10.as_s32_10);
            tpage_offset = frame->unk_10;
            {
                u16 tpage_value;

                if (tpage_offset != 0) {
                    base_tpage = frame_header->unk_04 & 0xFF9F;
                    tpage_value = tpage_offset + base_tpage;
                } else {
                    tpage_value = (u16) frame_header->unk_04;
                }
                packet->unk_16 = tpage_value;
            }
            packet->unk_1C.as_s16_1C = (s16) ((u16) scratch->unk_14.as_s32_14 | (u16) scratch->unk_08);
            packet->unk_24.as_s16_24 = (s16) ((u16) scratch->unk_14.as_s32_14 | (u16) scratch->unk_10.as_s32_10);
            if (packet->unk_08.as_s16_08 > packet->unk_20.as_s16_20) {
                right_u = (u8) packet->unk_24.as_s16_24;
                packet->unk_24.as_u8_24 = (u8) (right_u + 0xFF);
                packet->unk_14.as_u8_14 = right_u;
            }
            if (packet->unk_0A > packet->unk_22) {
                bottom_v = packet->unk_24.as_u8_25.unk_25;
                packet->unk_24.as_u8_25.unk_25 = (u8) (bottom_v + 0xFF);
                packet->unk_1C.as_u8_1D.unk_1D = bottom_v;
            }
            prim_code = frame_header->unk_01;
            frame->unk_0C.as_u8_0F.unk_0F = prim_code;
            tpage_offset = scratch->unk_24;
            if (tpage_offset & 8) {
                origin_byte = tpage_offset & 4;
                if (origin_byte != 0) {
                    origin_byte = prim_code | 2;
                } else {
                    origin_byte = prim_code & 0xFD;
                }
                frame->unk_0C.as_u8_0F.unk_0F = origin_byte;
            }
            first_quad = (Blk40 *)packet;
            packet->unk_04 = (s32) frame->unk_0C.as_s32_0C;
            ((S_func_81904990_1 *)((u8 *)sprite - 0x18))->unk_7A = (u16) packet->unk_0A;
            strip_bottom = (u16) packet->unk_0A + ((S_func_81904990_1 *)((u8 *)sprite - 0x18))->unk_7C;
            packet->unk_22 = strip_bottom;
            packet->unk_1A = strip_bottom;
            first_addr = (s32) packet & addr_mask;
            packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & length_mask) | (*scratch->unk_20 & addr_mask);
            first_link = scratch->unk_20;
            packet = (S_func_81904990_7 *)((u8 *)packet + 40);
            *first_link = (*first_link & length_mask) | first_addr;
            packet->unk_00.as_s8_03.unk_03 = quad_words;

            *(Blk40 *)packet = *first_quad;
            row_index = 1;
            wrapped_v_offset = -0x30;
            second_addr = (s32) packet & addr_mask;
            packet->unk_08.as_u16_08 = (u16) (packet->unk_08.as_u16_08 + 0x40);
            packet->unk_10.as_u16_10 = (u16) (packet->unk_10.as_u16_10 + 0x40);
            packet->unk_18.as_u16_18 = (u16) (packet->unk_18.as_u16_18 + 0x40);
            packet->unk_20.as_u16_20 = (u16) (packet->unk_20.as_u16_20 + 0x40);
            packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & length_mask) | (*scratch->unk_20 & addr_mask);
            second_link = scratch->unk_20;
            packet = (S_func_81904990_7 *)((u8 *)packet + 40);
            *second_link = (*second_link & length_mask) | second_addr;
            do {
            packet->unk_00.as_s8_03.unk_03 = quad_words;
            *(Blk40 *)packet = *first_quad;
            packet->unk_0A = (s16) (((S_func_81904990_1 *)((u8 *)sprite
                - 0x18))->unk_7A + ((u16 *)((u8 *)sprite + 0x62))[row_index]);
            packet->unk_12 = (s16) (((S_func_81904990_1 *)((u8 *)sprite
                - 0x18))->unk_7A + ((u16 *)((u8 *)sprite + 0x62))[row_index]);
            packet->unk_1A = (s16) (((S_func_81904990_1 *)((u8 *)sprite
                - 0x18))->unk_7A + ((u16 *)((u8 *)sprite + 0x62))[row_index + 1]);
            packet->unk_22 = (s16) (((S_func_81904990_1 *)((u8 *)sprite
                - 0x18))->unk_7A + ((u16 *)((u8 *)sprite + 0x62))[row_index + 1]);
            row_v_offset = row_index * 0x10;
            if (row_index < 4) {
                tail_value = packet->unk_0C.as_u8_0D.unk_0D;
                tail_uv = packet->unk_14.as_u8_15.unk_15;
                tail_value = tail_value + row_v_offset;
                packet->unk_0C.as_u8_0D.unk_0D = (u8) tail_value;
                tail_value = packet->unk_1C.as_u8_1D.unk_1D;
                tail_uv = tail_uv + row_v_offset;
                packet->unk_14.as_u8_15.unk_15 = (u8) tail_uv;
                tail_uv = packet->unk_24.as_u8_25.unk_25;
                tail_value = tail_value + row_v_offset;
                tail_uv = tail_uv + row_v_offset;
                packet->unk_1C.as_u8_1D.unk_1D = (u8) tail_value;
                packet->unk_24.as_u8_25.unk_25 = (u8) tail_uv;
            } else {
                tail_value = packet->unk_0C.as_u8_0D.unk_0D;
                tail_uv = packet->unk_14.as_u8_15.unk_15;
                tail_value = tail_value + wrapped_v_offset;
                packet->unk_0C.as_u8_0D.unk_0D = (u8) tail_value;
                tail_value = packet->unk_1C.as_u8_1D.unk_1D;
                tail_uv = tail_uv + wrapped_v_offset;
                packet->unk_14.as_u8_15.unk_15 = (u8) tail_uv;
                tail_uv = packet->unk_24.as_u8_25.unk_25;
                tail_value = tail_value + wrapped_v_offset;
                tail_uv = tail_uv + wrapped_v_offset;
                packet->unk_1C.as_u8_1D.unk_1D = (u8) tail_value;
                packet->unk_24.as_u8_25.unk_25 = (u8) tail_uv;
            }
            row_quad = (Blk40 *)packet;
            left_row_addr = (s32) packet & addr_mask;
            packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & length_mask) | (*scratch->unk_20 & addr_mask);
            left_row_link = scratch->unk_20;
            packet = (S_func_81904990_7 *)((u8 *)packet + 40);
            *left_row_link = (*left_row_link & length_mask) | left_row_addr;
            packet->unk_00.as_s8_03.unk_03 = quad_words;
            *(Blk40 *)packet = *row_quad;
            wrapped_v_offset += 0x10;
            row_index += 1;
            right_row_addr = (s32) packet & addr_mask;
            packet->unk_08.as_u16_08 =
                (u16) (packet->unk_08.as_u16_08 + 0x40);
            packet->unk_10.as_u16_10 =
                (u16) (packet->unk_10.as_u16_10 + 0x40);
            packet->unk_18.as_u16_18 =
                (u16) (packet->unk_18.as_u16_18 + 0x40);
            packet->unk_20.as_u16_20 =
                (u16) (packet->unk_20.as_u16_20 + 0x40);
            packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & length_mask) | (*scratch->unk_20 & addr_mask);
            right_row_link = scratch->unk_20;
            *right_row_link = (*right_row_link & length_mask) | right_row_addr;
            packet = (S_func_81904990_7 *)((u8 *)packet + 40);
            } while (row_index < 8);
        } else {
            draw_callback = frame_header->unk_08.as_FnPtr_08;
            if (draw_callback != NULL) {
                callback_sprite = sprite;
                callback_frame = frame;
                callback_param = callback_arg;
                callback_data = frame_header;
                packet = (S_func_81904990_7 *)draw_callback(callback_sprite, callback_param, callback_frame, callback_data,
                    (u8 *)packet);
            }
        }
        if ((s8) frame_header->unk_00 < 0) {
            break;
        }
        frame_header++;
    }
    restore_mode = saved_draw_mode << 0x10;

    restore_packet = (u8 *)packet;
    if (restore_mode != 0) {
        func_80067EF4(restore_packet, 0, 1);
        packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & 0xFF000000) | (*scratch->unk_20 & 0xFFFFFF);
        restore_link = scratch->unk_20;
        restore_packet = (u8 *) ((s32) packet & 0xFFFFFF);
        packet = (S_func_81904990_7 *)((u8 *)packet + 12);
        *restore_link = (*restore_link & 0xFF000000) | (s32) restore_packet;
    }
    PopMatrix((s32) restore_packet);
    {
        u8 *state_slot = (u8 *)state_page;
        u64 state_bits = *(u64 *)state_slot;
        GpuContext *final_state = (GpuContext *)(u32)state_bits;
        final_state->packetCursor = (u8 *)packet;
    }
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/*
 * Draws at a page-adjusted position with clipping commands and an optional black rectangle.
 * Keeping the page pointer live across setup and spelling the sign extension as one expression
 * reproduce the retail allocation and call-argument order.
 *
 * Screen position: x, then y (a page-relative row).
 *
 * Clip/fill rectangle: origin, then the size word copied verbatim.
 *
 * Link packet: tag word (next address + length), then payload.
 */
void decrement_effect_counter_by_twelve(s32 draw_data, ScreenRect *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param)
{
    u16 draw_pos[2];
    u16 clear_enabled;
    s32 draw_y;
    s32 rect_y;
    u8 *clip_packet;
    GameWork *page_ptr;
    s16 saved_param;
    u32 tag_mask;
    ScreenPos *pos_or_ot;
    u8 *order_table;
    GpuContext *draw_page;
    GpuContext *packet_page;
    s16 offset_y;
    void *call_pos;
    s32 call_data;
    void *call_order_table;
    s32 call_param;

    draw_page = g_game_work.draw_buffer;
    pos_or_ot = screen_pos;
    clip_packet = draw_page->packetCursor;
    offset_y = (void *)draw_page != (void *)upper_draw_context;
    draw_page->packetCursor = clip_packet + 0xC;
    saved_param = draw_param;
    clear_enabled = clear_rect;
    page_ptr = &g_game_work;
    SetDrawArea(clip_packet, g_game_work.draw_buffer);
    tag_mask = 0xFF000000U;

    *(u32 *)clip_packet = (*(u32 *)clip_packet & tag_mask) |
                            (draw_page->orderTag8B0 & 0x00FFFFFFU);
    draw_page->orderTag8B0 = (draw_page->orderTag8B0 & tag_mask) |
                             ((u32)clip_packet & 0x00FFFFFFU);

    draw_pos[0] = pos_or_ot->x;
    draw_y = pos_or_ot->y;
    order_table = (u8 *)draw_page + 0x8B0;
    if (offset_y != 0) {
        draw_y -= 0xE0;
    }
    call_pos = draw_pos;
    call_param = (s32)((u32)saved_param << 16) >> 16;
    call_order_table = order_table;
    call_data = draw_data;
    draw_pos[1] = draw_y;
    build_textured_sprite_strips(call_pos, (void *)call_data, call_order_table, call_param);

    if (clear_enabled != 0) {
        FillPacket *fill_packet;

        packet_page = g_game_work.draw_buffer;
        fill_packet = (FillPacket *)packet_page->packetCursor;
        packet_page->packetCursor = (u8 *)fill_packet + 0x10;
        fill_packet->command = 0x60000000;
        ((GpuLinkTag *)&fill_packet->tag)->len = 3;
        fill_packet->x = clip_rect->x;
        rect_y = clip_rect->y;
        if (offset_y != 0) {
            rect_y -= 0xE0;
        }
        fill_packet->y = rect_y;
        fill_packet->size = clip_rect->size;
        fill_packet->tag = (fill_packet->tag & tag_mask) |
                                 (*(u32 *)order_table & 0x00FFFFFFU);
        *(u32 *)order_table = (*(u32 *)order_table & tag_mask) |
                            ((u32)fill_packet & 0x00FFFFFFU);
    }

    packet_page = page_ptr->draw_buffer;
    clip_packet = packet_page->packetCursor;
    packet_page->packetCursor = clip_packet + 0xC;
    SetDrawArea(clip_packet, clip_rect);
    *(u32 *)clip_packet = (*(u32 *)clip_packet & 0xFF000000U) |
                            (*(u32 *)order_table & 0x00FFFFFFU);
    *(u32 *)order_table = (*(u32 *)order_table & 0xFF000000U) |
                        ((u32)clip_packet & 0x00FFFFFFU);
}
#include "shared/entity.h"
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/* Retail 81905564 (draw_brightness_scaled_linked_tiles): projects each linked point and queues a brightness-scaled shaded tile
 * followed by a draw-mode packet for it. */
s32 draw_brightness_scaled_linked_tiles(PointRecord *first_point, ObjectPosition *first_position)
{
    PointRecord *point = first_point;
    ObjectPosition *position = first_position;
    GameWork *render_state = &g_game_work;
    u32 addr_mask = 0x00FFFFFF;
    GpuContext *render_ctx = g_game_work.draw_buffer;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch80024D64 *scratch =
        (Scratch80024D64 *)0x1F800000;
    PointPacket *tile;
    PointPacket *draw_mode;
    GpuContext *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (PointPacket *)scratch->cursor;
        scratch->x = (u16)position->x.w.i;
        scratch->y = (u16)position->y.w.i;
        scratch->z = (u16)position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = RotTransPers(scratch, &tile->data,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->r = color_value >> 8;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->g = color_value >> 8;

            color_value = (s32)tile->b * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->b = color_value >> 8;

            ((GpuLinkTag *)&tile->tag)->len = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = GetTPage(0, 1, 0, 0);
            SetDrawMode(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->position;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->draw_buffer;
    final_render_ctx->packetCursor = scratch->cursor;
    return 0;
}
#include "shared/entity.h"
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/*
 * Raises the source toward its height limit and flags the object when its counter expires.
 *
 * Position slots: three 4-byte slots with only the second halfword used (x +2, y +6, z +0xA); the
 * z slot's word is also bumped as one s32 (+0x20000 raises z by 2).
 *
 * Effect record: the object header precedes it.
 */
void raise_effect_to_height_limit(EffectRecord *object, ObjectPosition *source)
{
    u16 x;
    u16 y;
    u16 z;
    u16 probe_z;
    s32 height_limit;
    s32 random_value;

    z = (u16)source->z.w.i;
    x = (u16)source->x.w.i;
    y = (u16)source->y.w.i;
    probe_z = z + 2;
    traveling_strip_effect_updated[0] = 1;
    height_limit = (s16)sample_terrain_surface_height(x, y, (s16)probe_z);
    if ((s16)(u16)source->z.w.i < height_limit) {
        random_value = rand();
        source->z.v += 0x20000 + (random_value & 0xFFF);
    }

    object->timer -= 8;
    if (object->timer <= 0) {
        ((ObjectNodeHeader *)object - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/entity.h"
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/* Retail 81905880 (get_half_byte_length): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void get_half_byte_length(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
                   s16 offset_y, s16 offset_z) {
    ObjectNodeHeader *source_obj = parent;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *spawned;
    PointRecord *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    ObjectPosition *dest_x;
    ObjectPosition *dest_y;
    ObjectPosition *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->update_callback = (void *)raise_effect_to_height_limit;
        jitter_x = rand() & 0x1F;
        position_x = source_obj->position->x.w.i;
        dest_x = spawned->position;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = source_obj->position->y.w.i;
        dest_y = spawned->position;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        jitter_z &= 0x1F;
        position_z = source_obj->position->z.w.i;
        fields = (PointRecord *)(spawned + 1);
        dest_z = spawned->position;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        register_node(spawned, draw_brightness_scaled_linked_tiles);
        fields->color = saved_field_28;
    }
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

   /* Update eight animation slots and mark completion when the countdown expires. */
void update_effect_animation_slots(void *anim_state)
{
    s16 next_phase;
    s32 slot_index;
    u16 ticks_left;
    u16 phase;
    s32 offset;
    s32 offset_delta;
    DungeonAnimSlot *setup_slot;
    DungeonAnimSlot *slot;

    ticks_left = ((S_800251A0_0 *)anim_state)->unk_02;
    traveling_strip_effect_updated[0] = 1;
    ((S_800251A0_0 *)anim_state)->unk_02 = ticks_left - 1;
    for (slot_index = 1, setup_slot = (DungeonAnimSlot *)((u8 *)anim_state + 2); slot_index < 9; slot_index++) {
        setup_slot->field_62 = slot_index * 0x10;
        setup_slot = (DungeonAnimSlot *)((u8 *)setup_slot + 2);
    }

    slot_index = 1;
    while (slot_index < 9) {
        slot = (DungeonAnimSlot *)((u8 *)anim_state + slot_index * 2);
        offset_delta = rsin(slot->field_50) >> 9;
        offset = slot->field_62;
        phase = (u16)slot->field_50;
        offset += offset_delta;
        next_phase = phase + 0x50;
        slot->field_50 = next_phase;
        slot->field_62 = offset;
        if (next_phase >= 0x1001) {
            s16 wrapped_phase;

            wrapped_phase = phase - 0xFB0;
            slot->field_50 = wrapped_phase;
        }
        slot_index += 1;
    }

    if ((s16)((S_800251A0_0 *)anim_state)->unk_02 <= 0) {
        ((S_800251A0_0_pre *)anim_state)[-1].unk_00 =
            (u16)(((S_800251A0_0_pre *)anim_state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/*
 * Decrement the record counter and set completion flags when it reaches zero.
 *
 * Effect record: the object header precedes it.
 */
void tick_effect_record(CountdownRecord *record)
{
    u16 counter;

    counter = record->counter;
    traveling_strip_effect_updated[0] = 1;
    counter--;
    record->counter = counter;
    if ((counter << 16) <= 0) {
        ((ObjectNodeHeader *)record - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/* Updates a timed brightness pulse and clears the linked object flag on completion. */
void update_effect_brightness_pulse(u8 *effect, void *unused, u8 *target)
{
    u8 *object;
    u8 *linked_object;
    s16 timer;
    s32 intensity;
    s32 global_flags;
    u16 linked_flags;

    object = *(u8 **)(effect + 0x3C);
    traveling_strip_effect_updated[0] = 1;
    if ((u32)(object[0x13] - 0x33) < 4U) {
        *(u16 *)(effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    *(u16 *)(effect + 2) -= 1;
    linked_object = *(u8 **)(*(u8 **)(effect + 0x3C) - 0x14);
    *(u16 *)(target + 0x14) &= 0xFF7F;
    *(u16 *)(linked_object + 0x14) |= 0x80;

    timer = *(s16 *)(effect + 2);
    if (timer < 20) {
        intensity = ((20 - timer) * 96) / 20 + 32;
        target[0xC] = intensity;
        target[0xD] = intensity;
        target[0xE] = intensity;
    } else if (timer < 40) {
        intensity = ((timer - 20) * 96) / 20 + 32;
        target[0xC] = intensity;
        target[0xD] = intensity;
        target[0xE] = intensity;
    }

    if (*(s16 *)(effect + 2) <= 0) {
        *(u16 *)(effect - 2) |= 0x8000;
        global_flags = object_flag_block.flags;
        linked_flags = *(u16 *)(linked_object + 0x14);
        global_flags |= 0x8000;
        linked_flags &= 0xFF7F;
        object_flag_block.flags = global_flags;
        *(u16 *)(linked_object + 0x14) = linked_flags;
    }
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/* Builds an inverted pixel mask and updates a timed fade effect. */
void build_inverted(void *context, void *unused, void *effect_data) {
    Box image_rect;
    Box mask_rect;
    Point center;
    s32 state;
    s32 tile_column;
    s32 tile_row;
    s32 tile_x;
    s32 mask_x;
    s32 tile_y;
    u16 mask_pixel;
    s16 frame;
    s32 pixel_index;
    s32 one;
    s32 image_width;
    u16 *pixel;
    u8 *pixel_page;
    Box *rect_template;

    rect_template = (Box *)(void *)&strip_texture_rect;
    image_rect = *rect_template;
    rect_template = (Box *)((u8 *)&strip_small_texture_rect);
    mask_rect = *rect_template;
    state = *(s16 *)context;
    traveling_strip_effect_updated[0] = 1;

    switch (state) {
    case 0:
        tile_column = 0;
        pixel_page = (u8 *)0x80020000;
        mask_pixel = -1;
        tile_x = 0x340;
        do {
            tile_row = 0;
            mask_x = tile_x;
            tile_y = 0x154;
            do {
                mask_rect.w = 0x18;
                mask_rect.x = mask_x;
                mask_rect.y = tile_y;
                mask_rect.h = 0x15;
                StoreImage(&mask_rect, pixel_page + 0x6820);
                do {
                } while (DrawSync(1) != 0);
                pixel = (u16 *)(pixel_page + 0x6820);
                pixel_index = 0;
                do {
                    if (*pixel == 0) {
                        *pixel = mask_pixel;
                    } else {
                        *pixel = 0;
                    }
                    pixel_index += 1;
                    pixel += 1;
                } while (pixel_index < 0x1f8);
                LoadImage(&mask_rect, pixel_page + 0x6820);
                tile_row += 1;
                tile_y += 0x15;
            } while (tile_row < 4);
            tile_column += 1;
            tile_x += 0x18;
        } while (tile_column < 4);
        *(s16 *)context = (u16)*(s16 *)context + 1;
        *(u16 *)((u8 *)effect_data + 0x14) &= 0xff7f;

    case 1:
        image_width = 0x60;
        mask_rect.x = 0x340;
        mask_rect.y = 0x100;
        mask_rect.w = image_width;
        mask_rect.h = 0x54;
        center.x = 0x370;
        center.y = 0x148;
        one = 1;
        draw_transformed_sprite_with_clip_rect(*(void **)((u8 *)context + 0x44), &mask_rect, &center, 0, one);
        image_rect.x = 0x340;
        image_rect.y = 0x100;
        image_rect.w = 0x60;
        image_rect.h = 0x54;
        center.x = 0x370;
        center.y = 0x12a;
        decrement_effect_counter_by_twelve(*(void **)((u8 *)context + 0x48), &image_rect, &center, one, one);
        frame = *(s16 *)((u8 *)context + 2);
        if (frame < 0x15) {
            *(s8 *)((u8 *)effect_data + 0xe) = (frame << 7) / 20;
            *(s8 *)((u8 *)effect_data + 0xd) = (*(s16 *)((u8 *)context + 2) << 7) / 20;
            *(s8 *)((u8 *)effect_data + 0xc) = (*(s16 *)((u8 *)context + 2) << 7) / 20;
        }
        if (*(s16 *)((u8 *)context + 2) >= 0x51) {
            *(s8 *)((u8 *)effect_data + 0xe) = ((0x64 - *(s16 *)((u8 *)context + 2)) << 7) / 20;
            *(s8 *)((u8 *)effect_data + 0xd) = ((0x64 - *(s16 *)((u8 *)context + 2)) << 7) / 20;
            *(s8 *)((u8 *)effect_data + 0xc) = ((0x64 - *(s16 *)((u8 *)context + 2)) << 7) / 20;
        }
        frame = (u16)*(s16 *)((u8 *)context + 2) + 1;
        *(s16 *)((u8 *)context + 2) = frame;
        if (frame >= 0x65) {
            *(s16 *)((u8 *)context + 2) = 0;
            *(s16 *)context = (u16)*(s16 *)context + 1;
            *(s16 *)(*(u8 **)((u8 *)context + 0x40) + 0x9c) = one;
            *(u16 *)((u8 *)context - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    if ((u32)(*(u8 *)(*(u8 **)((u8 *)context + 0x3c) + 0x13) - 0x33) < 4U) {
        *(u16 *)((u8 *)effect_data + 0x14) |= 0x80;
    }
    return;
}
#include "dungeon/effect/mesh/build_textured_sprite_strips.h"

/* Updates a traveling effect, its target animation, and its cleanup state. */
void update_traveling(S_func_81905FD0_1 *effect, S_func_81905FD0_2 *motion, S_func_81905FD0_3 *render)
{
    S_func_81905FD0_3 *target_render;
    u8 scratch[56];
    s32 index;
    s32 result;
    s32 random_bits;
    s32 state;
    u8 kind_or_shade;
    u8 *tex_rect;
    u8 *rect_template = strip_texture_rect;

    S_func_81905FD0_4 *owner;
    S_func_81905FD0_5 *owner_object;
    S_func_81905FD0_2 *owner_motion;
    owner = effect->owner;
    *(Copy8 *)(scratch + 8) = *(Copy8 *)rect_template;
    *(Copy32 *)(scratch + 24) = *(Copy32 *)strip_direction_steps;
    state = effect->phase.s16;
    owner_object = (S_func_81905FD0_5 *)((u8 *)owner - 0x20);
    owner_motion = owner_object->position;

    switch (state) {
        void *effect_object;
        S_func_81905FD0_2 *target_motion_m;
    case 0:
        render->color.u32 = 0x00808080;
        *(Copy12 *)((u8 *)effect + 0xA2) = *(Copy12 *)D_800267A8;
        render->source = (u8 *)effect + 0xA2;
        {
            u16 direction = (owner->facing >> 9) & 7;
            ((S_func_81905FD0_10 *)traveling_strip_effect_updated)->unk_00.u16 = 1;
            effect->direction.u16 = direction;
        }
        effect->phase.u16++;

    case 1:
        result = get_sprite_attachment_vector(((S_func_81905FD0_3 *)owner_object->sprite)->source,
                               owner_object->sprite,
                               (Vec3 *)scratch, 0);
        if (result == 0) {
            if ((((S_func_81905FD0_3 *)owner_object->sprite)->flags & 0x8000) == 0) {
                return;
            }
        }
        {
            u16 owner_height;

            motion->x.u16_02.unk_02 = owner_motion->x.u16_02.unk_02;
            motion->y.u16_06.unk_06 = owner_motion->y.u16_06.unk_06;
            owner_height = owner_motion->z.u16_0A.unk_0A;
            motion->z.u16_0A.unk_0A = owner_height;
            if ((((S_func_81905FD0_3 *)owner_object->sprite)->flags & 0x8000) == 0) {
                motion->x.u16_02.unk_02 += ((S_func_81905FD0_8 *)scratch)->unk_00;
                motion->y.u16_06.unk_06 += ((S_func_81905FD0_8 *)scratch)->unk_02;
                motion->z.u16_0A.unk_0A = motion->z.u16_0A.unk_0A + ((S_func_81905FD0_8 *)scratch)->unk_04;
            } else {
                motion->z.u16_0A.unk_0A = owner_height - 0x40;
            }
        }
        if ((((S_func_81905FD0_12 *)effect->launch_flags)->flags & 0x80) == 0) {
            return;
        }
        if ((effect->flags & 4) == 0) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            render->tpage_abr.u16 = 32;
            render->color.u8_0E.unk_0E = 128;
            render->color.u8_0D.unk_0D = 128;
            render->color.u8 = 128;
            render->scale_y.u16 = 2000;
            render->scale_x.u16 = 2000;
            render->flags |= 0xC;
            effect->flags |= 4;
        }
        {
            S_func_81905FD0_6 *target = owner->target;
            if (target != 0) {
                S_func_81905FD0_3 *owner_info;
                s32 tile_distance;

                s32 target_height;

                target_motion_m = ((S_func_81905FD0_5 *)((u8 *)target - 0x20))->position;
                kind_or_shade = target->species;
                target_height = entity_height_offsets[kind_or_shade] + 64;
                effect->target_height.u16 = target_motion_m->z.u16_0A.unk_0A - target_height;
                owner_info = ((S_func_81905FD0_5 *)((u8 *)owner - 0x20))->sprite;
                effect->unk_BA = owner_info->tile_x +
                    ((u8 *)dir_step_x)[effect->direction.s16 * 2];
                effect->unk_BB = owner_info->tile_y +
                    ((u8 *)dir_step_y)[effect->direction.s16 * 2];
                {
                    s32 target_tile;

                    random_bits = owner->target_tile_x;
                    target_tile = owner_info->tile_x;
                    if (random_bits == target_tile) {
                        random_bits = owner->target_tile_y;
                        target_tile = owner_info->tile_y;
                        tile_distance = random_bits - target_tile;
                    } else {
                        tile_distance = random_bits - target_tile;
                    }
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                effect->travel_ticks = tile_distance * 2 - 1;
            } else {
                u16 owner_height = owner->ground_height;

                effect->travel_ticks = 32;
                effect->target_height.u16 = owner_height - 80;
            }
        }
        {
            u8 *direction_steps = scratch + 24;
            u8 *x_step;
            u8 *y_step;

            x_step = direction_steps + effect->direction.s16 * 4;
            motion->velocity_x = (s32)((S_func_81905FD0_9 *)x_step)->unk_00 << 16;
            y_step = direction_steps + effect->direction.s16 * 4;
            motion->velocity_y = (s32)((S_func_81905FD0_9 *)y_step)->unk_02 << 16;
        }
        motion->velocity_z.s32 =
            (((s32)effect->target_height.s16 << 16) - motion->z.s32) /
            (s8)effect->travel_ticks;
        effect->timer.u16 = 0;
        effect->scale_shrinking.u16 = 0;
        effect->scale_timer = 0;
        effect->scale_period.u16 = 5;
        effect->scale_step = 200;
        effect->phase.u16++;
        effect->unk_88 = (s8)effect->travel_ticks;
        effect->unk_8A =
            (s8)effect->travel_ticks * (s8)effect->travel_ticks;
        return;

    case 2:
        index = 0;
        while (1) {
            random_bits = rand();
            get_half_byte_length((u8 *)effect - 0x20, effect->direction.s16, 0x00E02020, (random_bits & 0xFF) | 0x80, 0,
                0, 0);
            index++;
            if (index >= 4) {
                break;
            }
        }
        result = check_adjacent_tile_height_clearance(motion->x.u16_02.unk_02, motion->y.u16_06.unk_06,
                               motion->z.s16_0A.unk_0A, owner->target);
        if ((s16)result == 0) {
            {
                u16 previous_angle = render->angle_z;
                u16 angle = previous_angle + 0x190;
                render->angle_z = angle;
                if (angle >= 0x1001) {
                    render->angle_z = previous_angle - 0xE70;
                }
            }
            if (effect->scale_shrinking.s16 == 0) {
                render->scale_x.u16 += effect->scale_step;
                render->scale_y.u16 += effect->scale_step;
            } else {
                render->scale_x.u16 -= effect->scale_step;
                render->scale_y.u16 -= effect->scale_step;
            }
            {
                u16 timer = effect->scale_timer + 1;
                effect->scale_timer = timer;
                if ((s16)timer >= effect->scale_period.s16) {
                    effect->scale_timer = 0;
                    effect->scale_shrinking.u16 = effect->scale_shrinking.u16 ^ 1;
                }
            }
            effect->travel_ticks = effect->travel_ticks - 1;
            if ((s8)effect->travel_ticks > 0) {
                goto update_coords;
            }
            if (owner->target != 0) {
                effect->phase.u16 = 3;
                effect->timer.u16 = 0;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                {
                    S_func_81905FD0_6 *target = owner->target;
                    kind_or_shade = target->species;
                    target_render = ((S_func_81905FD0_5 *)((u8 *)target - 0x20))->sprite;
                    if ((u32)(kind_or_shade - 0x33) >= 4) {
                        target_render->flags |= 0x800;
                        ((S_func_81905FD0_6 *)owner->target)->property_flags |= 0x100000;
                    }
                }
                {

                    target_motion_m = ((S_func_81905FD0_5 *)((u8 *)owner->target - 0x20))->position;
                    motion->x.u16_02.unk_02 = target_motion_m->x.u16_02.unk_02;
                    motion->y.u16_06.unk_06 = target_motion_m->y.u16_06.unk_06;
                }
                motion->z.u16_0A.unk_0A = effect->target_height.u16;
                return;
            }
        }
        effect->phase.u16 = 8;
        effect->timer.u16 = 0;
        render->color.u8_0E.unk_0E = 0;
        render->color.u8_0D.unk_0D = 0;
        render->color.u8 = 0;
        return;

update_coords:
        motion->x.u32 += motion->velocity_x;
        motion->y.u32 += motion->velocity_y;
        motion->z.u32 += motion->velocity_z.u32;
        return;

    case 3:
    {
        {
            u16 previous_angle = render->angle_z;
            u16 angle = previous_angle + 0x190;
            render->angle_z = angle;
            if (angle >= 0x1001) {
                render->angle_z = previous_angle - 0xE70;
            }
        }
        if (effect->scale_shrinking.s16 == 0) {
            render->scale_x.u16 += effect->scale_step;
            render->scale_y.u16 += effect->scale_step;
        } else {
            render->scale_x.u16 -= effect->scale_step;
            render->scale_y.u16 -= effect->scale_step;
        }
        {
            u16 timer = effect->scale_timer + 1;
            effect->scale_timer = timer;
            if ((s16)timer >= effect->scale_period.s16) {
                effect->scale_timer = 0;
                effect->scale_shrinking.u16 = effect->scale_shrinking.u16 ^ 1;
            }
        }
        {
            s16 frame;
            u8 *tex_dest;

            effect->timer.u16 = effect->timer.u16 + 1;
            frame = (s16)effect->timer.u16;
            if (frame == 1) {
                s32 rect_value;
                u16 second_y;
                u16 second_dest_y;
                u16 first_y;
                u16 first_width;
                void *rect_arg;
                void *dest_arg;
                s32 dest_x;
                s32 rect_height;
                s32 rect_x;

                tex_rect = scratch + 8;
                rect_arg = tex_rect;
                tex_dest = scratch + 16;
                dest_arg = tex_dest;
                rect_x = 832;
                ((S_func_81905FD0_8 *)scratch)->unk_08 = rect_x;
                first_y = 340;
                ((S_func_81905FD0_8 *)scratch)->unk_0A = first_y;
                first_width = 96;
                rect_height = 84;
                dest_x = 880;
                ((S_func_81905FD0_8 *)scratch)->unk_0C = first_width;

                ((S_func_81905FD0_8 *)scratch)->unk_0E = rect_height;
                ((S_func_81905FD0_8 *)scratch)->unk_10 = dest_x;
                ((S_func_81905FD0_8 *)scratch)->unk_12 = 410;
                draw_transformed_sprite_with_clip_rect(owner->target, rect_arg,
                              dest_arg, 1, frame);
                rect_arg = tex_rect;
                dest_arg = tex_dest;
                ((S_func_81905FD0_8 *)scratch)->unk_08 = rect_x;
                second_y = 424;
                ((S_func_81905FD0_8 *)scratch)->unk_0A = second_y;
                rect_value = 96;
                ((S_func_81905FD0_8 *)scratch)->unk_0C = rect_value;
                second_dest_y = 495;
                ((S_func_81905FD0_8 *)scratch)->unk_0E = rect_height;
                ((S_func_81905FD0_8 *)scratch)->unk_10 = dest_x;
                ((S_func_81905FD0_8 *)scratch)->unk_12 = second_dest_y;
                draw_transformed_sprite_with_clip_rect(owner->target, rect_arg,
                              dest_arg, 1, frame);
            }
            if (effect->timer.s16 != 4) {
                return;
            }
        }
        {
            ObjectNodeHeader *upper_effect;
            ObjectNodeHeader *lower_effect;
            ObjectNodeHeader *ring_effect;
            ObjectNodeHeader *control_effect;
            S_func_81905FD0_7 *child_data;
            SpriteFrameState *child_render;
            ObjectPosition *child_motion;

            upper_effect = allocate_flagged_object_node(0x212);
            if (upper_effect != 0) {
                child_data = (S_func_81905FD0_7 *)((u8 *)upper_effect + 0x20);
                child_data->unk_02 = 120;
                upper_effect->update_callback = (void *)tick_effect_record;
                register_node(upper_effect, project_sprite_chain);
                child_render = upper_effect->sprite;
                {
                    u16 flags;

                    child_render->flags |= 0xC;
                    child_render->tpage_abr = 64;
                    child_render->depth_bias = 0;
                    flags = child_render->flags;
                    child_render->flags = flags | 0x80;
                }
                child_motion = upper_effect->position;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                {

                    target_motion_m = ((S_func_81905FD0_5 *)((u8 *)owner->target - 0x20))->position;
                    child_motion->x.v = target_motion_m->x.u32;
                    child_motion->y.v = target_motion_m->y.u32;
                    child_motion->z.v = target_motion_m->z.u32;
                }
                child_render = upper_effect->sprite;
                child_render->scale_x = 4100;
                child_render->scale_y = 4100;
                {
                    u8 target_height = entity_height_offsets[((S_func_81905FD0_6 *)owner->target)->species];

                    child_render->color.c.b = 128;
                    child_render->color.c.g = 128;
                    child_render->color.c.r = 128;
                    child_render->offset_y = (-target_height) / 2;
                }
                *(Copy12 *)((u8 *)upper_effect + 0x40) = *(Copy12 *)D_8002676C;
                child_render->source = (u8 *)upper_effect + 0x40;
                ((S_func_81905FD0_13 *)child_render->source)->tpage =
                    GetTPage(2, 1, 832, 340);
            }
            lower_effect = allocate_flagged_object_node(0x212);
            if (lower_effect != 0) {
                child_data = (S_func_81905FD0_7 *)((u8 *)lower_effect + 0x20);
                child_data->unk_02 = 140;
                lower_effect->update_callback = (void *)update_effect_brightness_pulse;
                register_node(lower_effect, project_sprite_chain);
                child_render = lower_effect->sprite;
                child_render->flags &= 0xFFF3;
                child_render->tpage_abr = 32;
                child_render->flags |= 0x80;
                child_data->unk_38 = owner;
                child_data->unk_3C = owner->target;
                child_data->unk_40 = effect;
                child_render->depth_bias = 0;
                child_motion = lower_effect->position;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                {

                    target_motion_m = ((S_func_81905FD0_5 *)((u8 *)owner->target - 0x20))->position;
                    child_motion->x.v = target_motion_m->x.u32;
                    child_motion->y.v = target_motion_m->y.u32;
                    child_motion->z.v = target_motion_m->z.u32;
                }
                child_render = lower_effect->sprite;
                child_render->scale_y = 4096;
                child_render->scale_x = 4096;
                child_render->color.c.b = 128;
                child_render->color.c.g = 128;
                child_render->color.c.r = 128;
                *(Copy12 *)((u8 *)lower_effect + 0x40) = *(Copy12 *)D_80026778;
                child_render->source = (u8 *)lower_effect + 0x40;
                ((S_func_81905FD0_13 *)child_render->source)->tpage =
                    GetTPage(2, 1, 832, 424);
            }
            ring_effect = allocate_flagged_object_node(0x212);
            if (ring_effect != 0) {
                child_data = (S_func_81905FD0_7 *)((u8 *)ring_effect + 0x20);
                child_data->unk_02 = 120;
                ring_effect->update_callback = (void *)update_effect_animation_slots;
                register_node(ring_effect, project_sprite_chain);
                child_render = ring_effect->sprite;
                {
                    u16 flags;

                    child_render->flags &= 0xFFF3;
                    child_render->tpage_abr = 32;
                    child_render->depth_bias = 0;
                    flags = child_render->flags;
                    child_render->flags = flags | 0x80;
                }
                child_motion = ring_effect->position;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                index = 0;
                {

                    target_motion_m = ((S_func_81905FD0_5 *)((u8 *)owner->target - 0x20))->position;
                    child_motion->x.v = target_motion_m->x.u32;
                    child_motion->y.v = target_motion_m->y.u32;
                    child_motion->z.v = target_motion_m->z.u32;
                }
                child_render = ring_effect->sprite;
                child_render->scale_x = 4096;
                child_render->scale_y = 4096;
                child_render->color.c.b = 128;
                child_render->color.c.g = 128;
                child_render->color.c.r = 128;
                {
                    u8 *descriptor_src = D_80026784;
                    u8 *descriptor_dest = (u8 *)child_data;

                    do {
                        *(Copy12 *)(descriptor_dest + 0x20) = *(Copy12 *)descriptor_src;
                        descriptor_src += 12;
                        descriptor_dest += 12;
                        index++;
                    } while (index < 2);
                }
                {
                    s16 *angle_slot;

                    index = 1;
                    angle_slot = (s16 *)((u8 *)child_data + 2);
                    do {
                        angle_slot[40] = index << 9;
                        index++;
                        angle_slot++;
                    } while (index < 9);
                }
                child_render->source = (u8 *)child_data + 0x20;
            }
            control_effect = allocate_flagged_object_node(0x212);
            if (control_effect != 0) {
                void *render_template;
                void *control_script;
                void *owner_target;

                child_data = (S_func_81905FD0_7 *)((u8 *)control_effect + 0x20);
                effect_object = control_effect;
                render_template = project_sprite_chain;
                child_data->unk_38 = owner;
                owner_target = owner->target;
                child_data->unk_44 = (void *)((u32)((u32)((u8 *)upper_effect + 0x20)));
                child_data->unk_48 = (u8 *)ring_effect + 0x20;
                child_data->unk_4C = (u8 *)lower_effect + 0x20;
                control_script = (void *)build_inverted;
                child_data->unk_40 = effect;
                child_data->unk_3C = owner_target;
                control_effect->update_callback = control_script;
                register_node(effect_object, render_template);
                child_render = control_effect->sprite;
                {
                    u16 flags;

                    child_render->flags |= 0xC;
                    child_render->tpage_abr = 32;
                    child_render->depth_bias = 0;
                    flags = child_render->flags;
                    child_render->flags = flags | 0x80;
                }
                child_motion = control_effect->position;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                {

                    target_motion_m = ((S_func_81905FD0_5 *)((u8 *)owner->target - 0x20))->position;
                    child_motion->x.v = target_motion_m->x.u32;
                    child_motion->y.v = target_motion_m->y.u32;
                    child_motion->z.v = target_motion_m->z.u32;
                }
                child_render = control_effect->sprite;
                child_render->scale_y = 4096;
                child_render->scale_x = 4096;
                child_render->color.c.b = 128;
                child_render->color.c.g = 128;
                child_render->color.c.r = 128;
                *(Copy12 *)((u8 *)control_effect + 0x40) = *(Copy12 *)D_80026760;
                child_render->source = (u8 *)control_effect + 0x40;
            }
            if (effect->timer.s16 == 4) {
                effect->phase.u16 = 4;
                effect->timer.u16 = 0;
                effect->child_done.u16 = 0;
                return;
            }
        }
        return;
    }

    case 4:
        effect->timer.u16++;
        index = 4;
        do {
            index--;
        } while (index >= 0);
        index++;
        {
            u16 previous_angle = render->angle_z;
            u16 angle = previous_angle + 0x190;
            render->angle_z = angle;
            if (angle >= 0x1001) {
                render->angle_z = previous_angle - 0xE70;
            }
        }
        if (effect->scale_shrinking.s16 == 0) {
            render->scale_x.u16 += effect->scale_step;
            render->scale_y.u16 += effect->scale_step;
        } else {
            render->scale_x.u16 -= effect->scale_step;
            render->scale_y.u16 -= effect->scale_step;
        }
        {
            u16 timer = effect->scale_timer + 1;
            effect->scale_timer = timer;
            if ((s16)timer >= effect->scale_period.s16) {
                effect->scale_timer = 0;
                effect->scale_shrinking.u16 = effect->scale_shrinking.u16 ^ 1;
            }
        }
        if ((u32)(effect->timer.u16 - 11) < 20) {
            kind_or_shade = render->color.u8_0E.unk_0E - 3;
            render->color.u8_0E.unk_0E = kind_or_shade;
            render->color.u8_0D.unk_0D = kind_or_shade;
            render->color.u8 = kind_or_shade;
        }
        if (effect->timer.s16 >= 100 && render->color.u8 >= 6) {
            kind_or_shade = render->color.u8_0E.unk_0E - 4;
            render->color.u8_0E.unk_0E = kind_or_shade;
            render->color.u8_0D.unk_0D = kind_or_shade;
            render->color.u8 = kind_or_shade;
        }
        if (effect->timer.s16 >= 120) {
            effect->timer.u16 = 0;
            effect->phase.u16 = effect->phase.u16 + 1;
        }
        return;

    case 5:
        if (effect->child_done.s16 == 0) {
            return;
        }
        result = 0xFF;
        if (((S_func_81905FD0_11 *)current_spell_effect_variant)->unk_00 != result) {
            result = effect->unk_09;
        }
        try_halve_actor_counter(owner->target, result, owner);

        effect->timer.u16 = 0;
        effect->phase.u16 = effect->phase.u16 + 1;
        return;

    case 6:
        effect->timer.u16 = effect->timer.u16 + 1;
        if (effect->timer.s16 < 11) {
            return;
        }
        target_render = ((S_func_81905FD0_5 *)((u8 *)owner->target - 0x20))->sprite;
        target_render->flags &= 0xF7FF;
        ((S_func_81905FD0_6 *)owner->target)->property_flags &= 0xFFEFFFFF;
        ((S_func_81905FD0_6 *)owner->target)->state_flags &= 0xEFFFFFFF;
        target_render->color.u8_0E.unk_0E = 128;
        target_render->color.u8_0D.unk_0D = 128;
        target_render->color.u8 = 128;
        effect->phase.u16 = 8;
        effect->timer.u16 = 30;
        return;

    case 8:
    {
        u16 previous_timer = effect->timer.u16;
        u16 timer = previous_timer + 1;

        effect->timer.u16 = timer;
        if ((s16)timer < 31) {
            return;
        }
        {
            s32 active_flag = ((S_func_81905FD0_10 *)traveling_strip_effect_updated)->unk_00.s16;

            effect->timer.u16 = previous_timer;
            if (active_flag == 0) {
                g_dungeon_status.active_actor = 0;
                ((ObjectNodeHeader *)((u8 *)effect - 0x20) )->flags|= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            } else {
                ((S_func_81905FD0_10 *)traveling_strip_effect_updated)->unk_00.u16 = 0;
            }
        }
        return;
    }

    case 7:
    default:
        return;
    }
}
