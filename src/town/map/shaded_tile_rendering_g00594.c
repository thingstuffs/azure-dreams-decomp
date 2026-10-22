#include "shared/sprite_frame_state.h"
/* Shaded tile rendering (G00594). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AF9D8, PD:town/engine:800D1548. */
#include "town/map/shaded_tile_rendering_g00594.h"
#include "shared/game_work.h"

/* Set texture coordinates, page, and palette for a 32-by-32 quad. */
void set_texture_quad_32_uv(s16 texture_page, s16 palette, s8 texture_u, s8 texture_v) {
    s8 right_u;
    s8 bottom_v;

    map_tile_uvs[8] = texture_u;
    map_tile_uvs[0] = texture_u;
    right_u = texture_u + 0x1F;
    map_tile_uvs[5] = texture_v;
    map_tile_uvs[1] = texture_v;
    bottom_v = texture_v + 0x1F;
    map_tile_uvs[0xA] = right_u;
    map_tile_uvs[4] = right_u;
    map_tile_uvs[0xB] = bottom_v;
    map_tile_uvs[9] = bottom_v;
    *(s16 *)&map_tile_uvs[6] = texture_page;
    *(s16 *)&map_tile_uvs[2] = palette;
}

/* Render visible town map tiles as shaded polygons in the ordering table. */
void render_shaded_map_tiles(void) {
    s32 width_shift;
    s32 tile_index;
    s32 height_shift;
    s32 max_column;
    s32 max_row;
    s32 flat_color;
    s32 base_color;
    void *ordering_table;
    u8 draw_mode;
    u32 draw_flags;
    s32 *depth_bucket;
    s8 *vertices;
    s8 *normals;
    s32 tile_id;
    s32 tile_flags;
    s32 next_x;
    s32 row_progress;
    s32 edge_x;
    s32 span_x;
    s32 edge_error;
    s32 stepped_x;
    s32 span_end_x;
    s32 row_index;
    s32 work_bits;
    s32 work_value;
    u16 half_y;
    s32 y_shift;
    s32 column_rounding;
    void * lookup_value;
    s32 edge_index;
    s8 *tile_map;
    s32 row_rounding;
    u16 normal_index;
    S_func_800AED64_14 *packet;
    void *view_bounds;
    S_func_800AED64_2 *map_data;
    S_func_800AED64_10 *tile_uvs;
    S_func_800AED64_13 *polygon;
    s32 x_step;
    u32 error_step;
    s32 row_limit;
    void *work_ptr;
    void *coord_offset;
    void *edge_count;
    S_func_800AED64_6 *render_buffer;
    u32 tag_low_mask;
    u32 tag_high_mask;
    s32 one;
    ScratchAddress scratch;
    register void *vertex_input;
    GameWork *render_state;

    render_state = (S_func_800AED64_1 *)&g_game_work;
    map_data = (u8 *)render_state + 0x1DC;
    tile_map = render_state->map.cells;
    vertices = map_data->unk_08;
    normals = map_data->unk_0C;
    func_80064D50((u8 *)render_state + 0x70);
    {
        S_func_800AED64_3 *view_params;
        view_params = (u8 *)render_state + 0x18;
        func_80064624(view_params->unk_84, view_params->unk_88);
    }
    scratch = (ScratchAddress){ (S_func_800AED64_4 *)0x1F800000 };
    func_80064D20((u8 *)render_state + 0x50);
    if (map_wide_culling[0] != 0) {
        render_state->view.clip_y = -0xB8;
        render_state->view.clip_height = 0x1DA;
    } else {

        render_state->view.clip_y = -0x88;
        render_state->view.clip_height = 0x1AA;
    }
    view_bounds = (u8 *)render_state + 0x20;
    build_screen_outline((u8 *)render_state + 0x18, view_bounds, 0);
    work_ptr = view_bounds;
    coord_offset = (void *) (scratch.address | 0x1C);
    base_color = *(s32 *)&render_state->view.tint.word;
    edge_count = (void *) (scratch.address | 0x174);
    scratch.ptr->unk_00 = base_color;
    ordering_table = render_state->draw_buffer;
    width_shift = map_data->unk_14;
    height_shift = map_data->unk_16;
    max_column = map_data->unk_18;
    max_row = map_data->unk_1A;
    {
        S_func_800AED64_5 *draw_settings;
        draw_settings = (u8 *)0x80010000;
        flat_color = draw_settings->unk_3180;
        draw_mode = draw_settings->unk_3184;
        draw_flags = draw_settings->unk_3185;
    }
    ordering_table += 0xB0;
    scratch.ptr->unk_124 = (s32) width_shift;
    ((S_func_800AED64_4 *)(scratch.ptr))->unk_178 = draw_flags;
    scratch.ptr->unk_BC = ordering_table;
    scratch.ptr->unk_128 = (s32) height_shift;
    scratch.ptr->unk_114 = 0x40 << scratch.ptr->unk_124;
    scratch.ptr->unk_11C = (s32) max_column;
    scratch.ptr->unk_120 = (s32) max_row;
    scratch.ptr->unk_110 = flat_color;
    scratch.ptr->unk_176 = draw_mode;
    render_buffer = render_state->draw_buffer;
    scratch.ptr->unk_118 = 0x40 << scratch.ptr->unk_128;
    packet = render_buffer->unk_8D0;
    scratch.ptr->unk_14C = 0xFFFF;
    scratch.ptr->unk_174 = 4;
    scratch.ptr->unk_164 = (u8 *) packet + 0xCCCC;
    scratch.ptr->unk_0C = (s16) runtime_initialize_polygon_edges((s32) work_ptr, (s32 *) coord_offset, (u16 *) edge_count);
    if (scratch.ptr->unk_174 != 0) {
        one = 1;
        vertex_input = &scratch.ptr->unk_E0;
        tile_uvs = (S_func_800AED64_10 *)map_tile_uvs;
        tag_low_mask = 0xFFFFFF;
        tag_high_mask = 0xFF000000;
        do {
            for (edge_index = 3; edge_index >= 0; edge_index--) {
                if (scratch.ptr->edges[edge_index].unk_1C == 0) {
                    work_bits = scratch.ptr->edges[edge_index].unk_18;
                    work_value = scratch.ptr->unk_0C;
                    work_value = work_value < work_bits;
                    if (!work_value) {
                        scratch.ptr->edges[edge_index].unk_1C = one;
                    }
                }
            }
            scratch.ptr->unk_14.s32 = 0x7FFF;
            scratch.ptr->unk_18 = -0x7FFF;
            for (edge_index = 3; edge_index >= 0; edge_index--) {
                if (scratch.ptr->edges[edge_index].unk_1C > 0) {
                    edge_x = scratch.ptr->edges[edge_index].unk_00;
                    scratch.ptr->unk_08 = edge_x;
                    if (edge_x < scratch.ptr->unk_14.s32) {
                        scratch.ptr->unk_14.s32 = edge_x;
                    }
                    span_x = scratch.ptr->unk_08;
                    if (scratch.ptr->unk_18 < span_x) {
                        scratch.ptr->unk_18 = span_x;
                    }
                    edge_error = scratch.ptr->edges[edge_index].unk_10 + scratch.ptr->edges[edge_index].unk_08;
                    scratch.ptr->edges[edge_index].unk_10 = edge_error;
                    if (edge_error >= 0) {
                        x_step = scratch.ptr->edges[edge_index].unk_14;
                        error_step = scratch.ptr->edges[edge_index].unk_04;
                        do {
                            work_value = scratch.ptr->edges[edge_index].unk_00;
                            work_bits = scratch.ptr->edges[edge_index].unk_20;
                            work_value += x_step;
                            scratch.ptr->edges[edge_index].unk_00 = work_value;
                            work_value = scratch.ptr->edges[edge_index].unk_10;
                            work_bits -= 0x40;
                            scratch.ptr->edges[edge_index].unk_20 = work_bits;
                            work_value -= error_step;
                            scratch.ptr->edges[edge_index].unk_10 = work_value;
                        } while (work_bits > 0 && work_value >= 0);
                    }
                    stepped_x = scratch.ptr->edges[edge_index].unk_00;
                    scratch.ptr->unk_08 = stepped_x;
                    if (stepped_x < scratch.ptr->unk_14.s32) {
                        scratch.ptr->unk_14.s32 = stepped_x;
                    }
                    span_end_x = scratch.ptr->unk_08;
                    if (scratch.ptr->unk_18 < span_end_x) {
                        scratch.ptr->unk_18 = span_end_x;
                    }
                }
            }
            scratch.ptr->unk_14.s32 = (scratch.ptr->unk_14.s32 - 0x20) & ~0x3F;
            scratch.ptr->unk_18 = (scratch.ptr->unk_18 + 0x20) & ~0x3F;
            column_rounding = scratch.ptr->unk_14.s32;
            if (column_rounding < 0) {
                column_rounding += 0x3F;
            }
            row_rounding = scratch.ptr->unk_0C;
            scratch.ptr->unk_134 = column_rounding >> 6;
            row_index = (row_rounding / 64);
            scratch.ptr->unk_138 = row_index;
            if (row_index < 0) {
                scratch.ptr->unk_138 = 0;
            } else {
                row_limit = scratch.ptr->unk_120;
                if (row_index >= row_limit) {
                    work_value = row_limit << scratch.ptr->unk_124;
                } else {
                    work_value = row_index << scratch.ptr->unk_124;
                }
                scratch.ptr->unk_138 = work_value;
            }

            work_bits = scratch.ptr->unk_14.s32;
            work_value = scratch.ptr->unk_18;
            work_value = work_value < work_bits;
            if (!work_value) {
                while (1) {
                    work_bits = scratch.ptr->unk_134;
                    if (work_bits < 0) {
                        work_value = scratch.ptr->unk_138;
                        work_bits &= 3;
                        work_value += work_bits;
                        scratch.ptr->unk_144 = work_value;
                    } else {
                        lookup_value = scratch.ptr->unk_11C;
                        if (work_bits >= (s32) lookup_value) {
                            work_value = scratch.ptr->unk_138;
                            work_bits &= 3;
                            work_value += (s32) lookup_value;
                            work_value += work_bits;
                            work_value -= 3;
                            scratch.ptr->unk_144 = work_value;
                        } else {
                            work_value = scratch.ptr->unk_138;
                            work_value += work_bits;
                            scratch.ptr->unk_144 = work_value;
                        }
                    }
                    tile_id = ((MapTileHalfView *)(tile_map
                        + (scratch.ptr->unk_144 * 2)))->unk_00 & 0x3FFF;
                    scratch.ptr->unk_C0 = tile_id;
                    if (tile_id != 0) {
                        tile_flags = ((MapTileHalfView *)(tile_map + (scratch.ptr->unk_144 * 2)))->unk_00 & 0xC000;
                        scratch.ptr->unk_17C = tile_flags;
                        if (tile_flags != 0) {
                            scratch.ptr->unk_FC = 0;
                            scratch.ptr->unk_F4 = 0;
                            scratch.ptr->unk_EC = 0;
                            scratch.ptr->unk_E4.s16 = 0;
                            scratch.ptr->unk_E0 = (u16) scratch.ptr->unk_14.s32 | (scratch.ptr->unk_0C << 0x10);
                            scratch.ptr->unk_E8 = ((u16) (scratch.ptr->unk_14.s32 + 0x40))
                                | (scratch.ptr->unk_0C << 0x10);
                            scratch.ptr->unk_F0 = (u16) scratch.ptr->unk_14.s32 | ((scratch.ptr->unk_0C + 0x40) << 0x10);
                            scratch.ptr->unk_F8 = ((u16) (scratch.ptr->unk_14.s32 + 0x40))
                                | ((scratch.ptr->unk_0C + 0x40) << 0x10);
                            gte_ldv3(vertex_input, (u8 *)scratch.ptr + 0xE8, (u8 *)scratch.ptr + 0xF0);
                            packet->unk_04.s32 = 0x2C404040;
                            gte_rtpt_nn();
                            gte_avsz3();
                            gte_stotz((u8 *)scratch.ptr + 0xC8);
                            gte_stsxy3_g3(packet);
                            gte_ldv0((u8 *)scratch.ptr + 0xF8);
                            packet->unk_0C = (s32) ((s32 *)map_tile_uvs)[0];
                            gte_rtps_nn();
                            gte_stsxy(&packet->unk_20);
                            packet->unk_14 = (s32) tile_uvs->unk_04;
                            packet->unk_1C = (u16) tile_uvs->unk_08;
                            packet->unk_24 = (u16) tile_uvs->unk_0A;
                            gte_stszotz((u8 *)scratch.ptr + 0xD4);
                            work_ptr = (void *)scratch.ptr->unk_D4;
                            work_value = scratch.ptr->unk_C8;
                            work_bits = work_value << 1;
                            work_value += work_bits;
                            work_value += (s32)work_ptr;
                            work_value += 3;
                            work_value >>= 2;
                            work_value += 4;
                            scratch.ptr->unk_C8 = work_value;
                            if ((u32)work_value >= 0x200U) {
                                scratch.ptr->unk_C8 = 0x1FF;
                            }
                            packet->unk_03 = 9;
                            *(s32 *)packet = (s32) ((*(s32 *)packet & tag_high_mask)
                                | (((S_func_800AED64_11 *)((s8 *)scratch.ptr->unk_BC
                                + (scratch.ptr->unk_C8 * 4)))->unk_00 & tag_low_mask));
                            depth_bucket = (scratch.ptr->unk_C8 * 4) + scratch.ptr->unk_BC;
                            *depth_bucket = (*depth_bucket & tag_high_mask) | ((s32) packet & tag_low_mask);
                            packet++;
                        }
                        tile_index = scratch.ptr->unk_C0;

                        scratch.ptr->unk_12C.s32 = 0;
                        polygon = ((S_func_800AED64_12 *)((s8 *)map_data->unk_04 + (tile_index * 4)))->unk_00;
                        for (;;) {
                            if (polygon->unk_0C != 0) {
                                work_value = polygon->unk_10;
                                work_ptr = (void *) (u32) scratch.ptr->unk_14.u16;
                                scratch.ptr->unk_170.s32 = work_value;
                                work_value = polygon->unk_00;
                                work_bits = polygon->unk_14.s32;
                                work_value <<= 3;
                                work_value += (s32) vertices;
                                scratch.ptr->unk_16C.s32 = work_bits;
                                work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                                work_bits = scratch.ptr->unk_12C.u16;
                                scratch.ptr->unk_168.s32 = work_value;
                                work_value = polygon->unk_00;
                                coord_offset = (void *) (u32) scratch.ptr->unk_168.u16;
                                work_value <<= 3;
                                work_value += (s32) vertices;
                                work_ptr = (void *) ((u32) work_ptr + (u32) coord_offset);
                                work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                                work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                                work_value -= work_bits;
                                scratch.ptr->unk_E4.s16 = work_value;
                                work_value = scratch.ptr->unk_168.at_16A.unk_16A;
                                work_bits = scratch.ptr->unk_0C;
                                y_shift = work_value << 0x10;
                                work_value = polygon->unk_02;
                                y_shift >>= 0x10;
                                work_bits += y_shift;
                                work_bits <<= 0x10;
                                work_ptr = (void *) ((u32) work_ptr | (u32) work_bits);
                                scratch.ptr->unk_E0 = (s32) work_ptr;
                                work_ptr = (void *) (u32) scratch.ptr->unk_14.u16;
                                work_bits = scratch.ptr->unk_12C.u16;
                                work_value <<= 3;
                                work_value += (s32) vertices;
                                work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                                scratch.ptr->unk_168.s32 = work_value;
                                work_value = polygon->unk_02;
                                coord_offset = (void *) (u32) scratch.ptr->unk_168.u16;
                                work_value <<= 3;
                                work_value += (s32) vertices;
                                work_ptr = (void *) ((u32) work_ptr + (u32) coord_offset);
                                work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                                work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                                work_value -= work_bits;
                                scratch.ptr->unk_EC = work_value;
                                work_value = scratch.ptr->unk_168.at_16A.unk_16A;
                                work_bits = scratch.ptr->unk_0C;
                                y_shift = work_value << 0x10;
                                work_value = polygon->unk_04;
                                y_shift >>= 0x10;
                                work_bits += y_shift;
                                work_bits <<= 0x10;
                                work_ptr = (void *) ((u32) work_ptr | (u32) work_bits);
                                scratch.ptr->unk_E8 = (s32) work_ptr;
                                work_ptr = (void *) (u32) scratch.ptr->unk_14.u16;
                                work_value <<= 3;
                                work_value += (s32) vertices;
                                work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                                scratch.ptr->unk_168.s32 = work_value;
                                work_value = scratch.ptr->unk_168.u16;
                                half_y = ((volatile S_func_800AED64_4 *)(scratch.ptr))->unk_168.at_16A.unk_16A;
                                work_bits = half_y;
                                work_ptr = (void *) ((u32) work_ptr + (u32) work_value);
                                work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                                work_bits <<= 0x10;
                                work_value = scratch.ptr->unk_0C;
                                work_bits >>= 0x10;
                                work_value += work_bits;
                                work_value <<= 0x10;
                                work_ptr = (void *) ((u32) work_ptr | (u32) work_value);
                                scratch.ptr->unk_F0 = (s32) work_ptr;
                                work_value = polygon->unk_04;
                                work_value <<= 3;
                                work_value += (s32) vertices;
                                work_bits = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                                work_value = scratch.ptr->unk_12C.u16;
                                work_bits -= work_value;
                                scratch.ptr->unk_F4 = work_bits;
                                gte_ldv3(vertex_input, (u8 *)scratch.ptr + 0xE8, (u8 *)scratch.ptr + 0xF0);
                                gte_rtpt();
                                gte_nclip();
                                gte_stopz((u8 *)scratch.ptr + 0xDC);
                                if (scratch.ptr->unk_DC >= 0) {
                                    work_value = polygon->unk_06;
                                    work_value <<= 3;
                                    work_value += (s32) vertices;
                                    work_bits = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                                    work_value = scratch.ptr->unk_12C.u16;
                                    work_bits -= work_value;
                                    scratch.ptr->unk_FC = work_bits;
                                    gte_stsxy3_g3(packet);
                                    gte_avsz3();
                                    gte_stotz((u8 *)scratch.ptr + 0xC8);
                                    normal_index = (u16) scratch.ptr->unk_170.s32;
                                    if (scratch.ptr->unk_14C != normal_index) {
                                        scratch.ptr->unk_14C = (s32) normal_index;
                                        gte_ldrgb(scratch.ptr);
                                        gte_ldv0(normals + (normal_index * 8));
                                        gte_nccs();
                                        gte_strgb((u8 *)scratch.ptr + 4);
                                    }
                                    work_value = polygon->unk_06;
                                    work_ptr = (void *) (u32) scratch.ptr->unk_14.u16;
                                    work_value <<= 3;
                                    work_value += (s32) vertices;
                                    work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                                    scratch.ptr->unk_168.s32 = work_value;
                                    work_value = scratch.ptr->unk_168.u16;
                                    half_y = ((volatile S_func_800AED64_4 *)(scratch.ptr))->unk_168.at_16A.unk_16A;
                                    work_bits = half_y;
                                    work_ptr = (void *) ((u32) work_ptr + (u32) work_value);
                                    work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                                    work_bits <<= 0x10;
                                    work_value = scratch.ptr->unk_0C;
                                    work_bits >>= 0x10;
                                    work_value += work_bits;
                                    work_value <<= 0x10;
                                    work_ptr = (void *) ((u32) work_ptr | (u32) work_value);
                                    scratch.ptr->unk_F8 = (s32) work_ptr;
                                    gte_ldv0((u8 *)scratch.ptr + 0xF8);
                                    packet->unk_0C = (s32) polygon->unk_08;
                                    gte_rtps_nn();
                                    packet->unk_14 = (s32) polygon->unk_0C;
                                    packet->unk_1C = scratch.ptr->unk_170.at_172.unk_172;
                                    packet->unk_24 =
                                        (u16) scratch.ptr->unk_16C.s32;
                                    gte_stsxy(&packet->unk_20);
                                    gte_stszotz((u8 *)scratch.ptr + 0xD4);
                                    work_ptr = (void *)scratch.ptr->unk_D4;
                                    work_value = scratch.ptr->unk_C8;
                                    work_bits = work_value << 1;
                                    work_value += work_bits;
                                    work_value += (s32)work_ptr;
                                    work_value += 3;
                                    work_value >>= 2;
                                    scratch.ptr->unk_C8 = work_value;
                                    if ((u32) work_value >= 0x200U) {
                                        scratch.ptr->unk_C8 = 0x1FF;
                                    }
                                    if ((((s32) scratch.ptr->unk_C8 < 0x1C1) || ((s32) (scratch.ptr->unk_E4.u16 << 0x10) >= 0)
                                        || ((work_value = scratch.ptr->unk_14C, work_value <<= 3,
                                        work_ptr = (void *)(work_value + (s32)normals), lookup_value = work_ptr,
                                        (((S_func_800AED64_16 *)(lookup_value))->unk_04 < 0))
                                        && !(((S_func_800AED64_16 *)(lookup_value))->unk_00 & 0x0FFF0FFF)))
                                        && ((u32) scratch.ptr->unk_C8 < 0x200U)) {
                                        packet->unk_03 = 9;
                                        packet->unk_04.s32 =
                                            (s32) scratch.ptr->unk_04;
                                        if (scratch.ptr->unk_16C.at_16F.unk_16F & 1) {
                                            packet->unk_04.at_07.unk_07 |= 2;
                                        } else {
                                            work_value = 0xC000;
                                            work_bits = scratch.ptr->unk_17C;
                                            work_bits &= 0xC000;
                                            if (work_bits == work_value) {
                                                work_value = packet->unk_10;
                                                work_bits = packet->unk_18;
                                                work_ptr = packet->unk_20;
                                                packet->unk_0C = work_value;
                                                packet->unk_10 = work_bits;
                                                packet->unk_14 =
                                                    (s32) work_ptr;
                                                work_bits = scratch.ptr->unk_110;
                                                work_value = 5;
                                                packet->unk_03 = work_value;
                                                packet->unk_04.s32 =
                                                    work_bits;
                                                work_value = scratch.ptr->unk_C8;
                                                work_bits = scratch.ptr->unk_BC;
                                                work_value <<= 2;
                                                work_value += work_bits;
                                                work_bits = *(s32 *)packet;
                                                work_value = ((S_func_800AED64_11 *)((void *)work_value))->unk_00;
                                                work_bits &= tag_high_mask;
                                                work_value &= tag_low_mask;
                                                work_bits |= work_value;
                                                *(s32 *)packet = work_bits;
                                                work_ptr = (void *)scratch.ptr->unk_C8;
                                                work_ptr = (void *)((s32)work_ptr * 4);
                                                work_value = scratch.ptr->unk_BC;
                                                work_ptr = (void *)((s32)work_ptr + work_value);
                                                work_value = (s32) packet & tag_low_mask;
                                                work_bits = ((S_func_800AED64_11 *)(work_ptr))->unk_00;
                                                packet++;
                                                work_bits &= tag_high_mask;
                                                work_bits |= work_value;
                                                ((S_func_800AED64_11 *)(work_ptr))->unk_00 = work_bits;
                                                packet->unk_03 = one;
                                                work_bits = scratch.ptr->unk_176;
                                                work_value = 0xE1000000;
                                                work_bits &= 0x9FF;
                                                work_bits |= work_value;
                                                packet->unk_04.s32 =
                                                    work_bits;
                                            }
                                        }

                                        work_value = scratch.ptr->unk_C8;
                                        work_bits = scratch.ptr->unk_BC;
                                        work_value <<= 2;
                                        work_value += work_bits;
                                        work_bits = *(s32 *)packet;
                                        work_value = ((S_func_800AED64_11 *)((void *)work_value))->unk_00;
                                        work_bits &= tag_high_mask;
                                        work_value &= tag_low_mask;
                                        work_bits |= work_value;
                                        *(s32 *)packet = work_bits;
                                        work_ptr = (void *)scratch.ptr->unk_C8;
                                        work_ptr = (void *)((s32)work_ptr * 4);
                                        work_value = scratch.ptr->unk_BC;
                                        work_ptr = (void *)((s32)work_ptr + work_value);
                                        work_bits = ((S_func_800AED64_11 *)(work_ptr))->unk_00;
                                        work_value = (s32) packet & tag_low_mask;
                                        packet++;
                                        work_bits &= tag_high_mask;
                                        work_bits |= work_value;
                                        ((S_func_800AED64_11 *)(work_ptr))->unk_00 = work_bits;
                                        work_bits = scratch.ptr->unk_16C.at_16E.unk_16E;
                                        if ((work_bits & 0xF) == one) {
                                            work_value = scratch.ptr->unk_16C.at_16F.unk_16F;
                                            work_value <<= 0x18;
                                            if (work_value >= 0) {
                                                work_bits = (u32) work_bits >> 4;
                                                work_value = work_bits * 3;
                                                work_value *= 8;
                                                work_value += 0x18;
                                                polygon = (s8 *) (u8 *)polygon + work_value;
                                                continue;
                                            }
                                            break;
                                        }
                                        polygon = (s8 *) (u8 *)polygon + 0x18;
                                        continue;
                                    }
                                    break;
                                }
                                if (((S_func_800AED64_16 *)((((u16) scratch.ptr->unk_170.s32 * 8) + normals)))->unk_04 < 0) {
                                    if (scratch.ptr->unk_16C.at_16E.unk_16E != one
                                        || (s32) scratch.ptr->unk_16C.at_16F.unk_16F << 0x18 >= 0) {
                                        polygon = (s8 *) (u8 *)polygon + 0x18;
                                        continue;
                                    }
                                    break;
                                }
                                work_bits = scratch.ptr->unk_16C.at_16E.unk_16E;
                                if ((work_bits & 0xF0) || (s32) scratch.ptr->unk_16C.at_16F.unk_16F << 0x18 >= 0) {
                                    work_bits &= 0xF;
                                    work_value = work_bits * 3;
                                    work_value *= 8;
                                    polygon = (s8 *) (u8 *)polygon + work_value;
                                    continue;
                                }
                                break;
                            }
                            if (polygon->unk_14.at_16.unk_16 != one || polygon->unk_14.at_17.unk_17 >= 0) {
                                polygon = (s8 *) (u8 *)polygon + 0x18;
                                continue;
                            }
                            break;
                        }
                        if ((u32) scratch.ptr->unk_164 < packet) {
                            ((S_func_800AED64_6 *)(render_state->draw_buffer))->unk_8D0 = packet;
                            {
                                S_func_800AED64_17 *scene_state;
                                scene_state = map_runtime_state;
                                if ((scene_state->unk_18 == 0xC) && ((u32) (scene_state->unk_1A - 0x25) >= 5U)
                                    && ((s16) scene_state->unk_1A != 0x34)) {
                                    draw_empty_map_cell_quads(scratch.ptr->unk_164);
                                }
                            }
                            return;
                        }
                    }
                    scratch.ptr->unk_134 += 1;
                    next_x = scratch.ptr->unk_14.s32 + 0x40;
                    scratch.ptr->unk_14.s32 = next_x;
                    if (scratch.ptr->unk_18 < next_x) {
                        break;
                    }
                }
            }
            row_progress = scratch.ptr->unk_0C;
            row_progress += 0x40;
            scratch.ptr->unk_0C = row_progress;
            for (edge_index = 3, column_rounding = -1; edge_index >= 0; edge_index--) {
                if (scratch.ptr->edges[edge_index].unk_1C > 0) {
                    row_progress = scratch.ptr->edges[edge_index].unk_0C - 0x40;
                    scratch.ptr->edges[edge_index].unk_0C = row_progress;
                    if (row_progress <= 0) {
                        scratch.ptr->edges[edge_index].unk_1C = column_rounding;
                        scratch.ptr->unk_174 = scratch.ptr->unk_174 - 1;
                    }
                }
            }
        } while (scratch.ptr->unk_174 != 0);
    }
    ((S_func_800AED64_6 *)(render_state->draw_buffer))->unk_8D0 = packet;
    {
        S_func_800AED64_17 *scene_state;
        scene_state = map_runtime_state;
        if ((scene_state->unk_18 == 0xC) && ((u32) (scene_state->unk_1A - 0x25) >= 5U)
            && ((s16) scene_state->unk_1A != 0x34)) {
            draw_empty_map_cell_quads(scratch.ptr->unk_164);
        }
    }
}

/* Draw textured quads for empty cells in the visible map region. */
void draw_empty_map_cell_quads(u32 packet_limit)
{
    u8 *scratch;
    u8 *state;
    u8 *map_bounds;
    u8 *render_state;
    u8 *edge_buffer;
    u8 *packet_fields;
    u16 *cell_table;
    u32 addr_mask;
    u32 length_mask;
    s32 edge_active;
    u8 *vertices;
    s32 initial_size;
    s32 edge_count_addr;
    s32 draw_rect[2];
    s32 x_shift;
    s32 y_shift;
    s32 map_height;
    s32 bound_x;
    s32 bound_y;
    s32 edge_index;
    s32 cell_x;
    s32 uv_bottom;
    s32 packet_addr;
    s32 min_x;
    s32 x;
    s32 row;
    s32 row_bound;
    s32 row_base;
    s32 col_bound;
    s32 edge_error;
    s32 shade_factor;
    s32 x_step;
    s32 error_step;
    u8 *edge_base;
    Slot800AF9D8 *edge;
    s32 cell_index;
    s32 tri_avg;
    s32 twice_avg;
    s32 last_value;
    u16 bottom_y;
    s32 rows_left;
    s32 uv_scroll;
    s32 uv_left;
    s32 uv_right;
    s32 uv_top;
    s32 v_scroll;
    s32 next_x;
    u32 red;
    s16 *clip_vertices;
    s32 vertex_z;
    s32 top_y;
    s32 coord_copy;
    u16 cell_id;
    u16 vertex_x;
    s32 *packet;
    s32 edge_done;
    s32 chain_addr;
    s32 packet_tag;
    s32 chain_tag;

    edge_buffer = (u8 *)0;
    edge_count_addr = (s32)edge_buffer;
    scratch = (u8 *)0x1F800000;

    ((MapQuadScratch *)scratch)->normal_z = -0x1000;

    state = ((u8 *)(&g_game_work));
    map_bounds = state + 0x1DC;
    ((MapQuadScratch *)scratch)->normal_x = 0;
    ((MapQuadScratch *)scratch)->normal_y = 0;
    render_state = g_game_work.draw_buffer;
    x_shift = ((S_800AD138_0 *)map_bounds)->unk_14;
    initial_size = 0x01000100;
    y_shift = ((S_800AD138_0 *)map_bounds)->unk_16;
    chain_addr = (s32)(render_state + 0x8AC);
    ((MapQuadScratch *)scratch)->chain_address = chain_addr;
    ((MapQuadScratch *)scratch)->y_shift = y_shift;
    ((MapQuadScratch *)scratch)->x_shift = x_shift;
    ((MapQuadScratch *)scratch)->step_x = 0x40 << x_shift;
    bound_x = ((S_800AD138_0 *)map_bounds)->unk_18;
    bound_y = ((S_800AD138_0 *)map_bounds)->unk_1A;
    uv_scroll = (((S_800AD138_1 *)state)->unk_04 >> 1) & 0x3F;
    map_height = 0x40 << y_shift;
    ((MapQuadScratch *)scratch)->step_y = map_height;
    ((MapQuadScratch *)scratch)->map_width = bound_x;
    ((MapQuadScratch *)scratch)->map_height = bound_y;
    ((MapQuadScratch *)scratch)->uv_scroll.value = uv_scroll;

    packet = ((S_800AD138_5 *)render_state)->unk_8D0;
    ((MapQuadScratch *)scratch)->color = ((S_800AD138_1 *)state)->unk_A8;
    draw_rect[0] = 0;
    draw_rect[1] = initial_size;
    cell_table = ((S_800AD138_1 *)state)->unk_1DC;
    func_80067F20(packet, (s32)edge_buffer, edge_count_addr, 0x20, draw_rect);
    func_8006658C((void *)((MapQuadScratch *)scratch)->chain_address, packet);
    packet += 3;
    ((MapQuadScratch *)scratch)->edge_count = 4;
    clip_vertices = (s16 *)(state + 0x20);
    edge_buffer = scratch;
    edge_buffer = (u8 *)((u32)edge_buffer | 0x1C);
    edge_count_addr = (s32)scratch;
    edge_count_addr |= 0x170;
    ((MapQuadScratch *)scratch)->scan_y.value =
        (s16)runtime_initialize_polygon_edges((s32)clip_vertices,
                      (s32 *)edge_buffer,
                      (u16 *)edge_count_addr);

    if (((MapQuadScratch *)scratch)->edge_count != 0) {
        edge_active = 1;
        vertices = scratch;
        vertices = (u8 *)((u32)vertices | 0xE0);
        addr_mask = 0x00FFFFFF;
        length_mask = 0xFF000000;
        do {
            edge_index = 3;
            do {
                if ((((MapQuadScratch *)scratch)->edges[edge_index].active == 0) &&
                    (((MapQuadScratch *)scratch)->edges[edge_index].start_y <= ((MapQuadScratch *)scratch)->scan_y.value)) {
                    ((MapQuadScratch *)scratch)->edges[edge_index].active = edge_active;
                }
                edge_index--;
            } while (edge_index >= 0);

            edge_index = 3;
            ((MapQuadScratch *)scratch)->min_x.value = 0x7FFF;
            ((MapQuadScratch *)scratch)->max_x = -0x7FFF;
            do {
                if (((MapQuadScratch *)scratch)->edges[edge_index].active > 0) {
                    x = ((MapQuadScratch *)scratch)->edges[edge_index].position;
                    ((MapQuadScratch *)scratch)->edge_x = x;
                    if (x < ((MapQuadScratch *)scratch)->min_x.value) {
                        ((MapQuadScratch *)scratch)->min_x.value = x;
                    }
                    x = ((MapQuadScratch *)scratch)->edge_x;
                    if (((MapQuadScratch *)scratch)->max_x < x) {
                        ((MapQuadScratch *)scratch)->max_x = x;
                    }
                    edge_error = ((MapQuadScratch *)scratch)->edges[edge_index].error + ((MapQuadScratch *)scratch)->edges[edge_index].error_step;
                    ((MapQuadScratch *)scratch)->edges[edge_index].error = edge_error;
                    if (edge_error >= 0) {

                        edge_base = scratch + edge_index * 0x28;
                        edge = (Slot800AF9D8 *)edge_base;
                        x_step = edge->increment;
                        error_step = edge->decrement;
                        do {
                            edge->position += x_step;
                            edge->phase -= 0x40;
                            edge->remaining -= error_step;
                        } while ((edge->phase > 0) &&
                                 (edge->remaining >= 0));
                    }
                    x = ((MapQuadScratch *)scratch)->edges[edge_index].position;
                    ((MapQuadScratch *)scratch)->edge_x = x;
                    if (x < ((MapQuadScratch *)scratch)->min_x.value) {
                        ((MapQuadScratch *)scratch)->min_x.value = x;
                    }
                    x = ((MapQuadScratch *)scratch)->edge_x;
                    if (((MapQuadScratch *)scratch)->max_x < x) {
                        ((MapQuadScratch *)scratch)->max_x = x;
                    }
                }
                edge_index--;
            } while (edge_index >= 0);

            ((MapQuadScratch *)scratch)->min_x.value =
                (((MapQuadScratch *)scratch)->min_x.value - 0x20) & ~0x3F;
            ((MapQuadScratch *)scratch)->max_x =
                (((MapQuadScratch *)scratch)->max_x + 0x20) & ~0x3F;
            min_x = ((MapQuadScratch *)scratch)->min_x.value;
            if (min_x < 0) {
                min_x += 0x3F;
            }
            row = ((MapQuadScratch *)scratch)->scan_y.value;
            ((MapQuadScratch *)scratch)->cell_x = min_x >> 6;
            if (row < 0) {
                row += 0x3F;
            }
            row >>= 6;
            ((MapQuadScratch *)scratch)->row_base = row;
            if (row < 0) {
                ((MapQuadScratch *)scratch)->row_base = 0;
            } else {
                row_bound = ((MapQuadScratch *)scratch)->map_height;
                if (row >= row_bound) {
                    row_base = row_bound << ((MapQuadScratch *)scratch)->x_shift;
                } else {
                    row_base = row << ((MapQuadScratch *)scratch)->x_shift;
                }
                ((MapQuadScratch *)scratch)->row_base = row_base;
            }

            edge_index = 3;
            if (((MapQuadScratch *)scratch)->min_x.value <= ((MapQuadScratch *)scratch)->max_x) {
                do {
                    packet_fields = (u8 *)packet + 7;
                    cell_x = ((MapQuadScratch *)scratch)->cell_x;
                    if (cell_x < 0) {
                        cell_index = ((MapQuadScratch *)scratch)->row_base;
                        cell_x &= 3;
                        cell_index += cell_x;
                        ((MapQuadScratch *)scratch)->cell_index = cell_index;
                    } else {
                        col_bound = ((MapQuadScratch *)scratch)->map_width;
                        if (cell_x >= col_bound) {
                            cell_index = ((MapQuadScratch *)scratch)->row_base;
                            cell_x &= 3;
                            cell_index += col_bound;
                            cell_index += cell_x;
                            cell_index -= 3;
                            ((MapQuadScratch *)scratch)->cell_index = cell_index;
                        } else {
                            cell_index = ((MapQuadScratch *)scratch)->row_base;
                            cell_index += cell_x;
                            ((MapQuadScratch *)scratch)->cell_index = cell_index;
                        }
                    }
                    cell_id = cell_table[((MapQuadScratch *)scratch)->cell_index];
                    ((MapQuadScratch *)scratch)->shade = cell_id;
                    if (cell_id == 0) {
                        vertex_x = ((MapQuadScratch *)scratch)->min_x.low_half;
                        top_y = ((MapQuadScratch *)scratch)->scan_y.low_half;
                        ((MapQuadScratch *)scratch)->vertices[3].z = 0;
                        ((MapQuadScratch *)scratch)->vertices[2].z = 0;
                        ((MapQuadScratch *)scratch)->vertices[1].z = 0;
                        ((MapQuadScratch *)scratch)->vertices[0].z = 0;
                        bottom_y = top_y;
                        coord_copy = top_y;
                        top_y = coord_copy;
                        top_y = coord_copy;
                        top_y = coord_copy;
                        coord_copy = vertex_x;
                        vertex_x = coord_copy;
                        vertex_x = coord_copy;
                        vertex_x = coord_copy;
                        coord_copy = 0;
                        ((MapQuadScratch *)scratch)->vertices[2].x = vertex_x;
                        ((MapQuadScratch *)scratch)->vertices[0].x = vertex_x;
                        vertex_x += 0x40;
                        bottom_y += 0x40;
                        ((MapQuadScratch *)scratch)->vertices[3].x = vertex_x;
                        ((MapQuadScratch *)scratch)->vertices[1].x = vertex_x;
                        ((MapQuadScratch *)scratch)->vertices[3].y = bottom_y;
                        ((MapQuadScratch *)scratch)->vertices[2].y = bottom_y;
                        ((MapQuadScratch *)scratch)->vertices[1].y = top_y;
                        ((MapQuadScratch *)scratch)->vertices[0].y = top_y;

                        gte_ldv3(vertices, scratch + 0xE8, scratch + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz(scratch + 0xDC);
                        if (((MapQuadScratch *)scratch)->clip_area > 0) {
                            gte_stsxy3_g3(packet);
                            gte_stdp(scratch + 0xC0);
                            gte_avsz3();
                            gte_stotz(scratch + 0xC8);
                            gte_ldv0(scratch + 0xF8);
                            gte_rtps();
                            gte_stsxy((u8 *)packet + 0x20);
                            gte_stdp(scratch + 0xC4);
                            gte_stszotz(scratch + 0xD4);

                            tri_avg = ((MapQuadScratch *)scratch)->depth;
                            last_value = ((MapQuadScratch *)scratch)->last_depth;
                            twice_avg = tri_avg << 1;
                            ((MapQuadScratch *)scratch)->depth =
                                (tri_avg + twice_avg + last_value + 3) >> 2;
                            if ((u32)((MapQuadScratch *)scratch)->depth >= 0x1E0U) {
                                ((MapQuadScratch *)scratch)->depth = 0x1DF;
                            }
                            tri_avg = ((MapQuadScratch *)scratch)->shade;
                            last_value = ((MapQuadScratch *)scratch)->last_shade;
                            twice_avg = tri_avg << 1;
                            ((MapQuadScratch *)scratch)->shade =
                                (tri_avg + twice_avg + last_value) >> 2;

                            gte_ldv0(scratch + 0x17C);
                            gte_ldrgb(scratch);
                            vertex_z = ((MapQuadScratch *)scratch)->vertices[3].z;
                            vertex_z = (s16)vertex_z;
                            shade_factor = 0;
                            if (vertex_z > 0) {
                                shade_factor = vertex_z << 2;
                            }
                            gte_ldir0(shade_factor);
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_00 = 9;
                            gte_ncds_nn();
                            gte_strgb((u8 *)packet + 4);

                            uv_left = ((MapQuadScratch *)scratch)->uv_scroll.low_byte;
                            ((S_800AD138_2 *)packet_fields)->unk_15 = uv_left;
                            ((S_800AD138_2 *)packet_fields)->unk_05 = uv_left;
                            uv_right = ((MapQuadScratch *)scratch)->uv_scroll.low_byte + 0x3F;
                            ((S_800AD138_2 *)packet_fields)->unk_1D = uv_right;
                            ((S_800AD138_2 *)packet_fields)->unk_0D = uv_right;
                            uv_top = -(s32)((MapQuadScratch *)scratch)->uv_scroll.low_byte;
                            red = ((S_800AD138_2_pre *)packet_fields)[-1].unk_01;
                            ((S_800AD138_2 *)packet_fields)->unk_0E = uv_top;
                            ((S_800AD138_2 *)packet_fields)->unk_06 = uv_top;
                            v_scroll = ((MapQuadScratch *)scratch)->uv_scroll.low_byte;
                            ((MapQuadTextureWords *)((u8 *)packet_fields - 7))->texture_page = 0x2D;
                            ((MapQuadTextureWords *)((u8 *)packet_fields - 7))->palette = 0x75C1;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_01 = red >> 1;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_02 >>= 1;
                            uv_bottom = 0x3F - v_scroll;
                            ((S_800AD138_2 *)packet_fields)->unk_1E = uv_bottom;
                            ((S_800AD138_2 *)packet_fields)->unk_16 = uv_bottom;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_03 >>= 1;
                            chain_tag = ((S_800AD138_4 *)((void *)((MapQuadScratch *)scratch)->chain_address))->unk_00;
                            packet_tag = ((S_800AD138_3 *)((u8 *)packet))->unk_00;
                            ((S_800AD138_3 *)((u8 *)packet))->unk_00 =
                                (packet_tag & length_mask) |
                                (chain_tag & addr_mask);
                            packet_addr = (s32)packet & addr_mask;
                            packet += 10;
                            ((S_800AD138_4 *)((void *)((MapQuadScratch *)scratch)->chain_address))->unk_00 =
                                (((S_800AD138_4 *)((void *)((MapQuadScratch *)scratch)->chain_address))->unk_00 & length_mask) |
                                packet_addr;
                            if (packet_limit < (u32)packet) {
                                goto done;
                            }
                        }
                    }
                    ((MapQuadScratch *)scratch)->cell_x += 1;
                    next_x = ((MapQuadScratch *)scratch)->min_x.value + 0x40;
                    ((MapQuadScratch *)scratch)->min_x.value = next_x;
                    if (((MapQuadScratch *)scratch)->max_x < next_x) {
                        break;
                    }
                } while (1);
            }

            edge_index = 3;
            edge_done = -1;
            ((MapQuadScratch *)scratch)->scan_y.value += 0x40;
            do {
                if (((MapQuadScratch *)scratch)->edges[edge_index].active > 0) {
                    rows_left = ((MapQuadScratch *)scratch)->edges[edge_index].rows_left - 0x40;
                    ((MapQuadScratch *)scratch)->edges[edge_index].rows_left = rows_left;
                    if (rows_left <= 0) {
                        ((MapQuadScratch *)scratch)->edges[edge_index].active = edge_done;
                        ((MapQuadScratch *)scratch)->edge_count -= 1;
                    }
                }
                edge_index--;
            } while (edge_index >= 0);
            edge_index = 3;
        } while (((MapQuadScratch *)scratch)->edge_count != 0);
    }

done:
    draw_rect[1] = 0x400040;
    draw_rect[0] = 0;
    func_80067F20(packet, 0, 0, 0x20, draw_rect);
    func_8006658C((void *)((MapQuadScratch *)scratch)->chain_address, packet);
    packet += 3;
    ((S_800AD138_5 *)(((S_800AD138_1 *)state)->unk_00))->unk_8D0 = packet;
    return;
}
