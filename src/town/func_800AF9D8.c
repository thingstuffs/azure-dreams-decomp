#include "common.h"


extern u8 D_80083160[];
extern s16 func_80046C20(s16 *, s32 *, u16 *);
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
} S_800AD138_4;   /* (void *)(*(s32 *)((u8 *)scratch + 0xBC)) in func_800AD138 */

typedef struct S_800AD138_5 {
    u8 pad_00[0x8D0];
    s32 * unk_8D0;
} S_800AD138_5;   /* ((S_800AD138_1 *)state)->unk_00 in func_800AD138 */

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

    (*(s16 *)((u8 *)scratch + 0x180)) = -0x1000;

    state = D_80083160;
    map_bounds = state + 0x1DC;
    (*(s16 *)((u8 *)scratch + 0x17C)) = 0;
    (*(s16 *)((u8 *)scratch + 0x17E)) = 0;
    render_state = *(u8 **)D_80083160;
    x_shift = ((S_800AD138_0 *)map_bounds)->unk_14;
    initial_size = 0x01000100;
    y_shift = ((S_800AD138_0 *)map_bounds)->unk_16;
    chain_addr = (s32)(render_state + 0x8AC);
    (*(s32 *)((u8 *)scratch + 0x0BC)) = chain_addr;
    (*(s32 *)((u8 *)scratch + 0x128)) = y_shift;
    (*(s32 *)((u8 *)scratch + 0x124)) = x_shift;
    (*(s32 *)((u8 *)scratch + 0x114)) = 0x40 << x_shift;
    bound_x = ((S_800AD138_0 *)map_bounds)->unk_18;
    bound_y = ((S_800AD138_0 *)map_bounds)->unk_1A;
    uv_scroll = (((S_800AD138_1 *)state)->unk_04 >> 1) & 0x3F;
    map_height = 0x40 << y_shift;
    (*(s32 *)((u8 *)scratch + 0x118)) = map_height;
    (*(s32 *)((u8 *)scratch + 0x11C)) = bound_x;
    (*(s32 *)((u8 *)scratch + 0x120)) = bound_y;
    (*(u16 *)((u8 *)scratch + 0x20C)) = uv_scroll;

    packet = (*(s32 * *)((u8 *)render_state + 0x8D0));
    (*(s32 *)((u8 *)scratch + 0)) = ((S_800AD138_1 *)state)->unk_A8;
    draw_rect[0] = 0;
    draw_rect[1] = initial_size;
    cell_table = ((S_800AD138_1 *)state)->unk_1DC;
    func_80067F20(packet, (s32)edge_buffer, edge_count_addr, 0x20, draw_rect);
    func_8006658C((void *)(*(s32 *)((u8 *)scratch + 0xBC)), packet);
    packet += 3;
    (*(u16 *)((u8 *)scratch + 0x170)) = 4;
    clip_vertices = (s16 *)(state + 0x20);
    edge_buffer = scratch;
    edge_buffer = (u8 *)((u32)edge_buffer | 0x1C);
    edge_count_addr = (s32)scratch;
    edge_count_addr |= 0x170;
    (*(s32 *)((u8 *)scratch + 0x0C)) =
        func_80046C20(clip_vertices,
                      (s32 *)edge_buffer,
                      (u16 *)edge_count_addr);

    if ((*(u16 *)((u8 *)scratch + 0x170)) != 0) {
        edge_active = 1;
        vertices = scratch;
        vertices = (u8 *)((u32)vertices | 0xE0);
        addr_mask = 0x00FFFFFF;
        length_mask = 0xFF000000;
        do {
            edge_index = 3;
            do {
                if (((*(s32 *)((u8 *)scratch + 0x38 + edge_index * 0x28)) == 0) &&
                    ((*(s32 *)((u8 *)scratch + 0x34 + edge_index * 0x28)) <= (*(s32 *)((u8 *)scratch + 0x0C)))) {
                    (*(s32 *)((u8 *)scratch + 0x38 + edge_index * 0x28)) = edge_active;
                }
                edge_index--;
            } while (edge_index >= 0);

            edge_index = 3;
            (*(s32 *)((u8 *)scratch + 0x14)) = 0x7FFF;
            (*(s32 *)((u8 *)scratch + 0x18)) = -0x7FFF;
            do {
                if ((*(s32 *)((u8 *)scratch + 0x38 + edge_index * 0x28)) > 0) {
                    x = (*(s32 *)((u8 *)scratch + 0x1C + edge_index * 0x28));
                    (*(s32 *)((u8 *)scratch + 8)) = x;
                    if (x < (*(s32 *)((u8 *)scratch + 0x14))) {
                        (*(s32 *)((u8 *)scratch + 0x14)) = x;
                    }
                    x = (*(s32 *)((u8 *)scratch + 8));
                    if ((*(s32 *)((u8 *)scratch + 0x18)) < x) {
                        (*(s32 *)((u8 *)scratch + 0x18)) = x;
                    }
                    edge_error = (*(s32 *)((u8 *)scratch + 0x2C + edge_index * 0x28)) + (*(s32 *)((u8 *)scratch + 0x24 + edge_index * 0x28));
                    (*(s32 *)((u8 *)scratch + 0x2C + edge_index * 0x28)) = edge_error;
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
                    x = (*(s32 *)((u8 *)scratch + 0x1C + edge_index * 0x28));
                    (*(s32 *)((u8 *)scratch + 8)) = x;
                    if (x < (*(s32 *)((u8 *)scratch + 0x14))) {
                        (*(s32 *)((u8 *)scratch + 0x14)) = x;
                    }
                    x = (*(s32 *)((u8 *)scratch + 8));
                    if ((*(s32 *)((u8 *)scratch + 0x18)) < x) {
                        (*(s32 *)((u8 *)scratch + 0x18)) = x;
                    }
                }
                edge_index--;
            } while (edge_index >= 0);

            (*(s32 *)((u8 *)scratch + 0x14)) =
                ((*(s32 *)((u8 *)scratch + 0x14)) - 0x20) & ~0x3F;
            (*(s32 *)((u8 *)scratch + 0x18)) =
                ((*(s32 *)((u8 *)scratch + 0x18)) + 0x20) & ~0x3F;
            min_x = (*(s32 *)((u8 *)scratch + 0x14));
            if (min_x < 0) {
                min_x += 0x3F;
            }
            row = (*(s32 *)((u8 *)scratch + 0x0C));
            (*(s32 *)((u8 *)scratch + 0x134)) = min_x >> 6;
            if (row < 0) {
                row += 0x3F;
            }
            row >>= 6;
            (*(s32 *)((u8 *)scratch + 0x138)) = row;
            if (row < 0) {
                (*(s32 *)((u8 *)scratch + 0x138)) = 0;
                goto row_ready;
            }
            row_bound = (*(s32 *)((u8 *)scratch + 0x120));
            if (row < row_bound) {
                goto row_in_range;
            }
            row_base = row_bound << (*(s32 *)((u8 *)scratch + 0x124));
            goto store_row_base;
    row_in_range:
            row_base = row << (*(s32 *)((u8 *)scratch + 0x124));
    store_row_base:
            (*(s32 *)((u8 *)scratch + 0x138)) = row_base;
    row_ready:

            edge_index = 3;
            if ((*(s32 *)((u8 *)scratch + 0x14)) <= (*(s32 *)((u8 *)scratch + 0x18))) {
                do {
                    packet_fields = (u8 *)packet + 7;
                    cell_x = (*(s32 *)((u8 *)scratch + 0x134));
                    if (cell_x < 0) {
                        cell_index = (*(s32 *)((u8 *)scratch + 0x138));
                        cell_x &= 3;
                        cell_index += cell_x;
                        (*(s32 *)((u8 *)scratch + 0x144)) = cell_index;
                    } else {
                        col_bound = (*(s32 *)((u8 *)scratch + 0x11C));
                        if (cell_x >= col_bound) {
                            cell_index = (*(s32 *)((u8 *)scratch + 0x138));
                            cell_x &= 3;
                            cell_index += col_bound;
                            cell_index += cell_x;
                            cell_index -= 3;
                            (*(s32 *)((u8 *)scratch + 0x144)) = cell_index;
                        } else {
                            cell_index = (*(s32 *)((u8 *)scratch + 0x138));
                            cell_index += cell_x;
                            (*(s32 *)((u8 *)scratch + 0x144)) = cell_index;
                        }
                    }
                    cell_id = cell_table[(*(s32 *)((u8 *)scratch + 0x144))];
                    (*(s32 *)((u8 *)scratch + 0x0C0)) = cell_id;
                    if (cell_id == 0) {
                        vertex_x = (*(u16 *)((u8 *)scratch + 0x14));
                        top_y = (*(u16 *)((u8 *)scratch + 0x0C));
                        (*(u16 *)((u8 *)scratch + 0x0FC)) = 0;
                        (*(u16 *)((u8 *)scratch + 0x0F4)) = 0;
                        (*(u16 *)((u8 *)scratch + 0x0EC)) = 0;
                        (*(u16 *)((u8 *)scratch + 0x0E4)) = 0;
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
                        (*(u16 *)((u8 *)scratch + 0x0F0)) = vertex_x;
                        (*(u16 *)((u8 *)scratch + 0x0E0)) = vertex_x;
                        vertex_x += 0x40;
                        bottom_y += 0x40;
                        (*(u16 *)((u8 *)scratch + 0x0F8)) = vertex_x;
                        (*(u16 *)((u8 *)scratch + 0x0E8)) = vertex_x;
                        (*(u16 *)((u8 *)scratch + 0x0FA)) = bottom_y;
                        (*(u16 *)((u8 *)scratch + 0x0F2)) = bottom_y;
                        (*(u16 *)((u8 *)scratch + 0x0EA)) = top_y;
                        (*(u16 *)((u8 *)scratch + 0x0E2)) = top_y;

                        gte_ldv3(vertices, scratch + 0xE8, scratch + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz(scratch + 0xDC);
                        if ((*(s32 *)((u8 *)scratch + 0x0DC)) > 0) {
                            gte_stsxy3_g3(packet);
                            gte_stdp(scratch + 0xC0);
                            gte_avsz3();
                            gte_stotz(scratch + 0xC8);
                            gte_ldv0(scratch + 0xF8);
                            gte_rtps();
                            gte_stsxy((u8 *)packet + 0x20);
                            gte_stdp(scratch + 0xC4);
                            gte_stszotz(scratch + 0xD4);

                            tri_avg = (*(s32 *)((u8 *)scratch + 0x0C8));
                            last_value = (*(s32 *)((u8 *)scratch + 0x0D4));
                            twice_avg = tri_avg << 1;
                            (*(s32 *)((u8 *)scratch + 0x0C8)) =
                                (tri_avg + twice_avg + last_value + 3) >> 2;
                            if ((u32)(*(s32 *)((u8 *)scratch + 0x0C8)) >= 0x1E0U) {
                                (*(s32 *)((u8 *)scratch + 0x0C8)) = 0x1DF;
                            }
                            tri_avg = (*(s32 *)((u8 *)scratch + 0x0C0));
                            last_value = (*(s32 *)((u8 *)scratch + 0x0C4));
                            twice_avg = tri_avg << 1;
                            (*(s32 *)((u8 *)scratch + 0x0C0)) =
                                (tri_avg + twice_avg + last_value) >> 2;

                            gte_ldv0(scratch + 0x17C);
                            gte_ldrgb(scratch);
                            vertex_z = (*(u16 *)((u8 *)scratch + 0x0FC));
                            vertex_z = (s16)vertex_z;
                            shade_factor = 0;
                            if (vertex_z > 0) {
                                shade_factor = vertex_z << 2;
                            }
                            gte_ldir0(shade_factor);
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_00 = 9;
                            gte_ncds_nn();
                            gte_strgb((u8 *)packet + 4);

                            uv_left = (*(u8 *)((u8 *)scratch + 0x20C));
                            ((S_800AD138_2 *)packet_fields)->unk_15 = uv_left;
                            ((S_800AD138_2 *)packet_fields)->unk_05 = uv_left;
                            uv_right = (*(u8 *)((u8 *)scratch + 0x20C)) + 0x3F;
                            ((S_800AD138_2 *)packet_fields)->unk_1D = uv_right;
                            ((S_800AD138_2 *)packet_fields)->unk_0D = uv_right;
                            uv_top = -(s32)(*(u8 *)((u8 *)scratch + 0x20C));
                            red = ((S_800AD138_2_pre *)packet_fields)[-1].unk_01;
                            ((S_800AD138_2 *)packet_fields)->unk_0E = uv_top;
                            ((S_800AD138_2 *)packet_fields)->unk_06 = uv_top;
                            v_scroll = (*(u8 *)((u8 *)scratch + 0x20C));
                            (*(s16 *)((u8 *)packet_fields + 0x0F)) = 0x2D;
                            (*(s16 *)((u8 *)packet_fields + 7)) = 0x75C1;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_01 = red >> 1;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_02 >>= 1;
                            uv_bottom = 0x3F - v_scroll;
                            ((S_800AD138_2 *)packet_fields)->unk_1E = uv_bottom;
                            ((S_800AD138_2 *)packet_fields)->unk_16 = uv_bottom;
                            ((S_800AD138_2_pre *)packet_fields)[-1].unk_03 >>= 1;
                            chain_tag = ((S_800AD138_4 *)((void *)(*(s32 *)((u8 *)scratch + 0xBC))))->unk_00;
                            packet_tag = ((S_800AD138_3 *)((u8 *)packet))->unk_00;
                            ((S_800AD138_3 *)((u8 *)packet))->unk_00 =
                                (packet_tag & length_mask) |
                                (chain_tag & addr_mask);
                            packet_addr = (s32)packet & addr_mask;
                            packet += 10;
                            ((S_800AD138_4 *)((void *)(*(s32 *)((u8 *)scratch + 0xBC))))->unk_00 =
                                (((S_800AD138_4 *)((void *)(*(s32 *)((u8 *)scratch + 0xBC))))->unk_00 & length_mask) |
                                packet_addr;
                            if (packet_limit < (u32)packet) {
                                goto done;
                            }
                        }
                    }
                    (*(s32 *)((u8 *)scratch + 0x134)) += 1;
                    next_x = (*(s32 *)((u8 *)scratch + 0x14)) + 0x40;
                    (*(s32 *)((u8 *)scratch + 0x14)) = next_x;
                    if ((*(s32 *)((u8 *)scratch + 0x18)) < next_x) {
                        break;
                    }
                } while (1);
            }

            edge_index = 3;
            edge_done = -1;
            (*(s32 *)((u8 *)scratch + 0x0C)) += 0x40;
            do {
                if ((*(s32 *)((u8 *)scratch + 0x38 + edge_index * 0x28)) > 0) {
                    rows_left = (*(s32 *)((u8 *)scratch + 0x28 + edge_index * 0x28)) - 0x40;
                    (*(s32 *)((u8 *)scratch + 0x28 + edge_index * 0x28)) = rows_left;
                    if (rows_left <= 0) {
                        (*(s32 *)((u8 *)scratch + 0x38 + edge_index * 0x28)) = edge_done;
                        (*(u16 *)((u8 *)scratch + 0x170)) -= 1;
                    }
                }
                edge_index--;
            } while (edge_index >= 0);
            edge_index = 3;
        } while ((*(u16 *)((u8 *)scratch + 0x170)) != 0);
    }

done:
    draw_rect[1] = 0x400040;
    draw_rect[0] = 0;
    func_80067F20(packet, 0, 0, 0x20, draw_rect);
    func_8006658C((void *)(*(s32 *)((u8 *)scratch + 0xBC)), packet);
    packet += 3;
    ((S_800AD138_5 *)(((S_800AD138_1 *)state)->unk_00))->unk_8D0 = packet;
    return;
}
