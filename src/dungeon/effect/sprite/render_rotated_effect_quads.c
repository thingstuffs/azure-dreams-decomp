/* Rotated sprite scanline rendering and clipping rectangle setup. */
#include "shared/sprite_frame_state.h"
#include "engine/graphics/sprite_scratch.h"
#include "dungeon/effect/sprite/render_rotated_effect_quads.h"
#include "shared/game_work.h"
#include "dungeon/effect/sprite.h"

/* Projects rotated sprite parts as waving scanline quads and links their packets into the ordering table. */
void render_rotated_effect_quads(void *screen_pos, void *effect, s32 *ordering_tag, u32 draw_mode)
{
    s32 quad_copies[20];
    u16 saved_draw_mode;
    u32 shifted_mode;
    s32 callback_arg;
    s32 *copy_end;
    u32 addr_mask;
    s32 draw_arg;
    u8 *render_state;
    MATRIX *view_matrix;
    s32 texture_word;
    void *render_context;
    void *final_context;
    s32 base_rotation;
    s32 packet_mask;
    u8 flipped_x;
    u8 origin_x;
    u8 origin_y;
    u8 flipped_y;
    s32 row_index;
    s32 clut_offset;
    s32 tpage_offset;
    s16 mirrored_x;
    s16 quad_x;
    s16 mirrored_y;
    s16 quad_y;
    s32 wave_phase;
    u8 *(*draw_callback)(void *, s32, void *, void *, u8 *);
    s32 *row_tag;
    s32 *start_tag;
    s32 *end_tag;
    u8 *restore_arg;
    u8 *packet;
    s32 draw_callback_arg;
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
    void *frame;
    void *row_effect;
    u8 *frame_data;
    SpriteFrameState *sprite;
    void *setup_arg;
    u8 *context_addr;
    s32 packet_low;
    setup_arg = screen_pos;
    sprite = *((void **) (((s8 *) effect) + (-0x14)));
    callback_arg = *((s32 *) (((s8 *) effect) + (-0x18)));
    render_context = g_game_work.draw_buffer;
    render_state = (u8 *)&g_game_work;
    frame = sprite->source;
    scratch = (SpriteQuadScratch *)0x1F800000;
    scratch->local_matrix.t[2] = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    packet = *((u8 **) (((s8 *) render_context) + 0x8D0));
    scratch->ordering_table = (u32 *)ordering_tag;
    scratch->sort_depth = 0;
    scratch->screen_origin.x = (u16) ((*((u16 *) (((s8 *) setup_arg) + 0))) - 0xA0);
    scratch->screen_origin.y = (u16) ((*((u16 *) (((s8 *) setup_arg) + 2))) - 0x78);
    saved_draw_mode = (u16) draw_mode;
    shifted_mode = draw_mode << 0x10;
    draw_arg = 0;
    if (shifted_mode != 0) {
        func_80067EF4(packet, draw_arg, draw_arg, shifted_mode);
        packet_mask = 0xFFFFFF;
        draw_arg = 0xFF000000;
        *((s32 *) packet) = ((*((s32 *) packet)) & 0xFF000000) | ((*scratch->ordering_table) & packet_mask);
        start_tag = (s32 *)scratch->ordering_table;
        setup_arg = (void *) (((s32) packet) & packet_mask);
        packet += 0xC;
        *start_tag = ((*start_tag) & 0xFF000000) | ((s32) setup_arg);
    }
    copy_end = &quad_copies[8];
    addr_mask = 0xFFFFFF;
    view_matrix = &effect_view_matrix;
    view_matrix->t[2] = (s32) (*((s32 *) (((s8 *) render_state) + 0xA0)));
    PushMatrix((s32) setup_arg, draw_arg);
    view_axis_x = *((s16 *) (((s8 *) render_state) + 0xC4));
    view_axis_y = *((s16 *) (((s8 *) render_state) + 0xC6));
    view_axis_z = *((s16 *) (((s8 *) render_state) + 0xC8));
    scratch->input.vx = view_axis_x;
    scratch->input.vy = view_axis_y;
    scratch->input.vz = view_axis_z;
    scratch->angles.vx = (u16) (sprite->angle_x);
    scratch->angles.vz = (s16) ((sprite->angle_z) - ((u16)scratch->input.vy));
    base_rotation = sprite->angle_y;
    scratch->angles.vy = (s16) ((((((u16)scratch->input.vz) + 0x100) & 0x1FF) - 0x100)
        + base_rotation);
    pivot_x = sprite->offset_x;
    scratch->local_matrix.t[0] = pivot_x;
    scratch->extent_x = pivot_x;
    pivot_y = sprite->offset_y;
    scratch->local_matrix.t[1] = pivot_y;
    scratch->extent_y = pivot_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    scratch->input.vx = (s32) (sprite->scale_x);
    scratch->input.vy = (s32) (sprite->scale_y);
    scratch->input.vz = 0x1000;
    ScaleMatrix(&scratch->local_matrix, &scratch->input);
    CompMatrix(view_matrix, &scratch->local_matrix, &scratch->matrix);
    SetTransMatrix(&scratch->matrix);
    SetRotMatrix(&scratch->matrix);
    scratch->sprite_flags = (u16) (sprite->flags);
    do {
    frame_data = frame + 8;
    if (!((*((u8 *) (((s8 *) frame) + 0))) & 0x20)) {
        scratch->uv_u_start = (s32) (*((u8 *) (((s8 *) frame_data) + 0)));
        scratch->uv_v_start = (s32) (*((u8 *) (((s8 *) frame_data) + 1)));
        scratch->uv_u_extent = (s32) (*((u8 *) (((s8 *) frame_data) + 2)));
        scratch->uv_v_extent = (s32) (*((u8 *) (((s8 *) frame_data) + 3)));
        if (((*((u8 *) (((s8 *) frame) + 0))) ^ (scratch->sprite_flags)) & 1) {
            flipped_x = *((u8 *) (((s8 *) frame_data) + (-6)));
            mirrored_x = (0 - ((s8) flipped_x)) - (scratch->extent_x);
            scratch->vertices[2].vx = mirrored_x;
            scratch->vertices[0].vx = mirrored_x;
            mirrored_x = mirrored_x - ((u16)scratch->uv_u_extent);
            scratch->vertices[3].vx = mirrored_x;
            scratch->vertices[1].vx = mirrored_x;
        }
        else {
            origin_x = *((u8 *) (((s8 *) frame_data) + (-6)));
            quad_x = ((s8) origin_x) - (scratch->extent_x);
            scratch->vertices[2].vx = quad_x;
            scratch->vertices[0].vx = quad_x;
            quad_x = quad_x + ((u16)scratch->uv_u_extent);
            scratch->vertices[3].vx = quad_x;
            scratch->vertices[1].vx = quad_x;
        }
        if (((*((u8 *) (((s8 *) frame) + 0))) ^ (scratch->sprite_flags)) & 2) {
            flipped_y = *((u8 *) (((s8 *) frame_data) + (-5)));
            mirrored_y = (0 - ((s8) flipped_y)) - (scratch->extent_y);
            scratch->vertices[1].vy = mirrored_y;
            scratch->vertices[0].vy = mirrored_y;
            mirrored_y = mirrored_y - ((u16)scratch->uv_v_extent);
            scratch->vertices[3].vy = mirrored_y;
            scratch->vertices[2].vy = mirrored_y;
        }
        else {
            origin_y = *((u8 *) (((s8 *) frame_data) + (-5)));
            quad_y = ((s8) origin_y) - (scratch->extent_y);
            scratch->vertices[1].vy = quad_y;
            scratch->vertices[0].vy = quad_y;
            quad_y = quad_y + ((u16)scratch->uv_v_extent);
            scratch->vertices[3].vy = quad_y;
            scratch->vertices[2].vy = quad_y;
        }
        RotTransPers4(&scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
            (s32 *)&scratch->projected_vertices[0], (s32 *)&scratch->projected_vertices[1],
            (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3], &scratch->depth_cue, &scratch->gte_flag);
        *((s16 *) (((s8 *) packet) + 8)) = (s16) ((scratch->projected_vertices[0].x) + (scratch->screen_origin.x));
        *((s16 *) (((s8 *) packet) + 0xA)) = (s16) ((scratch->projected_vertices[0].y)
            + (scratch->screen_origin.y));
        *((s16 *) (((s8 *) packet) + 0x10)) = (s16) ((scratch->projected_vertices[1].x)
            + (scratch->screen_origin.x));
        *((s16 *) (((s8 *) packet) + 0x12)) = (s16) ((scratch->projected_vertices[1].y)
            + (scratch->screen_origin.y));
        *((s16 *) (((s8 *) packet) + 0x18)) = (s16) ((scratch->projected_vertices[2].x)
            + (scratch->screen_origin.x));
        *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((scratch->projected_vertices[2].y)
            + (scratch->screen_origin.y));
        *((s16 *) (((s8 *) packet) + 0x20)) = (s16) ((scratch->projected_vertices[3].x)
            + (scratch->screen_origin.x));
        projected_y = scratch->projected_vertices[3].y;
        screen_y = scratch->screen_origin.y;
        *((((s8 *) packet) + 3)) = 9;
        *((s16 *) (((s8 *) packet) + 0x22)) = (s16) (projected_y + screen_y);
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
                *((u16 *) (((s8 *) packet) + 0xE)) = (u16) clut_offset;
            } else {
            texture_word = clut_offset + (*((u16 *) (((s8 *) frame_data) + (-2))));
            *((u16 *) (((s8 *) packet) + 0xE)) = (u16) texture_word;
            }
        }
        else {
            *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (*((u16 *) (((s8 *) frame_data) + (-2))));
        }
        *((s16 *) (((s8 *) packet) + 0xC)) = (s16) (((u16) ((u16)scratch->uv_v_start))
            + ((u16) ((u16)scratch->uv_u_start)));
        *((s16 *) (((s8 *) packet) + 0x14)) = (s16) (((u16) ((u16)scratch->uv_v_start))
            + ((u16) ((u16)scratch->uv_u_extent)));
        ;
        ;
        tpage_offset = sprite->tpage_abr;
        if (tpage_offset != 0) {
            *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (tpage_offset + ((*((u16 *) (((s8 *) frame_data)
                + (-4)))) & 0xFF9F));
        }
        else {
            *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (*((u16 *) (((s8 *) frame_data) + (-4))));
        }
        *((s16 *) (((s8 *) packet) + 0x1C)) = (s16) (((u16) ((u16)scratch->uv_v_extent))
            | ((u16) ((u16)scratch->uv_u_start)));
        *((s16 *) (((s8 *) packet) + 0x24)) = (s16) (((u16) ((u16)scratch->uv_v_extent))
            | ((u16) ((u16)scratch->uv_u_extent)));
        left_x = *((s16 *) (((s8 *) packet) + 8));
        if ((*((s16 *) (((s8 *) packet) + 0x20))) < left_x) {
            right_u = *((u8 *) (((s8 *) packet) + 0x24));
            *((u8 *) (((s8 *) packet) + 0x24)) = (u8) (right_u + 0xFF);
            *((u8 *) (((s8 *) packet) + 0x14)) = right_u;
        }
        edge_value = *((s16 *) (((s8 *) packet) + 0xA));
        if ((*((s16 *) (((s8 *) packet) + 0x22))) < edge_value) {
            draw_flags = *((u8 *) (((s8 *) packet) + 0x25));
            *((u8 *) (((s8 *) packet) + 0x25)) = (u8) (draw_flags + 0xFF);
            *((u8 *) (((s8 *) packet) + 0x1D)) = draw_flags;
        }
        prim_code = *((u8 *) (((s8 *) frame_data) + (-7)));
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
        *((s32 *) (((s8 *) packet) + 4)) = (s32) (sprite->color.word);
        *((Blk40 *) quad_copies) = *((Blk40 *) packet);
        {
            Blk16 *copy_dst = (Blk16 *) (&quad_copies[10]);
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
            *((((s8 *) packet) + 0x3)) = 9;
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
            *((u16 *) (((s8 *) packet) + 0x8)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x8)))
                + (((s32) (wave_value * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            *((u16 *) (((s8 *) packet) + 0x10)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x10)))
                + (((s32) (rsin(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            wave_phase = wave_phase + (*((s16 *) (((s8 *) effect) + 0x8E)));
            if (wave_phase >= 0x1001) {
                wave_phase -= 0x1000;
            }
            *((u16 *) (((s8 *) packet) + 0x18)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x18)))
                + (((s32) (rsin(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            *((u16 *) (((s8 *) packet) + 0x20)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x20)))
                + (((s32) (rsin(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
            *((u16 *) (((s8 *) packet) + 0xA)) = ((Row_818EC800_QuadTail *) quad_copies)->y;
            *((u16 *) (((s8 *) packet) + 0x12)) = ((Row_818EC800_QuadTail *) quad_copies)->y;
            *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) (((Row_818EC800_QuadTail *) quad_copies)->y + 1);
            *((s16 *) (((s8 *) packet) + 0x22)) = (s16) (((Row_818EC800_QuadTail *) quad_copies)->y + 1);
            *((u8 *) (((s8 *) packet) + 0xD)) = *((u8 *) (((s8 *) quad_copies) + 53));
            *((u8 *) (((s8 *) packet) + 0x15)) = *((u8 *) (((s8 *) quad_copies) + 53));
            row_index += 1;
            *((((s8 *) packet) + 0x1D)) = (s8) ((*((u8 *) (((s8 *) quad_copies) + 53))) + 1);
            *((((s8 *) packet) + 0x25)) = (s8) ((*((u8 *) (((s8 *) quad_copies) + 53))) + 1);
            {
                s32 link_lower;
                s32 tag_high;
                tag_high = (*((s32 *)packet) & 0xFF000000);
                link_lower = (*scratch->ordering_table) & addr_mask;
                *((s32 *)packet) = tag_high | link_lower;
            }
            row_tag = (s32 *)scratch->ordering_table;
            {
                s32 link_lower;
                s32 tag_high;
                tag_high = (*row_tag & 0xFF000000);
                link_lower = (s32)packet & addr_mask;
                *row_tag = tag_high | link_lower;
            }
            *((Blk40 *) (&quad_copies[10])) = *((Blk40 *) packet);
            next_row_y = (*((u16 *) (((s8 *) quad_copies) + 50))) + 1;
            *((u16 *) (((s8 *) quad_copies) + 50)) = next_row_y;
            *((u8 *) (((s8 *) quad_copies) + 53)) += 1;
            wave_phase = wave_phase + (*((s16 *) (((s8 *) effect) + 0x8E)));
            packet += 0x28;
            if (wave_phase >= 0x1001) {
                wave_phase -= 0x1000;
            }
        }
        while (((s16) next_row_y) < (*((s16 *) (((s8 *) quad_copies) + 26))));
    }
    else {
        draw_callback = (u8 *(*)(void *, s32, void *, void *, u8 *)) (*((s32 *) (((s8 *) frame_data) + 0)));
        if (draw_callback != 0) {
            draw_callback_arg = callback_arg;
            packet = draw_callback(effect, draw_callback_arg, sprite, frame, packet);
        }
    }
    if (((s8) (*((u8 *) (((s8 *) frame) + 0)))) < 0) break;
    frame = ((u8 *) frame) + 0xC;
    } while (1);
    restore_arg = packet;
    if ((saved_draw_mode << 0x10) != 0) {
        func_80067EF4(restore_arg, 0, 1);
        *((s32 *) packet) = ((*((s32 *) packet)) & 0xFF000000) | ((*scratch->ordering_table) & 0xFFFFFF);
        end_tag = (s32 *)scratch->ordering_table;
        restore_arg = (u8 *) (((s32) packet) & 0xFFFFFF);
        packet += 0xC;
        *end_tag = ((*end_tag) & 0xFF000000) | ((s32) restore_arg);
    }
    PopMatrix((s32) restore_arg);
    packet_low = (s32) ((u16) ((s32) packet));
    context_addr = render_state + (packet_low & 0x10000);
    final_context = *((void **) (((s8 *) context_addr) + 0));
    *((s32 **) (((s8 *) final_context) + 0x8D0)) = packet;
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
