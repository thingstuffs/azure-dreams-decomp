/* Rotated sprite scanline rendering and clipping rectangle setup. */
#include "shared/sprite_frame_state.h"
#include "engine/graphics/sprite_scratch.h"
#include "dungeon/effect/sprite/render_rotated_effect_quads.h"
#include "shared/game_work.h"
#include "dungeon/effect/sprite.h"
#include "shared/sprite_part_command.h"
#include "shared/gpu_packets.h"
#include "sdk/libgpu_packets.h"
#include "shared/object_node.h"

/* Projects rotated sprite parts as waving scanline quads and links their packets into the ordering table. */
void render_rotated_effect_quads(void *screen_pos, void *effect, u32 *ordering_tag, u32 draw_mode)
{
    POLY_FT4 quad_copies[2]; /* the projected part quad, then the scanline strip being advanced */
    u16 saved_draw_mode;
    u32 shifted_mode;
    ObjectPosition *callback_arg;
    s32 *copy_end;
    u32 addr_mask;
    s32 draw_arg;
    GameWork *render_state;
    MATRIX *view_matrix;
    s32 texture_word;
    GpuContext *render_context;
    GpuContext *final_context;
    s32 base_rotation;
    s32 packet_mask;
    s32 row_index;
    s32 clut_offset;
    s32 tpage_offset;
    s16 mirrored_x;
    s16 quad_x;
    s16 mirrored_y;
    s16 quad_y;
    s32 wave_phase;
    SpritePartCallback draw_callback;
    u32 *row_tag;
    u32 *start_tag;
    u32 *end_tag;
    POLY_FT4 *restore_arg;
    POLY_FT4 *packet;
    ObjectPosition *draw_callback_arg;
    s32 wave_value;
    s32 edge_value;
    s32 width_minus_one;
    s32 height_minus_one;
    s32 bottom_v;
    s32 view_axis_x;
    s32 view_axis_y;
    s32 view_axis_z;
    u16 screen_y;
    u16 projected_y;
    u32 pivot_x;
    u32 pivot_y;
    u16 next_row_y;
    u8 prim_code;
    u8 right_u;
    u16 draw_flags;
    s32 left_x;
    SpriteQuadScratch *scratch;
    SpritePartCommand *frame;
    void *row_effect;
    SpriteFrameState *sprite;
    void *setup_arg;
    u8 *context_addr;
    s32 packet_low;
    setup_arg = screen_pos;
    sprite = NODE_HEADER(effect)->sprite;
    callback_arg = NODE_HEADER(effect)->position;
    render_context = g_game_work.draw_buffer;
    render_state = &g_game_work;
    frame = sprite->source;
    scratch = (SpriteQuadScratch *)0x1F800000;
    scratch->local_matrix.t[2] = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    packet = render_context->packetCursor;
    scratch->ordering_table = ordering_tag;
    scratch->sort_depth = 0;
    scratch->screen_origin.x = (u16) ((*((u16 *) (((s8 *) setup_arg) + 0))) - 0xA0);
    scratch->screen_origin.y = (u16) ((*((u16 *) (((s8 *) setup_arg) + 2))) - 0x78);
    saved_draw_mode = (u16) draw_mode;
    shifted_mode = draw_mode << 0x10;
    draw_arg = 0;
    if (shifted_mode != 0) {
        SetPriority(packet, draw_arg, draw_arg);
        packet_mask = 0xFFFFFF;
        draw_arg = 0xFF000000;
        packet->tag = (packet->tag & 0xFF000000) | (*scratch->ordering_table & packet_mask);
        start_tag = scratch->ordering_table;
        setup_arg = (void *) (((s32) packet) & packet_mask);
        packet = (POLY_FT4 *) ((u32 *) packet + 3);
        *start_tag = ((*start_tag) & 0xFF000000) | ((s32) setup_arg);
    }
    copy_end = (s32 *) quad_copies + 8;
    addr_mask = 0xFFFFFF;
    view_matrix = &effect_view_matrix;
    view_matrix->t[2] = render_state->view.projection_distance;
    PushMatrix((s32) setup_arg, draw_arg);
    view_axis_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    view_axis_y = render_state->view.camera_rotation.parts.camera_rotation_y;
    view_axis_z = render_state->view.camera_rotation.parts.viewAngle;
    scratch->input.vx = view_axis_x;
    scratch->input.vy = view_axis_y;
    scratch->input.vz = view_axis_z;
    scratch->angles.vx = sprite->angle_x;
    scratch->angles.vz = sprite->angle_z - scratch->input.vy;
    base_rotation = sprite->angle_y;
    scratch->angles.vy = (((scratch->input.vz + 0x100) & 0x1FF) - 0x100) + base_rotation;
    pivot_x = sprite->offset_x;
    scratch->local_matrix.t[0] = pivot_x;
    scratch->extent_x = pivot_x;
    pivot_y = sprite->offset_y;
    scratch->local_matrix.t[1] = pivot_y;
    scratch->extent_y = pivot_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    scratch->input.vx = sprite->scale_x;
    scratch->input.vy = sprite->scale_y;
    scratch->input.vz = 0x1000;
    ScaleMatrix(&scratch->local_matrix, &scratch->input);
    CompMatrix(view_matrix, &scratch->local_matrix, &scratch->matrix);
    SetTransMatrix(&scratch->matrix);
    SetRotMatrix(&scratch->matrix);
    scratch->sprite_flags = sprite->flags;
    do {
    if (!(frame->flags & 0x20)) {
        scratch->uv_u_start = frame->data.texture.u0;
        scratch->uv_v_start = frame->data.texture.v0;
        scratch->uv_u_extent = frame->data.texture.width;
        scratch->uv_v_extent = frame->data.texture.height;
        if ((frame->flags ^ scratch->sprite_flags) & 1) {
            mirrored_x = (0 - frame->offset_x) - scratch->extent_x;
            scratch->vertices[2].vx = mirrored_x;
            scratch->vertices[0].vx = mirrored_x;
            mirrored_x = mirrored_x - scratch->uv_u_extent;
            scratch->vertices[3].vx = mirrored_x;
            scratch->vertices[1].vx = mirrored_x;
        }
        else {
            quad_x = frame->offset_x - scratch->extent_x;
            scratch->vertices[2].vx = quad_x;
            scratch->vertices[0].vx = quad_x;
            quad_x = quad_x + scratch->uv_u_extent;
            scratch->vertices[3].vx = quad_x;
            scratch->vertices[1].vx = quad_x;
        }
        if ((frame->flags ^ scratch->sprite_flags) & 2) {
            mirrored_y = (0 - frame->offset_y) - scratch->extent_y;
            scratch->vertices[1].vy = mirrored_y;
            scratch->vertices[0].vy = mirrored_y;
            mirrored_y = mirrored_y - scratch->uv_v_extent;
            scratch->vertices[3].vy = mirrored_y;
            scratch->vertices[2].vy = mirrored_y;
        }
        else {
            quad_y = frame->offset_y - scratch->extent_y;
            scratch->vertices[1].vy = quad_y;
            scratch->vertices[0].vy = quad_y;
            quad_y = quad_y + scratch->uv_v_extent;
            scratch->vertices[3].vy = quad_y;
            scratch->vertices[2].vy = quad_y;
        }
        RotTransPers4(&scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
            (s32 *)&scratch->projected_vertices[0], (s32 *)&scratch->projected_vertices[1],
            (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3], &scratch->depth_cue, &scratch->gte_flag);
        packet->x0 = ((scratch->projected_vertices[0].x) + (scratch->screen_origin.x));
        packet->y0 = ((scratch->projected_vertices[0].y)
            + (scratch->screen_origin.y));
        packet->x1 = ((scratch->projected_vertices[1].x)
            + (scratch->screen_origin.x));
        packet->y1 = ((scratch->projected_vertices[1].y)
            + (scratch->screen_origin.y));
        packet->x2 = ((scratch->projected_vertices[2].x)
            + (scratch->screen_origin.x));
        packet->y2 = ((scratch->projected_vertices[2].y)
            + (scratch->screen_origin.y));
        packet->x3 = ((scratch->projected_vertices[3].x)
            + (scratch->screen_origin.x));
        projected_y = scratch->projected_vertices[3].y;
        screen_y = scratch->screen_origin.y;
        ((GpuLinkTag *) &packet->tag)->len = 9;
        packet->y3 = (projected_y + screen_y);
        width_minus_one = (scratch->uv_u_extent) - 1;
        edge_value = width_minus_one + (scratch->uv_u_start);
        scratch->uv_u_extent = edge_value;
        if (edge_value & 0x100) {
            scratch->uv_u_extent = edge_value - 1;
        }
        height_minus_one = (scratch->uv_v_extent) - 1;
        bottom_v = height_minus_one + (scratch->uv_v_start);
        scratch->uv_v_extent = bottom_v;
        if (bottom_v & 0x100) {
            scratch->uv_v_extent = bottom_v - 1;
        }
        scratch->uv_v_extent <<= 8;
        scratch->uv_v_start <<= 8;
        clut_offset = sprite->clut;
        if (clut_offset != 0) {
            if ((scratch->sprite_flags) & 0x100) {
                packet->clut = clut_offset;
            } else {
            texture_word = clut_offset + frame->clut;
            packet->clut = texture_word;
            }
        }
        else {
            packet->clut = frame->clut;
        }
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(s16 *) &packet->u0 = scratch->uv_v_start + scratch->uv_u_start;
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(s16 *) &packet->u1 = scratch->uv_v_start + scratch->uv_u_extent;
        tpage_offset = sprite->tpage_abr;
        if (tpage_offset != 0) {
            packet->tpage = tpage_offset + (frame->tpage & 0xFF9F);
        }
        else {
            packet->tpage = frame->tpage;
        }
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(s16 *) &packet->u2 = scratch->uv_v_extent | scratch->uv_u_start;
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(s16 *) &packet->u3 = scratch->uv_v_extent | scratch->uv_u_extent;
        left_x = packet->x0;
        if (packet->x3 < left_x) {
            right_u = packet->u3;
            packet->u3 = right_u + 0xFF;
            packet->u1 = right_u;
        }
        edge_value = packet->y0;
        if (packet->y3 < edge_value) {
            draw_flags = packet->v3;
            packet->v3 = draw_flags + 0xFF;
            packet->v2 = draw_flags;
        }
        prim_code = frame->code;
        sprite->color.c.code = prim_code;
        draw_flags = scratch->sprite_flags;
        if (draw_flags & 8) {
            if (draw_flags & 4) {
                sprite->color.c.code = prim_code | 2;
            }
            else {
                sprite->color.c.code = prim_code & 0xFD;
            }
        }
        /* BYTES: retail stores the sprite colour word (r0, g0, b0 and code) with one sw; member stores compile to four sb */
        *(s32 *) &packet->r0 = sprite->color.word;
        quad_copies[0] = *packet;
        {
            Blk16 *copy_dst = (Blk16 *) &quad_copies[1];
            Blk16 *copy_src = (Blk16 *) quad_copies;
            do {
                {
                    *(copy_dst++) = *(copy_src++);
                }
            } while (((s32 *) copy_src) != copy_end);
            *((Blk8 *) copy_dst) = *((Blk8 *) copy_src);
        }
        row_index = 0;
        wave_phase = *((s16 *) (((s8 *) effect) + 0x8C));
        do {
            ((GpuLinkTag *) &packet->tag)->len = 9;
            {
                Blk16 *packet_dst = (Blk16 *) packet;
                Blk16 *packet_src = (Blk16 *) quad_copies;
                do {
                    *(packet_dst++) = *(packet_src++);
                }
                while (((s32 *) packet_src) != copy_end);
                *((Blk8 *) packet_dst) = *((Blk8 *) packet_src);
            }
            wave_value = rsin(wave_phase);
            row_effect = effect + row_index;
            packet->x0 = (packet->x0
                + (((s32) (wave_value * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            packet->x1 = (packet->x1
                + (((s32) (rsin(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            wave_phase = wave_phase + (*((s16 *) (((s8 *) effect) + 0x8E)));
            if (wave_phase >= 0x1001) {
                wave_phase -= 0x1000;
            }
            packet->x2 = (packet->x2
                + (((s32) (rsin(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            packet->x3 = (packet->x3
                + (((s32) (rsin(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            packet->y0 = quad_copies[1].y0;
            packet->y1 = quad_copies[1].y0;
            packet->y2 = (quad_copies[1].y0 + 1);
            packet->y3 = (quad_copies[1].y0 + 1);
            packet->v0 = quad_copies[1].v0;
            packet->v1 = quad_copies[1].v0;
            row_index += 1;
            packet->v2 = (quad_copies[1].v0) + 1;
            packet->v3 = (quad_copies[1].v0) + 1;
            {
                s32 link_lower;
                s32 tag_high;
                tag_high = packet->tag & 0xFF000000;
                link_lower = *scratch->ordering_table & addr_mask;
                packet->tag = tag_high | link_lower;
            }
            row_tag = scratch->ordering_table;
            {
                s32 link_lower;
                s32 tag_high;
                tag_high = (*row_tag & 0xFF000000);
                link_lower = (s32)packet & addr_mask;
                *row_tag = tag_high | link_lower;
            }
            quad_copies[1] = *packet;
            next_row_y = quad_copies[1].y0 + 1;
            quad_copies[1].y0 = next_row_y;
            quad_copies[1].v0 += 1;
            wave_phase = wave_phase + (*((s16 *) (((s8 *) effect) + 0x8E)));
            packet++;
            if (wave_phase >= 0x1001) {
                wave_phase -= 0x1000;
            }
        }
        while (((s16) next_row_y) < (quad_copies[0].y2));
    }
    else {
        draw_callback = frame->data.callback;
        if (draw_callback != 0) {
            draw_callback_arg = callback_arg;
            packet = draw_callback(effect, draw_callback_arg, sprite, frame, packet);
        }
    }
    if ((s8) frame->flags < 0) break;
    frame++;
    } while (1);
    restore_arg = packet;
    if ((saved_draw_mode << 0x10) != 0) {
        SetPriority(restore_arg, 0, 1);
        packet->tag = (packet->tag & 0xFF000000) | (*scratch->ordering_table & 0xFFFFFF);
        end_tag = scratch->ordering_table;
        restore_arg = (POLY_FT4 *) (((s32) packet) & 0xFFFFFF);
        packet = (POLY_FT4 *) ((u32 *) packet + 3);
        *end_tag = ((*end_tag) & 0xFF000000) | ((s32) restore_arg);
    }
    PopMatrix((s32) restore_arg);
    packet_low = (s32) ((u16) ((s32) packet));
    context_addr = (u8 *) render_state + (packet_low & 0x10000);
    final_context = *(GpuContext **) context_addr;
    final_context->packetCursor = packet;
}

/* Queues clipping packets around the effect draw and optionally clears the supplied rectangle. */
void draw_effect_and_restore_clip(s32 draw_data, Row_818ED25C_S_80024A5C_5 *clip_rect, void *screen_pos, u16 clear_rect, s16 draw_param)
{
    u16 draw_pos[2];
    u16 clear_enabled;
    s32 draw_y;
    s32 rect_y;
    u8 *clip_packet;
    GameWork *page_ptr;
    s16 saved_param;
    u32 tag_mask;
    u8 *pos_or_ot;
    Row_818ED25C_S_80024A5C_6 *order_table;
    Row_818ED25C_S_80024A5C_0 *draw_page;
    Row_818ED25C_S_80024A5C_3 *packet_page;
    s16 offset_y;
    void *call_pos;
    s32 call_data;
    void *call_order_table;
    s32 call_param;

    draw_page = g_game_work.draw_buffer;
    pos_or_ot = screen_pos;
    clip_packet = draw_page->unk_8D0;
    offset_y = draw_page != (void *)upper_draw_context;
    draw_page->unk_8D0 = clip_packet + 0xC;
    saved_param = draw_param;
    clear_enabled = clear_rect;
    page_ptr = &g_game_work;
    SetDrawArea(clip_packet, g_game_work.draw_buffer);
    tag_mask = 0xFF000000U;

    ((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 = (((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 & tag_mask) |
                            (draw_page->unk_8B0 & 0x00FFFFFFU);
    draw_page->unk_8B0 = (draw_page->unk_8B0 & tag_mask) |
                             ((u32)clip_packet & 0x00FFFFFFU);

    draw_pos[0] = ((Row_818ED25C_S_80024A5C_2 *)pos_or_ot)->unk_00;
    draw_y = ((Row_818ED25C_S_80024A5C_2 *)pos_or_ot)->unk_02;
    pos_or_ot = (u8 *)draw_page + 0x8B0;
    order_table = (Row_818ED25C_S_80024A5C_6 *)pos_or_ot;
    if (offset_y != 0) {
        draw_y -= 0xE0;
    }
    call_pos = draw_pos;
    call_param = (s32)((u32)saved_param << 16) >> 16;
    call_order_table = order_table;
    call_data = draw_data;
    draw_pos[1] = draw_y;
    render_rotated_effect_quads(call_pos, call_data, call_order_table, call_param);

    if (clear_enabled != 0) {
        Row_818ED25C_S_80024A5C_4 *fill_packet;

        packet_page = g_game_work.draw_buffer;
        fill_packet = (Row_818ED25C_S_80024A5C_4 *)packet_page->unk_8D0;
        packet_page->unk_8D0 = (u8 *)fill_packet + 0x10;
        fill_packet->unk_04 = 0x60000000;
        fill_packet->unk_00.at03.v = 3;
        fill_packet->unk_08 = clip_rect->unk_00;
        rect_y = clip_rect->unk_02;
        if (offset_y != 0) {
            rect_y -= 0xE0;
        }
        fill_packet->unk_0A = rect_y;
        fill_packet->unk_0C = clip_rect->unk_04;
        fill_packet->unk_00.at00.v = (fill_packet->unk_00.at00.v & tag_mask) |
                                 (order_table->unk_00 & 0x00FFFFFFU);
        order_table->unk_00 = (order_table->unk_00 & tag_mask) |
                            ((u32)fill_packet & 0x00FFFFFFU);
    }

    packet_page = page_ptr->draw_buffer;
    clip_packet = packet_page->unk_8D0;
    packet_page->unk_8D0 = clip_packet + 0xC;
    SetDrawArea(clip_packet, clip_rect);
    ((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 = (((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 & 0xFF000000U) |
                            (order_table->unk_00 & 0x00FFFFFFU);
    order_table->unk_00 = (order_table->unk_00 & 0xFF000000U) |
                        ((u32)clip_packet & 0x00FFFFFFU);
}
