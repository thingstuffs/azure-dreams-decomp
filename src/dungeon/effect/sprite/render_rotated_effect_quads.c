/* Rotated sprite scanline rendering and clipping rectangle setup. */
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/render_rotated_effect_quads.h"
#include "shared/game_work.h"

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
    u8 *view_matrix;
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
    ScratchPad *scratch;
    void *frame;
    void *row_effect;
    u8 *frame_data;
    void *sprite;
    void *setup_arg;
    u8 *context_addr;
    s32 packet_low;
    setup_arg = screen_pos;
    sprite = *((void **) (((s8 *) effect) + (-0x14)));
    callback_arg = *((s32 *) (((s8 *) effect) + (-0x18)));
    render_context = g_game_work.draw_buffer;
    render_state = (u8 *) (((struct S_8003E2D8 *)&g_game_work));
    frame = *((void **) (((s8 *) sprite) + 8));
    scratch = (ScratchPad *)0x1F800000;
    scratch->sw[59] = 0;
    scratch->h[70] = 0;
    scratch->h[66] = 0;
    scratch->h[62] = 0;
    scratch->h[58] = 0;
    packet = *((u8 **) (((s8 *) render_context) + 0x8D0));
    scratch->sw[8] = (s32) ordering_tag;
    scratch->sw[48] = 0;
    scratch->h[92] = (u16) ((*((u16 *) (((s8 *) setup_arg) + 0))) - 0xA0);
    scratch->h[93] = (u16) ((*((u16 *) (((s8 *) setup_arg) + 2))) - 0x78);
    saved_draw_mode = (u16) draw_mode;
    shifted_mode = draw_mode << 0x10;
    draw_arg = 0;
    if (shifted_mode != 0) {
        func_80067EF4(packet, draw_arg, draw_arg, shifted_mode);
        packet_mask = 0xFFFFFF;
        draw_arg = 0xFF000000;
        *((s32 *) packet) = ((*((s32 *) packet)) & 0xFF000000) | ((*((s32 *) (scratch->sw[8]))) & packet_mask);
        start_tag = (s32 *) (scratch->sw[8]);
        setup_arg = (void *) (((s32) packet) & packet_mask);
        packet += 0xC;
        *start_tag = ((*start_tag) & 0xFF000000) | ((s32) setup_arg);
    }
    copy_end = &quad_copies[8];
    addr_mask = 0xFFFFFF;
    view_matrix = (u8 *) (&D_8006CD10);
    *((s32 *) (((s8 *) view_matrix) + 0x1C)) = (s32) (*((s32 *) (((s8 *) render_state) + 0xA0)));
    PushMatrix((s32) setup_arg, draw_arg);
    view_axis_x = *((s16 *) (((s8 *) render_state) + 0xC4));
    view_axis_y = *((s16 *) (((s8 *) render_state) + 0xC6));
    view_axis_z = *((s16 *) (((s8 *) render_state) + 0xC8));
    scratch->sw[12] = view_axis_x;
    scratch->sw[13] = view_axis_y;
    scratch->sw[14] = view_axis_z;
    scratch->h[128] = (u16) (*((u16 *) (((s8 *) sprite) + 0x16)));
    scratch->h[130] = (s16) ((*((u16 *) (((s8 *) sprite) + 0x1A))) - (scratch->h[26]));
    base_rotation = *((u16 *) (((s8 *) sprite) + 0x18));
    scratch->h[129] = (s16) (((((scratch->h[28]) + 0x100) & 0x1FF) - 0x100)
        + base_rotation);
    pivot_x = *((u16 *) (((s8 *) sprite) + 0x20));
    scratch->sw[57] = pivot_x;
    scratch->h[132] = pivot_x;
    pivot_y = *((u16 *) (((s8 *) sprite) + 0x22));
    scratch->sw[58] = pivot_y;
    scratch->h[133] = pivot_y;
    RotMatrix(0x1F800100, 0x1F8000D0);
    scratch->sw[12] = (s32) (*((u16 *) (((s8 *) sprite) + 0x1C)));
    scratch->sw[13] = (s32) (*((u16 *) (((s8 *) sprite) + 0x1E)));
    scratch->sw[14] = 0x1000;
    ScaleMatrix(0x1F8000D0, 0x1F800030);
    CompMatrix(view_matrix, 0x1F8000D0, 0x1F800050);
    SetTransMatrix(0x1F800050);
    SetRotMatrix(0x1F800050);
    scratch->h[18] = (u16) (*((u16 *) (((s8 *) sprite) + 0x14)));
    do {
    frame_data = frame + 8;
    if (!((*((u8 *) (((s8 *) frame) + 0))) & 0x20)) {
        scratch->sw[2] = (s32) (*((u8 *) (((s8 *) frame_data) + 0)));
        scratch->sw[3] = (s32) (*((u8 *) (((s8 *) frame_data) + 1)));
        scratch->sw[4] = (s32) (*((u8 *) (((s8 *) frame_data) + 2)));
        scratch->sw[5] = (s32) (*((u8 *) (((s8 *) frame_data) + 3)));
        if (((*((u8 *) (((s8 *) frame) + 0))) ^ (scratch->h[18])) & 1) {
            flipped_x = *((u8 *) (((s8 *) frame_data) + (-6)));
            mirrored_x = (0 - ((s8) flipped_x)) - (scratch->h[132]);
            scratch->h[64] = mirrored_x;
            scratch->h[56] = mirrored_x;
            mirrored_x = mirrored_x - (scratch->h[8]);
            scratch->h[68] = mirrored_x;
            scratch->h[60] = mirrored_x;
        }
        else {
            origin_x = *((u8 *) (((s8 *) frame_data) + (-6)));
            quad_x = ((s8) origin_x) - (scratch->h[132]);
            scratch->h[64] = quad_x;
            scratch->h[56] = quad_x;
            quad_x = quad_x + (scratch->h[8]);
            scratch->h[68] = quad_x;
            scratch->h[60] = quad_x;
        }
        if (((*((u8 *) (((s8 *) frame) + 0))) ^ (scratch->h[18])) & 2) {
            flipped_y = *((u8 *) (((s8 *) frame_data) + (-5)));
            mirrored_y = (0 - ((s8) flipped_y)) - (scratch->h[133]);
            scratch->h[61] = mirrored_y;
            scratch->h[57] = mirrored_y;
            mirrored_y = mirrored_y - (scratch->h[10]);
            scratch->h[69] = mirrored_y;
            scratch->h[65] = mirrored_y;
        }
        else {
            origin_y = *((u8 *) (((s8 *) frame_data) + (-5)));
            quad_y = ((s8) origin_y) - (scratch->h[133]);
            scratch->h[61] = quad_y;
            scratch->h[57] = quad_y;
            quad_y = quad_y + (scratch->h[10]);
            scratch->h[69] = quad_y;
            scratch->h[65] = quad_y;
        }
        RotTransPers4((u8 *)scratch + 0x70, (u8 *)scratch + 0x78, (u8 *)scratch + 0x80, (u8 *)scratch + 0x88, (u8 *)scratch + 0xF0, (u8 *)scratch + 0xF4,
            (u8 *)scratch + 0xF8, (u8 *)scratch + 0xFC, (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);
        *((s16 *) (((s8 *) packet) + 8)) = (s16) ((scratch->h[120]) + (scratch->h[92]));
        *((s16 *) (((s8 *) packet) + 0xA)) = (s16) ((scratch->h[121])
            + (scratch->h[93]));
        *((s16 *) (((s8 *) packet) + 0x10)) = (s16) ((scratch->h[122])
            + (scratch->h[92]));
        *((s16 *) (((s8 *) packet) + 0x12)) = (s16) ((scratch->h[123])
            + (scratch->h[93]));
        *((s16 *) (((s8 *) packet) + 0x18)) = (s16) ((scratch->h[124])
            + (scratch->h[92]));
        *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((scratch->h[125])
            + (scratch->h[93]));
        *((s16 *) (((s8 *) packet) + 0x20)) = (s16) ((scratch->h[126])
            + (scratch->h[92]));
        projected_y = scratch->h[127];
        screen_y = scratch->h[93];
        *((s8 *) (((s8 *) packet) + 3)) = 9;
        *((s16 *) (((s8 *) packet) + 0x22)) = (s16) (projected_y + screen_y);
        width_minus_one = (scratch->sw[4]) - 1;
        edge_value = width_minus_one + (scratch->sw[2]);
        scratch->sw[4] = edge_value;
        if (edge_value & 0x100) {
            scratch->sw[4] = edge_value - 1;
        }
        height_minus_one = (scratch->sw[5]) - 1;
        bottom_v = height_minus_one + (scratch->sw[3]);
        scratch->sw[5] = bottom_v;
        if (bottom_v & 0x100) {
            scratch->sw[5] = bottom_v - 1;
        }
        scratch->sw[5] <<= 8;
        scratch->sw[3] <<= 8;
        clut_offset = *((u16 *) (((s8 *) sprite) + 0x12));
        if (clut_offset != 0) {
            if ((scratch->h[18]) & 0x100) {
                *((u16 *) (((s8 *) packet) + 0xE)) = (u16) clut_offset;
            } else {
            texture_word = clut_offset + (*((u16 *) (((s8 *) frame_data) + (-2))));
            *((u16 *) (((s8 *) packet) + 0xE)) = (u16) texture_word;
            }
        }
        else {
            *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (*((u16 *) (((s8 *) frame_data) + (-2))));
        }
        *((s16 *) (((s8 *) packet) + 0xC)) = (s16) (((u16) (scratch->h[6]))
            + ((u16) (scratch->h[4])));
        *((s16 *) (((s8 *) packet) + 0x14)) = (s16) (((u16) (scratch->h[6]))
            + ((u16) (scratch->h[8])));
        ;
        ;
        tpage_offset = *((u16 *) (((s8 *) sprite) + 0x10));
        if (tpage_offset != 0) {
            *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (tpage_offset + ((*((u16 *) (((s8 *) frame_data)
                + (-4)))) & 0xFF9F));
        }
        else {
            *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (*((u16 *) (((s8 *) frame_data) + (-4))));
        }
        *((s16 *) (((s8 *) packet) + 0x1C)) = (s16) (((u16) (scratch->h[10]))
            | ((u16) (scratch->h[4])));
        *((s16 *) (((s8 *) packet) + 0x24)) = (s16) (((u16) (scratch->h[10]))
            | ((u16) (scratch->h[8])));
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
        *((u8 *) (((s8 *) sprite) + 0xF)) = prim_code;
        draw_flags = scratch->h[18];
        if (draw_flags & 8) {
            if (draw_flags & 4) {
                *((u8 *) (((s8 *) sprite) + 0xF)) = prim_code | 2;
            }
            else {
                *((u8 *) (((s8 *) sprite) + 0xF)) = prim_code & 0xFD;
            }
        }
        *((s32 *) (((s8 *) packet) + 4)) = (s32) (*((s32 *) (((s8 *) sprite) + 0xC)));
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
            *((s8 *) (((s8 *) packet) + 0x3)) = 9;
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
            *((s8 *) (((s8 *) packet) + 0x1D)) = (s8) ((*((u8 *) (((s8 *) quad_copies) + 53))) + 1);
            *((s8 *) (((s8 *) packet) + 0x25)) = (s8) ((*((u8 *) (((s8 *) quad_copies) + 53))) + 1);
            {
                s32 link_lower;
                s32 tag_high;
                tag_high = (*((s32 *)packet) & 0xFF000000);
                link_lower = (*((s32 *)(scratch->sw[8]))) & addr_mask;
                *((s32 *)packet) = tag_high | link_lower;
            }
            row_tag = (s32 *) (scratch->sw[8]);
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
        *((s32 *) packet) = ((*((s32 *) packet)) & 0xFF000000) | ((*((s32 *) (scratch->sw[8]))) & 0xFFFFFF);
        end_tag = (s32 *) (scratch->sw[8]);
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
    u8 *order_table;
    void *draw_page;
    Row_818ED25C_S_80024A5C_3 *packet_page;
    s16 offset_y;
    void *call_pos;
    s32 call_data;
    void *call_order_table;
    s32 call_param;

    draw_page = g_game_work.draw_buffer;
    pos_or_ot = screen_pos;
    clip_packet = ((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8D0;
    offset_y = draw_page != (void *)upper_draw_context;
    ((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8D0 = clip_packet + 0xC;
    saved_param = draw_param;
    clear_enabled = clear_rect;
    page_ptr = &g_game_work;
    SetDrawArea(clip_packet, g_game_work.draw_buffer);
    tag_mask = 0xFF000000U;

    ((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 = (((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 & tag_mask) |
                            (((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8B0 & 0x00FFFFFFU);
    ((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8B0 = (((Row_818ED25C_S_80024A5C_0 *)draw_page)->unk_8B0 & tag_mask) |
                             ((u32)clip_packet & 0x00FFFFFFU);

    draw_pos[0] = ((Row_818ED25C_S_80024A5C_2 *)pos_or_ot)->unk_00;
    draw_y = ((Row_818ED25C_S_80024A5C_2 *)pos_or_ot)->unk_02;
    pos_or_ot = (u8 *)draw_page + 0x8B0;
    order_table = pos_or_ot;
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
        u8 *fill_packet;

        packet_page = g_game_work.draw_buffer;
        fill_packet = packet_page->unk_8D0;
        packet_page->unk_8D0 = fill_packet + 0x10;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_04 = 0x60000000;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_00.at03.v = 3;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_08 = clip_rect->unk_00;
        rect_y = clip_rect->unk_02;
        if (offset_y != 0) {
            rect_y -= 0xE0;
        }
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_0A = rect_y;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_0C = clip_rect->unk_04;
        ((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_00.at00.v = (((Row_818ED25C_S_80024A5C_4 *)fill_packet)->unk_00.at00.v & tag_mask) |
                                 (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & 0x00FFFFFFU);
        ((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 = (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & tag_mask) |
                            ((u32)fill_packet & 0x00FFFFFFU);
    }

    packet_page = page_ptr->draw_buffer;
    clip_packet = packet_page->unk_8D0;
    packet_page->unk_8D0 = clip_packet + 0xC;
    SetDrawArea(clip_packet, clip_rect);
    ((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 = (((Row_818ED25C_S_80024A5C_1 *)clip_packet)->unk_00 & 0xFF000000U) |
                            (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & 0x00FFFFFFU);
    ((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 = (((Row_818ED25C_S_80024A5C_6 *)order_table)->unk_00 & 0xFF000000U) |
                        ((u32)clip_packet & 0x00FFFFFFU);
}
