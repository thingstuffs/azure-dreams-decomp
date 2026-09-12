/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80046884();     /* extern */
s32 func_80046C20(); /* extern */
M2C_UNK func_80064624();                    /* extern */
M2C_UNK func_80064D20();                      /* extern */
M2C_UNK func_80064D50();                      /* extern */
M2C_UNK func_800AD138();                         /* extern */
extern u8 D_8006ADBC[];
extern u8 D_80083160[];
extern s32 D_800D1548[3];
extern u8 D_800D1554[9];

typedef struct S_func_800AED64_1 {
    void * unk_00;
    u8 pad_04[0x16];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x88];
    s32 unk_A8;
    u8 pad_AC[0x130];
    void * unk_1DC;
} S_func_800AED64_1;

typedef struct S_func_800AED64_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_func_800AED64_2;

typedef struct S_func_800AED64_3 {
    u8 pad_00[0x84];
    s32 unk_84;
    s32 unk_88;
} S_func_800AED64_3;

typedef struct S_func_800AED64_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    union {
        s32 s32;
        u16 u16;
    } unk_14;
    s32 unk_18;
    u8 pad_1C[0xA0];
    s32 unk_BC;
    s32 unk_C0;
    u8 pad_C4[0x4];
    s32 unk_C8;
    u8 pad_CC[0x8];
    s32 unk_D4;
    u8 pad_D8[0x4];
    s32 unk_DC;
    s32 unk_E0;
    union {
        s16 s16;
        u16 u16;
    } unk_E4;
    u8 pad_E6[0x2];
    s32 unk_E8;
    s16 unk_EC;
    u8 pad_EE[0x2];
    s32 unk_F0;
    s16 unk_F4;
    u8 pad_F6[0x2];
    s32 unk_F8;
    s16 unk_FC;
    u8 pad_FE[0x12];
    s32 unk_110;
    s32 unk_114;
    s32 unk_118;
    s32 unk_11C;
    s32 unk_120;
    s32 unk_124;
    s32 unk_128;
    union {
        s32 s32;
        u16 u16;
    } unk_12C;
    u8 pad_130[0x4];
    s32 unk_134;
    s32 unk_138;
    u8 pad_13C[0x8];
    s32 unk_144;
    u8 pad_148[0x4];
    s32 unk_14C;
    u8 pad_150[0x14];
    s32 unk_164;
    union {
        s32 s32;
        u16 u16;
        struct {
            u8 pad_168[0x2];
            u16 unk_16A;
        } at_16A;
    } unk_168;
    union {
        s32 s32;
        struct {
            u8 pad_16C[0x2];
            u8 unk_16E;
        } at_16E;
        struct {
            u8 pad_16C[0x3];
            u8 unk_16F;
        } at_16F;
    } unk_16C;
    s32 unk_170;
    u16 unk_174;
    u16 unk_176;
    u16 unk_178;
    u8 pad_17A[0x2];
    s32 unk_17C;
} S_func_800AED64_4;

typedef struct S_func_800AED64_5 {
    u8 pad_00[0x3180];
    s32 unk_3180;
    u8 unk_3184;
    u8 unk_3185;
} S_func_800AED64_5;

typedef struct S_func_800AED64_6 {
    u8 pad_00[0x8D0];
    u32 unk_8D0;
} S_func_800AED64_6;

typedef struct S_func_800AED64_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} S_func_800AED64_7;

typedef struct S_func_800AED64_8 {
    u16 unk_00;
} S_func_800AED64_8;

typedef struct S_func_800AED64_9 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x4];
    u16 unk_1C;
    u8 pad_1E[0x6];
    u16 unk_24;
} S_func_800AED64_9;

typedef struct S_func_800AED64_10 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
} S_func_800AED64_10;

typedef struct S_func_800AED64_11 {
    s32 unk_00;
} S_func_800AED64_11;

typedef struct S_func_800AED64_12 {
    void * unk_00;
} S_func_800AED64_12;

typedef struct S_func_800AED64_13 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    union {
        s32 s32;
        struct {
            u8 pad_14[0x2];
            u8 unk_16;
        } at_16;
        struct {
            u8 pad_14[0x3];
            s8 unk_17;
        } at_17;
    } unk_14;
} S_func_800AED64_13;

typedef struct S_func_800AED64_14 {
    u8 pad_00[0x3];
    s8 unk_03;
    union {
        s32 s32;
        struct {
            u8 pad_04[0x3];
            u8 unk_07;
        } at_07;
    } unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u16 unk_1C;
    u8 pad_1E[0x2];
    void * unk_20;
    u16 unk_24;
} S_func_800AED64_14;

typedef struct S_func_800AED64_15 {
    s32 unk_00;
    u16 unk_04;
} S_func_800AED64_15;

typedef struct S_func_800AED64_16 {
    s32 unk_00;
    s16 unk_04;
} S_func_800AED64_16;

typedef struct S_func_800AED64_17 {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1A;
} S_func_800AED64_17;

/* Render visible town map tiles as shaded polygons in the ordering table. */
void func_800AC4C4(void) {
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
    register s32 work_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 work_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 column_rounding;
    M2C_UNK * lookup_value;
    register s32 edge_index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 span_edge_index;
    s8 *tile_map;
    s32 row_rounding;
    u16 normal_index;
    M2C_UNK * packet;
    void *view_bounds;
    register S_func_800AED64_2 *map_data ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_func_800AED64_10 *tile_uvs;
    S_func_800AED64_7 *start_edge;
    S_func_800AED64_7 *span_edge;
    S_func_800AED64_13 *polygon; /* MATCH: the polygon loop keeps its cursor in a2, sharing the outer loop counter register. */
    void *packet_color;
    void *packet_xy3;
    S_func_800AED64_7 *end_edge;
    S_func_800AED64_7 *step_edge;
    register s32 x_step ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 error_step ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 row_limit;
    register void *work_ptr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    void *coord_offset;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *edge_count;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_func_800AED64_6 *render_buffer;
    u32 tag_low_mask;
    u32 tag_high_mask;
    s32 one;
    S_func_800AED64_4 *scratch;
    register void *vertex_input;
    register S_func_800AED64_1 *render_state ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    {
        register u8 *state_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        state_page = (u8 *)0x80080000;
        ASM_KEEP_NV(state_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        render_state = state_page + 0x3160;
    }
    ASM_KEEP_NV(render_state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    map_data = (u8 *)render_state + 0x1DC;
    tile_map = render_state->unk_1DC;
    vertices = map_data->unk_08;
    normals = map_data->unk_0C;
    func_80064D50((u8 *)render_state + 0x70);
    {
        S_func_800AED64_3 *view_params;
        view_params = (u8 *)render_state + 0x18;
        func_80064624(view_params->unk_84, view_params->unk_88);
    }
    scratch = (s8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    func_80064D20((u8 *)render_state + 0x50);
    if (D_800D1554[0] != 0) {
        render_state->unk_1A = -0xB8;
        render_state->unk_1E = 0x1DA;
    } else {

        render_state->unk_1A = -0x88;
        render_state->unk_1E = 0x1AA;
    }
    view_bounds = (u8 *)render_state + 0x20;
    func_80046884((u8 *)render_state + 0x18, view_bounds, 0);
    work_ptr = view_bounds;
    coord_offset = (void *) ((u32) scratch | 0x1C);
    base_color = render_state->unk_A8;
    edge_count = (void *) ((u32) scratch | 0x174);
    scratch->unk_00 = base_color;
    ordering_table = render_state->unk_00;
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
    scratch->unk_124 = (s32) width_shift;
    ((volatile S_func_800AED64_4 *)(scratch))->unk_178 = draw_flags;
    scratch->unk_BC = ordering_table;
    scratch->unk_128 = (s32) height_shift;
    scratch->unk_114 = 0x40 << scratch->unk_124;
    scratch->unk_11C = (s32) max_column;
    scratch->unk_120 = (s32) max_row;
    scratch->unk_110 = flat_color;
    scratch->unk_176 = draw_mode;
    render_buffer = render_state->unk_00;
    scratch->unk_118 = 0x40 << scratch->unk_128;
    packet = render_buffer->unk_8D0;
    scratch->unk_14C = 0xFFFF;
    scratch->unk_174 = 4;
    scratch->unk_164 = (u8 *) packet + 0xCCCC;
    scratch->unk_0C = (s16) func_80046C20(work_ptr, coord_offset, edge_count, render_buffer);
    if (scratch->unk_174 != 0) {
        one = 1;
        vertex_input = (u8 *)scratch + 0xE0;
        tile_uvs = D_800D1548;
        tag_low_mask = 0xFFFFFF;
        tag_high_mask = 0xFF000000;
scan_row:
        edge_index = 3;
        start_edge = (s32 *)((u8 *)scratch + 0x78);
        do {
            if (start_edge->unk_38 == 0) {
                work_bits = start_edge->unk_34;
                work_value = scratch->unk_0C;
                if (work_value >= work_bits) {
                    start_edge->unk_38 = one;
                }
            }
            edge_index -= 1;
            start_edge = (S_func_800AED64_7 *)((u8 *)start_edge - 0x28);
        } while (edge_index >= 0);
        span_edge_index = 3;
        span_edge = (s32 *)((u8 *)scratch + 0x78);
        scratch->unk_14.s32 = 0x7FFF;
        scratch->unk_18 = -0x7FFF;
        do {
            if (span_edge->unk_38 > 0) {
                edge_x = span_edge->unk_1C;
                scratch->unk_08 = edge_x;
                if (edge_x < scratch->unk_14.s32) {
                    scratch->unk_14.s32 = edge_x;
                }
                span_x = scratch->unk_08;
                if (scratch->unk_18 < span_x) {
                    scratch->unk_18 = span_x;
                }
                edge_error = span_edge->unk_2C + span_edge->unk_24;
                span_edge->unk_2C = edge_error;
                if (edge_error >= 0) {
                    step_edge = span_edge;
                    x_step = span_edge->unk_30;
                    error_step = span_edge->unk_20;
step_span:
                    work_value = step_edge->unk_1C;
                    work_bits = step_edge->unk_3C;
                    work_value += x_step;
                    step_edge->unk_1C = work_value;
                    work_value = step_edge->unk_2C;
                    work_bits -= 0x40;
                    step_edge->unk_3C = work_bits;
                    work_value -= error_step;
                    step_edge->unk_2C = work_value;
                    if (work_bits > 0) {
                        if (work_value >= 0) {
                            goto step_span;
                        }
                    }
                }
                stepped_x = span_edge->unk_1C;
                scratch->unk_08 = stepped_x;
                if (stepped_x < scratch->unk_14.s32) {
                    scratch->unk_14.s32 = stepped_x;
                }
                span_end_x = scratch->unk_08;
                if (scratch->unk_18 < span_end_x) {
                    scratch->unk_18 = span_end_x;
                }
            }
            span_edge_index -= 1;
            span_edge = (S_func_800AED64_7 *)((u8 *)span_edge - 0x28);
        } while (span_edge_index >= 0);
        scratch->unk_14.s32 = (scratch->unk_14.s32 - 0x20) & ~0x3F;
        column_rounding = ((volatile S_func_800AED64_4 *)scratch)->unk_14.s32;
        scratch->unk_18 = (scratch->unk_18 + 0x20) & ~0x3F;
        if (column_rounding < 0) {
            column_rounding += 0x3F;
        }
        row_rounding = scratch->unk_0C;
        scratch->unk_134 = column_rounding >> 6;
        if (row_rounding < 0) {
            row_rounding += 0x3F;
        }
        row_index = row_rounding >> 6;
        scratch->unk_138 = row_index;
        if (row_index < 0) {
            scratch->unk_138 = 0;
        } else {
            row_limit = scratch->unk_120;
            if (row_index >= row_limit) {
                work_value = row_limit << scratch->unk_124;
            } else {
                work_value = row_index << scratch->unk_124;
            }
            scratch->unk_138 = work_value;
        }

        work_bits = scratch->unk_14.s32;
        work_value = scratch->unk_18;
        polygon = (void *)3;
        if (work_value >= work_bits) {
            packet_xy3 = (s8 *) packet + 0x20;
scan_column:
            work_bits = scratch->unk_134;
            if (work_bits < 0) {
                work_value = scratch->unk_138;
                work_bits &= 3;
            } else {
                lookup_value = scratch->unk_11C;
                if (work_bits >= (s32) lookup_value) {
                    work_value = scratch->unk_138;
                    work_bits &= 3;
                    work_value += (s32) lookup_value;
                    work_value += work_bits;
                    work_value -= 3;
                    goto store_column;
                }
                work_value = scratch->unk_138;
            }
            work_value += work_bits;
store_column:
            scratch->unk_144 = work_value;
            tile_id = ((S_func_800AED64_8 *)(tile_map + (((volatile S_func_800AED64_4 *)(scratch))->unk_144 * 2)))->unk_00 & 0x3FFF;
            scratch->unk_C0 = tile_id;
            if (tile_id != 0) {
                tile_flags = ((S_func_800AED64_8 *)(tile_map + (scratch->unk_144 * 2)))->unk_00 & 0xC000;
                scratch->unk_17C = tile_flags;
                if (tile_flags != 0) {
                    scratch->unk_FC = 0;
                    scratch->unk_F4 = 0;
                    scratch->unk_EC = 0;
                    scratch->unk_E4.s16 = 0;
                    scratch->unk_E0 = (u16) scratch->unk_14.s32 | (scratch->unk_0C << 0x10);
                    scratch->unk_E8 = ((((volatile S_func_800AED64_4 *)(scratch))->unk_14.u16 + 0x40) & 0xFFFF) | (scratch->unk_0C << 0x10);
                    scratch->unk_F0 = (u16) scratch->unk_14.s32 | ((scratch->unk_0C + 0x40) << 0x10);
                    scratch->unk_F8 = ((((volatile S_func_800AED64_4 *)(scratch))->unk_14.u16 + 0x40) & 0xFFFF) | ((scratch->unk_0C + 0x40) << 0x10);
                    gte_ldv3(vertex_input, (u8 *)scratch + 0xE8, (u8 *)scratch + 0xF0);
                    ((S_func_800AED64_9 *)((u8 *)packet_xy3 - 0x20))->unk_04 = 0x2C404040;
                    gte_rtpt_nn();
                    gte_avsz3();
                    gte_stotz((u8 *)scratch + 0xC8);
                    gte_stsxy3_g3(packet);
                    gte_ldv0((u8 *)scratch + 0xF8);
                    ((S_func_800AED64_9 *)((u8 *)packet_xy3 - 0x20))->unk_0C = (s32) D_800D1548[0];
                    gte_rtps_nn();
                    gte_stsxy(packet_xy3);
                    ((S_func_800AED64_9 *)((u8 *)packet_xy3 - 0x20))->unk_14 = (s32) tile_uvs->unk_04;
                    ((S_func_800AED64_9 *)((u8 *)packet_xy3 - 0x20))->unk_1C = (u16) tile_uvs->unk_08;
                    ((S_func_800AED64_9 *)((u8 *)packet_xy3 - 0x20))->unk_24 = (u16) tile_uvs->unk_0A;
                    gte_stszotz((u8 *)scratch + 0xD4);
                    work_ptr = (void *)scratch->unk_D4;
                    work_value = scratch->unk_C8;
                    work_bits = work_value << 1;
                    work_value += work_bits;
                    work_value += (s32)work_ptr;
                    work_value += 3;
                    work_value >>= 2;
                    work_value += 4;
                    scratch->unk_C8 = work_value;
                    if ((u32)work_value >= 0x200U) {
                        scratch->unk_C8 = 0x1FF;
                    }
                    ((S_func_800AED64_9 *)((u8 *)packet_xy3 - 0x20))->unk_03 = 9;
                    packet_xy3 += 0x28;
                    lookup_value = (s32) packet & tag_low_mask;
                    *packet = (s32) ((*packet & tag_high_mask) | (((S_func_800AED64_11 *)((s8 *)scratch->unk_BC + (scratch->unk_C8 * 4)))->unk_00 & tag_low_mask));
                    depth_bucket = (scratch->unk_C8 * 4) + scratch->unk_BC;
                    packet = (s32 *)((s8 *)packet + 0x28);
                    *depth_bucket = (*depth_bucket & tag_high_mask) | (s32) lookup_value;
                }
                tile_index = scratch->unk_C0;
                   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                packet_color = (s8 *)packet + 4;

                scratch->unk_12C.s32 = 0;
                polygon = ((S_func_800AED64_12 *)((s8 *)map_data->unk_04 + (tile_index * 4)))->unk_00;
                for (;;) {
                    if (polygon->unk_0C != 0) {
                        work_value = polygon->unk_10;
                        work_ptr = (void *) (u32) scratch->unk_14.u16;
                        scratch->unk_170 = work_value;
                        work_value = polygon->unk_00;
                        work_bits = polygon->unk_14.s32;
                        work_value <<= 3;
                        work_value += (s32) vertices;
                        scratch->unk_16C.s32 = work_bits;
                        work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                        work_bits = scratch->unk_12C.u16;
                        scratch->unk_168.s32 = work_value;
                        work_value = polygon->unk_00;
                        coord_offset = (void *) (u32) scratch->unk_168.u16;
                        work_value <<= 3;
                        work_value += (s32) vertices;
                        work_ptr = (void *) ((u32) work_ptr + (u32) coord_offset);
                        work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                        work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                        work_value -= work_bits;
                        scratch->unk_E4.s16 = work_value;
                        work_value = scratch->unk_168.at_16A.unk_16A;
                        work_bits = scratch->unk_0C;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        ASM_KEEP_NV(work_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        work_value = (s32) (work_value << 0x10) >> 0x10;
                        work_bits += work_value;
                        work_bits <<= 0x10;
                        work_value = polygon->unk_02;
                        work_ptr = (void *) ((u32) work_ptr | (u32) work_bits);
                        scratch->unk_E0 = (s32) work_ptr;
                        work_ptr = (void *) (u32) scratch->unk_14.u16;
                        work_bits = scratch->unk_12C.u16;
                        work_value <<= 3;
                        work_value += (s32) vertices;
                        work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                        scratch->unk_168.s32 = work_value;
                        work_value = polygon->unk_02;
                        coord_offset = (void *) (u32) scratch->unk_168.u16;
                        work_value <<= 3;
                        work_value += (s32) vertices;
                        work_ptr = (void *) ((u32) work_ptr + (u32) coord_offset);
                        work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                        work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                        work_value -= work_bits;
                        scratch->unk_EC = work_value;
                        work_value = scratch->unk_168.at_16A.unk_16A;
                        work_bits = scratch->unk_0C;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        ASM_KEEP_NV(work_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        work_value = (s32) (work_value << 0x10) >> 0x10;
                        work_bits += work_value;
                        work_bits <<= 0x10;
                        work_value = polygon->unk_04;
                        work_ptr = (void *) ((u32) work_ptr | (u32) work_bits);
                        scratch->unk_E8 = (s32) work_ptr;
                        work_ptr = (void *) (u32) scratch->unk_14.u16;
                        work_value <<= 3;
                        work_value += (s32) vertices;
                        work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                        scratch->unk_168.s32 = work_value;
                        work_value = scratch->unk_168.u16;
                        work_bits = ((volatile S_func_800AED64_4 *)(scratch))->unk_168.at_16A.unk_16A;
                        work_ptr = (void *) ((u32) work_ptr + (u32) work_value);
                        work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                        work_bits <<= 0x10;
                        work_value = scratch->unk_0C;
                        work_bits >>= 0x10;
                        work_value += work_bits;
                        work_value <<= 0x10;
                        work_ptr = (void *) ((u32) work_ptr | (u32) work_value);
                        scratch->unk_F0 = (s32) work_ptr;
                        work_value = polygon->unk_04;
                        work_value <<= 3;
                        work_value += (s32) vertices;
                        work_bits = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                        work_value = scratch->unk_12C.u16;
                        work_bits -= work_value;
                        scratch->unk_F4 = work_bits;
                        gte_ldv3(vertex_input, (u8 *)scratch + 0xE8, (u8 *)scratch + 0xF0);
                        gte_rtpt();
                        gte_nclip();
                        gte_stopz((u8 *)scratch + 0xDC);
                        if (scratch->unk_DC >= 0) {
                            work_value = polygon->unk_06;
                            work_value <<= 3;
                            work_value += (s32) vertices;
                            work_bits = ((S_func_800AED64_15 *)((void *) work_value))->unk_04;
                            work_value = scratch->unk_12C.u16;
                            work_bits -= work_value;
                            scratch->unk_FC = work_bits;
                            gte_stsxy3_g3(packet);
                            gte_avsz3();
                            gte_stotz((u8 *)scratch + 0xC8);
                            normal_index = (u16) scratch->unk_170;
                            if (scratch->unk_14C != normal_index) {
                                scratch->unk_14C = (s32) normal_index;
                                gte_ldrgb(scratch);
                                gte_ldv0(normals + (normal_index * 8));
                                gte_nccs();
                                gte_strgb((u8 *)scratch + 4);
                            }
                            work_value = polygon->unk_06;
                            work_ptr = (void *) (u32) scratch->unk_14.u16;
                            work_value <<= 3;
                            work_value += (s32) vertices;
                            work_value = ((S_func_800AED64_15 *)((void *) work_value))->unk_00;
                            scratch->unk_168.s32 = work_value;
                            work_value = scratch->unk_168.u16;
                            work_bits = ((volatile S_func_800AED64_4 *)(scratch))->unk_168.at_16A.unk_16A;
                            work_ptr = (void *) ((u32) work_ptr + (u32) work_value);
                            work_ptr = (void *) ((u32) work_ptr & 0xFFFF);
                            work_bits <<= 0x10;
                            work_value = scratch->unk_0C;
                            work_bits >>= 0x10;
                            work_value += work_bits;
                            work_value <<= 0x10;
                            work_ptr = (void *) ((u32) work_ptr | (u32) work_value);
                            scratch->unk_F8 = (s32) work_ptr;
                            gte_ldv0((u8 *)scratch + 0xF8);
                            ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_0C = (s32) polygon->unk_08;
                            gte_rtps_nn();
                            ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_14 = (s32) polygon->unk_0C;
                            ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_1C = (u16) *(s32 *)((u8 *)(u8 *)scratch + 0x172);
                            ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_24 = (u16) scratch->unk_16C.s32;
                            gte_stsxy(packet_xy3);
                            gte_stszotz((u8 *)scratch + 0xD4);
                            work_ptr = (void *)scratch->unk_D4;
                            work_value = scratch->unk_C8;
                            work_bits = work_value << 1;
                            work_value += work_bits;
                            work_value += (s32)work_ptr;
                            work_value += 3;
                            work_value >>= 2;
                            scratch->unk_C8 = work_value;
                            if ((u32) work_value >= 0x200U) {
                                scratch->unk_C8 = 0x1FF;
                            }
                            if ((((s32) scratch->unk_C8 < 0x1C1) || ((s32) (scratch->unk_E4.u16 << 0x10) >= 0) || ((work_value = scratch->unk_14C, work_value <<= 3, work_ptr = (void *)(work_value + (s32)normals), lookup_value = work_ptr, (((S_func_800AED64_16 *)(lookup_value))->unk_04 < 0)) && !(((S_func_800AED64_16 *)(lookup_value))->unk_00 & 0x0FFF0FFF))) && ((u32) scratch->unk_C8 < 0x200U)) {
                                ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_03 = 9;
                                ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_04.s32 = (s32) scratch->unk_04;
                                if (scratch->unk_16C.at_16F.unk_16F & 1) {
                                    ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_04.at_07.unk_07 |= 2;
                                } else {
                                    work_value = 0xC000;
                                    work_bits = scratch->unk_17C & 0xC000;
                                    if (work_bits == work_value) {
                                        work_value = ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_10;
                                        work_bits = ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_18;
                                        work_ptr = ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_20;
                                        packet_xy3 += 0x28;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_0C = work_value;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_10 = work_bits;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_14 = (s32) work_ptr;
                                        work_bits = scratch->unk_110;
                                        work_value = 5;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_03 = work_value;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_04.s32 = work_bits;
                                        packet_color += 0x28;
                                        work_value = scratch->unk_C8;
                                        work_bits = scratch->unk_BC;
                                        work_value <<= 2;
                                        work_value += work_bits;
                                        work_bits = *packet;
                                        work_value = ((S_func_800AED64_11 *)((void *)work_value))->unk_00;
                                        work_bits &= tag_high_mask;
                                        work_value &= tag_low_mask;
                                        work_bits |= work_value;
                                        *packet = work_bits;
                                        work_ptr = (void *)(scratch->unk_C8 * 4);
                                        work_value = scratch->unk_BC;
                                        work_ptr = (void *)((s32)work_ptr + work_value);
                                        work_value = (s32) packet & tag_low_mask;
                                        work_bits = ((S_func_800AED64_11 *)(work_ptr))->unk_00;
                                        packet = (s32 *)((s8 *)packet + 0x28);
                                        work_bits &= tag_high_mask;
                                        work_bits |= work_value;
                                        ((S_func_800AED64_11 *)(work_ptr))->unk_00 = work_bits;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_03 = one;
                                        work_bits = scratch->unk_176;
                                        work_value = 0xE1000000;
                                        work_bits &= 0x9FF;
                                        work_bits |= work_value;
                                        ((S_func_800AED64_14 *)((u8 *)packet_color - 0x4))->unk_04.s32 = work_bits;
                                    }
                                }
                                packet_color += 0x28;

                                packet_xy3 += 0x28;
                                work_value = scratch->unk_C8;
                                work_bits = scratch->unk_BC;
                                work_value <<= 2;
                                work_value += work_bits;
                                work_bits = *packet;
                                work_value = ((S_func_800AED64_11 *)((void *)work_value))->unk_00;
                                work_bits &= tag_high_mask;
                                work_value &= tag_low_mask;
                                work_bits |= work_value;
                                *packet = work_bits;
                                work_ptr = (void *)(scratch->unk_C8 * 4);
                                work_value = scratch->unk_BC;
                                work_ptr = (void *)((s32)work_ptr + work_value);
                                work_bits = ((S_func_800AED64_11 *)(work_ptr))->unk_00;
                                work_value = (s32) packet & tag_low_mask;
                                packet = (s32 *)((s8 *)packet + 0x28);
                                work_bits &= tag_high_mask;
                                work_bits |= work_value;
                                ((S_func_800AED64_11 *)(work_ptr))->unk_00 = work_bits;
                                work_bits = scratch->unk_16C.at_16E.unk_16E;
                                if ((work_bits & 0xF) == one) {
                                    work_value = scratch->unk_16C.at_16F.unk_16F;
                                    work_value <<= 0x18;
                                    if (work_value >= 0) {
                                        work_bits = (u32) work_bits >> 4;
                                        work_value = work_bits * 3;
                                        work_value *= 8;
                                        work_value += 0x18;
                                        polygon = (s8 *) (u8 *)polygon + work_value;
                                        continue;
                                    }
                                    goto finish_tile;
                                }
                                goto next_polygon;
                            }
                            goto finish_tile;
                        }
                        if (((S_func_800AED64_16 *)((((u16) scratch->unk_170 * 8) + normals)))->unk_04 < 0) {
                            if (scratch->unk_16C.at_16E.unk_16E == one) {
                                work_value = (s32) scratch->unk_16C.at_16F.unk_16F << 0x18;
                                goto check_polygon_end;
                            }
                            goto next_polygon;
                        }
                        work_bits = scratch->unk_16C.at_16E.unk_16E;
                        if (work_bits & 0xF0) {
                            goto skip_polygons;
                        }
                        work_value = scratch->unk_16C.at_16F.unk_16F;
                        work_value <<= 0x18;
                        if (work_value >= 0) {
skip_polygons:
                            work_bits &= 0xF;
                            work_value = work_bits * 3;
                            work_value *= 8;
                            polygon = (s8 *) (u8 *)polygon + work_value;
                            continue;
                        }
                        goto finish_tile;
                    }
                    if (polygon->unk_14.at_16.unk_16 != one) {
                        goto next_polygon;
                    }
                    work_value = polygon->unk_14.at_17.unk_17;
check_polygon_end:
                    if (work_value >= 0) {
next_polygon:

                        polygon = (s8 *) (u8 *)polygon + 0x18;
                        continue;
                    }
                    break;
                }
finish_tile:
                if ((u32) scratch->unk_164 >= packet) {
                    goto advance_column;
                }
                goto finish_draw;
            }
advance_column:
            scratch->unk_134 += 1;
            next_x = scratch->unk_14.s32 + 0x40;
            scratch->unk_14.s32 = next_x;
            if (scratch->unk_18 < next_x) {
                polygon = (void *)3;
                goto advance_row;
            }
            goto scan_column;
        }
advance_row:
        column_rounding = -1;
        row_progress = scratch->unk_0C;
        end_edge = (s32 *)((u8 *)scratch + 0x78);
        row_progress += 0x40;
        scratch->unk_0C = row_progress;
        do {
            if (end_edge->unk_38 > 0) {
                row_progress = end_edge->unk_28 - 0x40;
                end_edge->unk_28 = row_progress;
                if (row_progress <= 0) {
                    end_edge->unk_38 = column_rounding;
                    scratch->unk_174 = scratch->unk_174 - 1;
                }
            }
            polygon = (S_func_800AED64_13 *)((u8 *)polygon - 1);
            end_edge = (S_func_800AED64_7 *)((u8 *)end_edge - 0x28);
        } while ((s32) polygon >= 0);
        if (scratch->unk_174 == 0) {
            goto finish_draw;
        }
        goto scan_row;
    }
finish_draw:
    ((S_func_800AED64_6 *)(render_state->unk_00))->unk_8D0 = packet;
    {
        S_func_800AED64_17 *scene_state;
        scene_state = D_8006ADBC;
        if ((scene_state->unk_18 == 0xC) && ((u32) (scene_state->unk_1A - 0x25) >= 5U) && ((s16) scene_state->unk_1A != 0x34)) {
            func_800AD138(scratch->unk_164);
        }
    }
}
