#include "slus/map_state.h"
#include "shared/sprite_frame_state.h"
/* Shaded tile rendering. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AF9D8, PD:town/engine:800D1548. */
#include "town/map/shaded_tile_rendering_g00594.h"
#include "town/map/wide_culling_data.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "engine/graphics/lit_mesh.h"
#include "town/map.h"
#include "engine/graphics.h"

/* Set texture coordinates, page, and palette for a 32-by-32 quad. */
void set_texture_quad_32_uv(u16 texture_page, u16 palette, u8 texture_u, u8 texture_v) {
    MapTileTextureCoords *uv = (MapTileTextureCoords *)map_tile_uvs;
    u8 right_u;
    u8 bottom_v;

    uv->u2 = texture_u;
    uv->u0 = texture_u;
    right_u = texture_u + 0x1F;
    uv->v1 = texture_v;
    uv->v0 = texture_v;
    bottom_v = texture_v + 0x1F;
    uv->u3 = right_u;
    uv->u1 = right_u;
    uv->v3 = bottom_v;
    uv->v2 = bottom_v;
    uv->tpage = texture_page;
    uv->clut = palette;
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
    S_func_800AED64_16 *lookup_value;
    s32 edge_index;
    u16 *tile_map;
    s32 row_rounding;
    u16 normal_index;
    LitMeshQuadPacket *packet;
    SVECTOR *view_bounds;
    MapGrid *map_data;
    const MapTilePacketCoords *tile_uvs;
    S_func_800AED64_13 *polygon;
    s32 x_step;
    u32 error_step;
    s32 row_limit;
    s32 fourth_depth;
    u32 packed_xy;
    S_func_800AED64_11 *work_ptr;
    void *coord_offset;
    void *edge_count;
    S_func_800AED64_6 *render_buffer;
    u32 tag_low_mask;
    u32 tag_high_mask;
    s32 one;
    ScratchAddress scratch;
    register s32 *vertex_input;
    GameWork *render_state;

    render_state = &g_game_work;
    map_data = &render_state->map;
    tile_map = render_state->map.cells;
    vertices = map_data->vertices;
    normals = map_data->surface_planes;
    SetColorMatrix(&render_state->view.color_matrix);
    {
        GameView *view_params;
        view_params = &render_state->view;
        SetFogFar(view_params->fog_far, view_params->projection_distance);
    }
    scratch = (ScratchAddress){ (S_func_800AED64_4 *)0x1F800000 };
    SetLightMatrix(&render_state->view.light_matrix);
    if (map_wide_culling[0] != 0) {
        render_state->view.clip_y = -0xB8;
        render_state->view.clip_height = 0x1DA;
    } else {

        render_state->view.clip_y = -0x88;
        render_state->view.clip_height = 0x1AA;
    }
    view_bounds = render_state->view.outline;
    build_screen_outline(&render_state->view, view_bounds, 0);
    coord_offset = (void *) (scratch.address | 0x1C);
    base_color = ((s32)(render_state->view.tint.word));
    edge_count = (void *) (scratch.address | 0x174);
    scratch.ptr->unk_00 = base_color;
    ordering_table = render_state->draw_buffer;
    width_shift = map_data->shiftX;
    height_shift = map_data->shiftY;
    max_column = map_data->maskX;
    max_row = map_data->maskY;
    {
        S_func_800AED64_5 *draw_settings;
        draw_settings = (u8 *)0x80010000;
        flat_color = draw_settings->unk_3180;
        draw_mode = draw_settings->unk_3184;
        draw_flags = draw_settings->unk_3185;
    }
    ordering_table += 0xB0;
    scratch.ptr->unk_124 = (s32) width_shift;
    (scratch.ptr)->unk_178 = draw_flags;
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
    scratch.ptr->unk_0C = (s16) init_polygon_edges(view_bounds, coord_offset, edge_count);
    if (scratch.ptr->unk_174 != 0) {
        one = 1;
        vertex_input = &scratch.ptr->unk_E0;
        tile_uvs = (const MapTilePacketCoords *)map_tile_uvs;
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
                        lookup_value = (S_func_800AED64_16 *)scratch.ptr->unk_11C;
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
                    tile_id = tile_map[scratch.ptr->unk_144] & 0x3FFF;
                    scratch.ptr->unk_C0 = tile_id;
                    if (tile_id != 0) {
                        tile_flags = tile_map[scratch.ptr->unk_144] & 0xC000;
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
                            packet->color.word = 0x2C404040;
                            gte_rtpt_nn();
                            gte_avsz3();
                            gte_stotz((u8 *)scratch.ptr + 0xC8);
                            gte_stsxy3_g3(packet);
                            gte_ldv0((u8 *)scratch.ptr + 0xF8);
                            packet->uv_clut.word = (s32) ((s32 *)map_tile_uvs)[0];
                            gte_rtps_nn();
                            gte_stsxy(&packet->xy3);
                            packet->uv_page.word = tile_uvs->uv1_tpage;
                            packet->uv2 = tile_uvs->uv2;
                            packet->uv3 = tile_uvs->uv3;
                            gte_stszotz((u8 *)scratch.ptr + 0xD4);
                            fourth_depth = scratch.ptr->unk_D4;
                            work_value = scratch.ptr->unk_C8;
                            work_bits = work_value << 1;
                            work_value += work_bits;
                            work_value += fourth_depth;
                            work_value += 3;
                            work_value >>= 2;
                            work_value += 4;
                            scratch.ptr->unk_C8 = work_value;
                            if ((u32)work_value >= 0x200U) {
                                scratch.ptr->unk_C8 = 0x1FF;
                            }
                            ((GpuLinkTag *)&packet->tag)->len = 9;
                            packet->tag = (s32) ((packet->tag & tag_high_mask)
                                | (((S_func_800AED64_11 *)((s8 *)scratch.ptr->unk_BC
                                + (scratch.ptr->unk_C8 * 4)))->unk_00 & tag_low_mask));
                            depth_bucket = (scratch.ptr->unk_C8 * 4) + scratch.ptr->unk_BC;
                            *depth_bucket = (*depth_bucket & tag_high_mask) | ((s32) packet & tag_low_mask);
                            packet++;
                        }
                        tile_index = scratch.ptr->unk_C0;

                        scratch.ptr->unk_12C.s32 = 0;
                        polygon = map_data->cell_faces[tile_index];
                        for (;;) {
                            if (polygon->unk_0C != 0) {
                                work_value = polygon->unk_10;
                                packed_xy = scratch.ptr->unk_14.u16;
                                scratch.ptr->unk_170.s32 = work_value;
                                work_value = polygon->unk_00;
                                work_bits = polygon->unk_14.s32;
                                work_value <<= 3;
                                work_value += (s32)vertices;
                                scratch.ptr->unk_16C.s32 = work_bits;
                                work_value = ((Vertex *)work_value)->value;
                                work_bits = scratch.ptr->unk_12C.u16;
                                scratch.ptr->unk_168.s32 = work_value;
                                work_value = polygon->unk_00;
                                coord_offset = (void *) (u32) scratch.ptr->unk_168.u16;
                                work_value <<= 3;
                                work_value += (s32)vertices;
                                packed_xy += (u32)coord_offset;
                                work_value = ((Vertex *)work_value)->depth;
                                packed_xy &= 0xFFFF;
                                work_value -= work_bits;
                                scratch.ptr->unk_E4.s16 = work_value;
                                work_value = scratch.ptr->unk_168.at_16A.unk_16A;
                                work_bits = scratch.ptr->unk_0C;
                                y_shift = work_value << 0x10;
                                work_value = polygon->unk_02;
                                y_shift >>= 0x10;
                                work_bits += y_shift;
                                work_bits <<= 0x10;
                                packed_xy |= work_bits;
                                scratch.ptr->unk_E0 = packed_xy;
                                packed_xy = scratch.ptr->unk_14.u16;
                                work_bits = scratch.ptr->unk_12C.u16;
                                work_value <<= 3;
                                work_value += (s32)vertices;
                                work_value = ((Vertex *)work_value)->value;
                                scratch.ptr->unk_168.s32 = work_value;
                                work_value = polygon->unk_02;
                                coord_offset = (void *) (u32) scratch.ptr->unk_168.u16;
                                work_value <<= 3;
                                work_value += (s32)vertices;
                                packed_xy += (u32)coord_offset;
                                work_value = ((Vertex *)work_value)->depth;
                                packed_xy &= 0xFFFF;
                                work_value -= work_bits;
                                scratch.ptr->unk_EC = work_value;
                                work_value = scratch.ptr->unk_168.at_16A.unk_16A;
                                work_bits = scratch.ptr->unk_0C;
                                y_shift = work_value << 0x10;
                                work_value = polygon->unk_04;
                                y_shift >>= 0x10;
                                work_bits += y_shift;
                                work_bits <<= 0x10;
                                packed_xy |= work_bits;
                                scratch.ptr->unk_E8 = packed_xy;
                                packed_xy = scratch.ptr->unk_14.u16;
                                work_value <<= 3;
                                work_value += (s32)vertices;
                                work_value = ((Vertex *)work_value)->value;
                                scratch.ptr->unk_168.s32 = work_value;
                                work_value = scratch.ptr->unk_168.u16;
                                half_y = ((volatile S_func_800AED64_4 *)(scratch.ptr))->unk_168.at_16A.unk_16A;
                                work_bits = half_y;
                                packed_xy += work_value;
                                packed_xy &= 0xFFFF;
                                work_bits <<= 0x10;
                                work_value = scratch.ptr->unk_0C;
                                work_bits >>= 0x10;
                                work_value += work_bits;
                                work_value <<= 0x10;
                                packed_xy |= work_value;
                                scratch.ptr->unk_F0 = packed_xy;
                                work_value = polygon->unk_04;
                                work_value <<= 3;
                                work_value += (s32)vertices;
                                work_bits = ((Vertex *)work_value)->depth;
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
                                    work_value += (s32)vertices;
                                    work_bits = ((Vertex *)work_value)->depth;
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
                                    packed_xy = scratch.ptr->unk_14.u16;
                                    work_value <<= 3;
                                    work_value += (s32)vertices;
                                    work_value = ((Vertex *)work_value)->value;
                                    scratch.ptr->unk_168.s32 = work_value;
                                    work_value = scratch.ptr->unk_168.u16;
                                    half_y = ((volatile S_func_800AED64_4 *)(scratch.ptr))->unk_168.at_16A.unk_16A;
                                    work_bits = half_y;
                                    packed_xy += work_value;
                                    packed_xy &= 0xFFFF;
                                    work_bits <<= 0x10;
                                    work_value = scratch.ptr->unk_0C;
                                    work_bits >>= 0x10;
                                    work_value += work_bits;
                                    work_value <<= 0x10;
                                    packed_xy |= work_value;
                                    scratch.ptr->unk_F8 = packed_xy;
                                    gte_ldv0((u8 *)scratch.ptr + 0xF8);
                                    packet->uv_clut.word = (s32) polygon->unk_08;
                                    gte_rtps_nn();
                                    packet->uv_page.word = (s32) polygon->unk_0C;
                                    packet->uv2 = scratch.ptr->unk_170.at_172.unk_172;
                                    packet->uv3 =
                                        (u16) scratch.ptr->unk_16C.s32;
                                    gte_stsxy(&packet->xy3);
                                    gte_stszotz((u8 *)scratch.ptr + 0xD4);
                                    fourth_depth = scratch.ptr->unk_D4;
                                    work_value = scratch.ptr->unk_C8;
                                    work_bits = work_value << 1;
                                    work_value += work_bits;
                                    work_value += fourth_depth;
                                    work_value += 3;
                                    work_value >>= 2;
                                    scratch.ptr->unk_C8 = work_value;
                                    if ((u32) work_value >= 0x200U) {
                                        scratch.ptr->unk_C8 = 0x1FF;
                                    }
                                    if ((((s32) scratch.ptr->unk_C8 < 0x1C1) || ((s32) (scratch.ptr->unk_E4.u16 << 0x10) >= 0)
                                        || ((work_value = scratch.ptr->unk_14C, work_value <<= 3,
                                        /* Preserve the index-first address add emitted for the normal lookup. */
                                        lookup_value = (void *)(work_value + (long)normals),
                                        (lookup_value->unk_04 < 0))
                                        && !(lookup_value->unk_00 & 0x0FFF0FFF)))
                                        && ((u32) scratch.ptr->unk_C8 < 0x200U)) {
                                        ((GpuLinkTag *)&packet->tag)->len = 9;
                                        packet->color.word =
                                            (s32) scratch.ptr->unk_04;
                                        if (scratch.ptr->unk_16C.at_16F.unk_16F & 1) {
                                            packet->color.c.code |= 2;
                                        } else {
                                            work_value = 0xC000;
                                            work_bits = scratch.ptr->unk_17C;
                                            work_bits &= 0xC000;
                                            if (work_bits == work_value) {
                                                work_value = packet->xy1;
                                                work_bits = packet->xy2;
                                                packed_xy = packet->xy3;
                                                packet->uv_clut.word = work_value;
                                                packet->xy1 = work_bits;
                                                packet->uv_page.word = packed_xy;
                                                work_bits = scratch.ptr->unk_110;
                                                work_value = 5;
                                                ((GpuLinkTag *)&packet->tag)->len = work_value;
                                                packet->color.word =
                                                    work_bits;
                                                work_value = scratch.ptr->unk_C8;
                                                work_bits = scratch.ptr->unk_BC;
                                                work_value <<= 2;
                                                work_value += work_bits;
                                                work_bits = packet->tag;
                                                work_value = ((S_func_800AED64_11 *)((void *)work_value))->unk_00;
                                                work_bits &= tag_high_mask;
                                                work_value &= tag_low_mask;
                                                work_bits |= work_value;
                                                packet->tag = work_bits;
                                                work_ptr = (void *)scratch.ptr->unk_C8;
                                                work_ptr = (void *)((s32)work_ptr * 4);
                                                work_value = scratch.ptr->unk_BC;
                                                work_ptr = (void *)((long)work_ptr + work_value);
                                                work_value = (s32) packet & tag_low_mask;
                                                work_bits = work_ptr->unk_00;
                                                packet++;
                                                work_bits &= tag_high_mask;
                                                work_bits |= work_value;
                                                work_ptr->unk_00 = work_bits;
                                                ((GpuLinkTag *)&packet->tag)->len = one;
                                                work_bits = scratch.ptr->unk_176;
                                                work_value = 0xE1000000;
                                                work_bits &= 0x9FF;
                                                work_bits |= work_value;
                                                packet->color.word =
                                                    work_bits;
                                            }
                                        }

                                        work_value = scratch.ptr->unk_C8;
                                        work_bits = scratch.ptr->unk_BC;
                                        work_value <<= 2;
                                        work_value += work_bits;
                                        work_bits = packet->tag;
                                        work_value = ((S_func_800AED64_11 *)((void *)work_value))->unk_00;
                                        work_bits &= tag_high_mask;
                                        work_value &= tag_low_mask;
                                        work_bits |= work_value;
                                        packet->tag = work_bits;
                                        work_ptr = (void *)scratch.ptr->unk_C8;
                                        work_ptr = (void *)((s32)work_ptr * 4);
                                        work_value = scratch.ptr->unk_BC;
                                        work_ptr = (void *)((long)work_ptr + work_value);
                                        work_bits = work_ptr->unk_00;
                                        work_value = (s32) packet & tag_low_mask;
                                        packet++;
                                        work_bits &= tag_high_mask;
                                        work_bits |= work_value;
                                        work_ptr->unk_00 = work_bits;
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
                                MapRuntimeState *scene_state;
                                scene_state = &map_runtime_state;
                                if ((scene_state->scene_selector == 0xC) && ((u32) ((u16)scene_state->map_index - 0x25) >= 5U)
                                    && (scene_state->map_index != 0x34)) {
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
        MapRuntimeState *scene_state;
        scene_state = &map_runtime_state;
        if ((scene_state->scene_selector == 0xC) && ((u32) ((u16)scene_state->map_index - 0x25) >= 5U)
            && (scene_state->map_index != 0x34)) {
            draw_empty_map_cell_quads(scratch.ptr->unk_164);
        }
    }
}

/* Draw textured quads for empty cells in the visible map region. */
void draw_empty_map_cell_quads(u32 packet_limit)
{
    MapQuadScratch *scratch;
    S_800AD138_1 *state;
    MapGrid *map_bounds;
    u8 *render_state;
    u8 *edge_buffer;
    S_800AD138_2 *packet_fields;
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
    SVECTOR *clip_vertices;
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

    edge_buffer = 0;
    edge_count_addr = (s32)edge_buffer;
    scratch = (MapQuadScratch *)0x1F800000;

    scratch->normal_z = -0x1000;

    state = ((S_800AD138_1 *)(&g_game_work));
    map_bounds = (MapGrid *)((u8 *)state + 0x1DC);
    scratch->normal_x = 0;
    scratch->normal_y = 0;
    render_state = g_game_work.draw_buffer;
    x_shift = map_bounds->shiftX;
    initial_size = 0x01000100;
    y_shift = map_bounds->shiftY;
    chain_addr = (s32)(render_state + 0x8AC);
    scratch->chain_address = chain_addr;
    scratch->y_shift = y_shift;
    scratch->x_shift = x_shift;
    scratch->step_x = 0x40 << x_shift;
    bound_x = map_bounds->maskX;
    bound_y = map_bounds->maskY;
    uv_scroll = (state->unk_04 >> 1) & 0x3F;
    map_height = 0x40 << y_shift;
    scratch->step_y = map_height;
    scratch->map_width = bound_x;
    scratch->map_height = bound_y;
    scratch->uv_scroll.value = uv_scroll;

    packet = ((S_800AD138_5 *)render_state)->unk_8D0;
    scratch->color = state->unk_A8;
    draw_rect[0] = 0;
    draw_rect[1] = initial_size;
    cell_table = state->unk_1DC;
    SetDrawMode(packet, (s32)edge_buffer, edge_count_addr, 0x20, draw_rect);
    AddPrim((void *)scratch->chain_address, packet);
    packet += 3;
    scratch->edge_count = 4;
    clip_vertices = g_game_work.view.outline;
    edge_buffer = scratch;
    edge_buffer = (u8 *)((u32)edge_buffer | 0x1C);
    edge_count_addr = (s32)scratch;
    edge_count_addr |= 0x170;
    scratch->scan_y.value =
        (s16)init_polygon_edges(clip_vertices,
                      (s32 *)edge_buffer,
                      (u16 *)edge_count_addr);

    if (scratch->edge_count != 0) {
        edge_active = 1;
        vertices = scratch;
        vertices = (u8 *)((u32)vertices | 0xE0);
        addr_mask = 0x00FFFFFF;
        length_mask = 0xFF000000;
        do {
            edge_index = 3;
            do {
                if ((scratch->edges[edge_index].active == 0) &&
                    (scratch->edges[edge_index].start_y <= scratch->scan_y.value)) {
                    scratch->edges[edge_index].active = edge_active;
                }
                edge_index--;
            } while (edge_index >= 0);

            edge_index = 3;
            scratch->min_x.value = 0x7FFF;
            scratch->max_x = -0x7FFF;
            do {
                if (scratch->edges[edge_index].active > 0) {
                    x = scratch->edges[edge_index].position;
                    scratch->edge_x = x;
                    if (x < scratch->min_x.value) {
                        scratch->min_x.value = x;
                    }
                    x = scratch->edge_x;
                    if (scratch->max_x < x) {
                        scratch->max_x = x;
                    }
                    edge_error = scratch->edges[edge_index].error + scratch->edges[edge_index].error_step;
                    scratch->edges[edge_index].error = edge_error;
                    if (edge_error >= 0) {

                        edge_base = (u8 *)scratch + edge_index * 0x28;
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
                    x = scratch->edges[edge_index].position;
                    scratch->edge_x = x;
                    if (x < scratch->min_x.value) {
                        scratch->min_x.value = x;
                    }
                    x = scratch->edge_x;
                    if (scratch->max_x < x) {
                        scratch->max_x = x;
                    }
                }
                edge_index--;
            } while (edge_index >= 0);

            scratch->min_x.value =
                (scratch->min_x.value - 0x20) & ~0x3F;
            scratch->max_x =
                (scratch->max_x + 0x20) & ~0x3F;
            min_x = scratch->min_x.value;
            if (min_x < 0) {
                min_x += 0x3F;
            }
            row = scratch->scan_y.value;
            scratch->cell_x = min_x >> 6;
            if (row < 0) {
                row += 0x3F;
            }
            row >>= 6;
            scratch->row_base = row;
            if (row < 0) {
                scratch->row_base = 0;
            } else {
                row_bound = scratch->map_height;
                if (row >= row_bound) {
                    row_base = row_bound << scratch->x_shift;
                } else {
                    row_base = row << scratch->x_shift;
                }
                scratch->row_base = row_base;
            }

            edge_index = 3;
            if (scratch->min_x.value <= scratch->max_x) {
                do {
                    packet_fields = (S_800AD138_2 *)((u8 *)packet + 7);
                    cell_x = scratch->cell_x;
                    if (cell_x < 0) {
                        cell_index = scratch->row_base;
                        cell_x &= 3;
                        cell_index += cell_x;
                        scratch->cell_index = cell_index;
                    } else {
                        col_bound = scratch->map_width;
                        if (cell_x >= col_bound) {
                            cell_index = scratch->row_base;
                            cell_x &= 3;
                            cell_index += col_bound;
                            cell_index += cell_x;
                            cell_index -= 3;
                            scratch->cell_index = cell_index;
                        } else {
                            cell_index = scratch->row_base;
                            cell_index += cell_x;
                            scratch->cell_index = cell_index;
                        }
                    }
                    cell_id = cell_table[scratch->cell_index];
                    scratch->shade = cell_id;
                    if (cell_id == 0) {
                        vertex_x = scratch->min_x.low_half;
                        top_y = scratch->scan_y.low_half;
                        scratch->vertices[3].z = 0;
                        scratch->vertices[2].z = 0;
                        scratch->vertices[1].z = 0;
                        scratch->vertices[0].z = 0;
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
                        scratch->vertices[2].x = vertex_x;
                        scratch->vertices[0].x = vertex_x;
                        vertex_x += 0x40;
                        bottom_y += 0x40;
                        scratch->vertices[3].x = vertex_x;
                        scratch->vertices[1].x = vertex_x;
                        scratch->vertices[3].y = bottom_y;
                        scratch->vertices[2].y = bottom_y;
                        scratch->vertices[1].y = top_y;
                        scratch->vertices[0].y = top_y;

                        gte_ldv3(vertices, (u8 *)scratch + 0xE8, (u8 *)scratch + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz((u8 *)scratch + 0xDC);
                        if (scratch->clip_area > 0) {
                            gte_stsxy3_g3(packet);
                            gte_stdp((u8 *)scratch + 0xC0);
                            gte_avsz3();
                            gte_stotz((u8 *)scratch + 0xC8);
                            gte_ldv0((u8 *)scratch + 0xF8);
                            gte_rtps();
                            gte_stsxy((u8 *)packet + 0x20);
                            gte_stdp((u8 *)scratch + 0xC4);
                            gte_stszotz((u8 *)scratch + 0xD4);

                            tri_avg = scratch->depth;
                            last_value = scratch->last_depth;
                            twice_avg = tri_avg << 1;
                            scratch->depth =
                                (tri_avg + twice_avg + last_value + 3) >> 2;
                            if ((u32)scratch->depth >= 0x1E0U) {
                                scratch->depth = 0x1DF;
                            }
                            tri_avg = scratch->shade;
                            last_value = scratch->last_shade;
                            twice_avg = tri_avg << 1;
                            scratch->shade =
                                (tri_avg + twice_avg + last_value) >> 2;

                            gte_ldv0((u8 *)scratch + 0x17C);
                            gte_ldrgb(scratch);
                            vertex_z = scratch->vertices[3].z;
                            vertex_z = (s16)vertex_z;
                            shade_factor = 0;
                            if (vertex_z > 0) {
                                shade_factor = vertex_z << 2;
                            }
                            gte_ldir0(shade_factor);
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_00 = 9;
                            gte_ncds_nn();
                            gte_strgb((u8 *)packet + 4);

                            uv_left = scratch->uv_scroll.low_byte;
                            packet_fields->unk_15 = uv_left;
                            packet_fields->unk_05 = uv_left;
                            uv_right = scratch->uv_scroll.low_byte + 0x3F;
                            packet_fields->unk_1D = uv_right;
                            packet_fields->unk_0D = uv_right;
                            uv_top = -(s32)scratch->uv_scroll.low_byte;
                            red = ((S_800AD138_2_pre *)packet_fields)[-1].unk_01;
                            packet_fields->unk_0E = uv_top;
                            packet_fields->unk_06 = uv_top;
                            v_scroll = scratch->uv_scroll.low_byte;
                            ((MapQuadTextureWords *)((u8 *)packet_fields - 7))->texture_page = 0x2D;
                            ((MapQuadTextureWords *)((u8 *)packet_fields - 7))->palette = 0x75C1;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_01 = red >> 1;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_02 >>= 1;
                            uv_bottom = 0x3F - v_scroll;
                            packet_fields->unk_1E = uv_bottom;
                            packet_fields->unk_16 = uv_bottom;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_03 >>= 1;
                            chain_tag = ((S_800AD138_4 *)((void *)scratch->chain_address))->unk_00;
                            packet_tag = ((S_800AD138_3 *)((u8 *)packet))->unk_00;
                            ((S_800AD138_3 *)((u8 *)packet))->unk_00 =
                                (packet_tag & length_mask) |
                                (chain_tag & addr_mask);
                            packet_addr = (s32)packet & addr_mask;
                            packet += 10;
                            ((S_800AD138_4 *)((void *)scratch->chain_address))->unk_00 =
                                (((S_800AD138_4 *)((void *)scratch->chain_address))->unk_00 & length_mask) |
                                packet_addr;
                            if (packet_limit < (u32)packet) {
                                goto done;
                            }
                        }
                    }
                    scratch->cell_x += 1;
                    next_x = scratch->min_x.value + 0x40;
                    scratch->min_x.value = next_x;
                    if (scratch->max_x < next_x) {
                        break;
                    }
                } while (1);
            }

            edge_index = 3;
            edge_done = -1;
            scratch->scan_y.value += 0x40;
            do {
                if (scratch->edges[edge_index].active > 0) {
                    rows_left = scratch->edges[edge_index].rows_left - 0x40;
                    scratch->edges[edge_index].rows_left = rows_left;
                    if (rows_left <= 0) {
                        scratch->edges[edge_index].active = edge_done;
                        scratch->edge_count -= 1;
                    }
                }
                edge_index--;
            } while (edge_index >= 0);
            edge_index = 3;
        } while (scratch->edge_count != 0);
    }

done:
    draw_rect[1] = 0x400040;
    draw_rect[0] = 0;
    SetDrawMode(packet, 0, 0, 0x20, draw_rect);
    AddPrim((void *)scratch->chain_address, packet);
    packet += 3;
    ((S_800AD138_5 *)(state->unk_00))->unk_8D0 = packet;
    return;
}
