#include "common.h"
#include "shared/game_work.h"


extern s16 runtimeInitializePolygonEdges(s16 *, s32 *, u16 *);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, void *);

typedef struct Slot800AF9D8 {
    u8 pad00[0x1C];
    s32 position;
    s32 decrement;
    u8 pad24[8];
    s32 remaining;
    s32 increment;
    u8 pad34[8];
    s32 phase;
} Slot800AF9D8;


typedef struct S_800AD138_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800AD138_0;   /* record in func_800AD138 */

typedef struct S_800AD138_1 {
    u8 * unk_00;
    u16 unk_04;
    u8 pad_06[0xA2];
    s32 unk_A8;
    u8 pad_AC[0x130];
    u16 * unk_1DC;
} S_800AD138_1;   /* state in func_800AD138 */

typedef struct S_800AD138_2_pre {
    s8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800AD138_2_pre;   /* the 0x4 bytes before packet_use in func_800AD138, addressed as packet_use[-1] */

typedef struct S_800AD138_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    s8 unk_06;
    u8 pad_07[0x6];
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x6];
    u8 unk_15;
    s8 unk_16;
    u8 pad_17[0x6];
    s8 unk_1D;
    s8 unk_1E;
} S_800AD138_2;   /* packet_use in func_800AD138 */

typedef struct S_800AD138_3 {
    s32 unk_00;
} S_800AD138_3;   /* (u8 *)list in func_800AD138 */

typedef struct S_800AD138_4 {
    s32 unk_00;
} S_800AD138_4;   /* (void *)((MapQuadScratch *)scratch)->chain_address in func_800AD138 */

typedef struct S_800AD138_5 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_800AD138_5;   /* ((S_800AD138_1 *)state)->unk_00 in func_800AD138 */

typedef struct MapQuadTextureWords {
    u8 pad_00[0xE];
    s16 palette;
    u8 pad_10[6];
    s16 texture_page;
} MapQuadTextureWords;

typedef struct MapQuadEdge {
    s32 position;
    s32 unused_04;
    s32 error_step;
    s32 rows_left;
    s32 error;
    s32 unused_14;
    s32 start_y;
    s32 active;
    u8 pad_20[8];
} MapQuadEdge;

typedef struct MapQuadVertex {
    u16 x, y, z, pad;
} MapQuadVertex;

typedef union MapQuadCoordinate {
    s32 value;
    u16 low_half;
} MapQuadCoordinate;

typedef struct MapQuadScratch {
    s32 color;
    s32 unused_04;
    s32 edge_x;
    MapQuadCoordinate scan_y;
    s32 unused_10;
    MapQuadCoordinate min_x;
    s32 max_x;
    MapQuadEdge edges[4];
    s32 chain_address;
    s32 shade;
    s32 last_shade;
    s32 depth;
    u8 pad_CC[8];
    s32 last_depth;
    s32 unused_D8;
    s32 clip_area;
    MapQuadVertex vertices[4];
    u8 pad_100[0x14];
    s32 step_x;
    s32 step_y;
    s32 map_width;
    s32 map_height;
    s32 x_shift;
    s32 y_shift;
    u8 pad_12C[8];
    s32 cell_x;
    s32 row_base;
    u8 pad_13C[8];
    s32 cell_index;
    u8 pad_148[0x28];
    u16 edge_count;
    u8 pad_172[0xA];
    s16 normal_x, normal_y, normal_z;
    u8 pad_182[0x8A];
    union { u16 value; u8 low_byte; } uv_scroll;
} MapQuadScratch;

/* Draw textured quads for empty cells in the visible map region. */
void func_800AD138(u32 packet_limit)
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

    state = ((u8 *)(&gameWork));
    map_bounds = state + 0x1DC;
    ((MapQuadScratch *)scratch)->normal_x = 0;
    ((MapQuadScratch *)scratch)->normal_y = 0;
    render_state = gameWork.unk_000;
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
        runtimeInitializePolygonEdges(clip_vertices,
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
