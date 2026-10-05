#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"

typedef struct S_800CF8E4_0 {
    void * unk_00;
    u8 pad_04[0x1A];
    s16 unk_1E;
    u8 pad_20[0x1BC];
    s32 unk_1DC;
} S_800CF8E4_0;   /* var_s6 in func_800CF8E4 */

typedef struct S_800CF8E4_1 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800CF8E4_1;   /* temp_s5 in func_800CF8E4 */

typedef struct S_800CF8E4_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x56];
    s32 unk_84;
    s32 unk_88;
    u8 pad_8C[0x4];
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
} S_800CF8E4_2;   /* temp_s1 in func_800CF8E4 */

typedef struct S_800CF8E4_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CF8E4_3;   /* (void *)init_a3 in func_800CF8E4 */

typedef struct S_800CF8E4_6 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800CF8E4_6;   /* temp_t0_2 in func_800CF8E4 */

typedef struct S_800CF8E4_7 {
    s32 unk_00;
    u16 unk_04;
} S_800CF8E4_7;   /* (void *)geom_v0 in func_800CF8E4 */

typedef struct S_800CF8E4_8 {
    s32 unk_00;
    s16 unk_04;
} S_800CF8E4_8;   /* temp_v1_11 in func_800CF8E4 */

typedef struct S_800CF8E4_9_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800CF8E4_9_pre;   /* the 0x4 bytes before var_a3 in func_800CF8E4, addressed as var_a3[-1] */

typedef struct S_800CF8E4_9 {
    u8 unk_00;
} S_800CF8E4_9;   /* var_a3 in func_800CF8E4 */

typedef struct S_800CF8E4_10 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_800CF8E4_10;   /* ((scratch->face_attr.h.x * 8) + temp_s4) in func_800CF8E4 */

typedef struct S_800CF8E4_12 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800CF8E4_12;   /* ((((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2) in func_800CF8E4 */

typedef struct S_800CF8E4_13 {
    s32 unk_00;
} S_800CF8E4_13;   /* (((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2 in func_800CF8E4 */

typedef struct S_800CF8E4_14 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CF8E4_14;   /* ((S_800CF8E4_0 *)var_s6)->unk_00 in func_800CF8E4 */


typedef struct {
    u16 index;
    s16 offset;
    u16 flags;
} CellRec;


typedef struct {
    s32 x;             /* 0x00 */
    s32 error_dec;     /* 0x04 */
    s32 error_inc;     /* 0x08 */
    s32 remaining;     /* 0x0C */
    s32 error;         /* 0x10 */
    s32 x_inc;         /* 0x14 */
    s32 start_y;       /* 0x18 */
    s32 state;         /* 0x1C */
    s32 height;        /* 0x20 */
    s32 pad_24;
} ScanEdge;

typedef struct {
    s32 xy;
    u16 z;
    u16 pad;
} ScratchVertex;

typedef union {
    s32 word;
    struct {
        u16 x;
        u16 y;
    } h;
} ScratchPair;

typedef struct {
    s32 color;                  /* 0x000 */
    s32 lit_color;              /* 0x004 */
    s32 cur_x;                  /* 0x008 */
    s32 cur_y;                  /* 0x00C */
    ScratchPair step;           /* 0x010 */
    ScratchPair min_x;          /* 0x014 */
    s32 max_x;                  /* 0x018 */
    ScanEdge edges[4];          /* 0x01C */
    s32 ot_base;                /* 0x0BC */
    u8 pad_0C0[0x8];
    s32 otz;                    /* 0x0C8 */
    u8 pad_0CC[0x8];
    s32 otz4;                   /* 0x0D4 */
    s32 flag;                   /* 0x0D8 */
    s32 opz;                    /* 0x0DC */
    ScratchVertex v[4];         /* 0x0E0 */
    u8 pad_100[0x10];
    s32 overlay_color;          /* 0x110 */
    s32 map_width;              /* 0x114 */
    s32 map_height;             /* 0x118 */
    s32 column_mask;            /* 0x11C */
    s32 row_mask;               /* 0x120 */
    s32 width_shift;            /* 0x124 */
    s32 height_shift;           /* 0x128 */
    ScratchPair cell_height;    /* 0x12C */
    u8 pad_130[0x4];
    s32 column;                 /* 0x134 */
    s32 row_base;               /* 0x138 */
    s32 neighbor_index;         /* 0x13C */
    u8 pad_140[0x4];
    s32 cell_index;             /* 0x144 */
    s32 min_height;             /* 0x148 */
    s32 last_normal;            /* 0x14C */
    u8 pad_150[0x8];
    s32 view_height;            /* 0x158 */
    u8 pad_15C[0x8];
    ScratchPair vtx;            /* 0x164 */
    u8 pad_168[0x4];
    union {
        s32 word;
        struct {
            u16 tex;
            u8 skip;
            u8 flags;
        } b;
        struct {
            u16 tex;
            u16 mode;
        } h;
    } face_info;                /* 0x16C */
    ScratchPair face_attr;      /* 0x170 */
    u16 active_edges;           /* 0x174 */
    u16 draw_mode;              /* 0x176 */
    u16 blend;                  /* 0x178 */
    u16 pad_17A;
    s32 packet_end;             /* 0x17C */
} RenderScratch;


s32 func_80046884();
s32 func_80046C20();
s32 func_80064624();
s32 func_80064D20();
s32 func_80064D50();
s16 func_800BCB04();

/* Render visible dungeon cells as lit, textured polygons in the ordering table. */
void func_800CF8E4(void) {
    RenderScratch *scratch;
    RenderScratch *view_scratch;
    u16 view_corners[23];
    s32 *ot_entry;
    s32 neighbor_index;
    u8 *vertices;
    CellRec *cells;
    u8 *normals;
    s32 render_flags;
    s32 row_step;
    s32 face_skip;
    s32 min_x;
    s32 max_x;
    s32 next_column;
    s32 next_x;
    s32 edge_remaining;
    s32 coord;
    s32 normal_xy;
    s32 occlusion_height;
    s32 quad_depth;
    s32 view_height;
    s32 edge_x;
    s32 scan_x;
    s32 scan_y;
    s32 map_width;
    s32 cell_index;
    s32 overlay_color;
    s32 *overlay_ot_entry;
    u16 normal_x;
    u16 normal_y;
    s32 normal_index;
    u16 neighbor_flags;
    u16 corner_0_x;
    u16 corner_0_y;
    u16 corner_0_z;
    u16 corner_1_x;
    u16 corner_1_y;
    u16 corner_1_z;
    u16 corner_2_x;
    u16 corner_2_y;
    u16 corner_2_z;
    u16 corner_3_x;
    u16 corner_3_y;
    u16 corner_3_z;
    u8 *reset_page;
    u8 neighbor_face_flags;
    s32 face_flags;
    u8 *view;
    u8 *packet;
    u8 *map;
    u8 *scene;
    void *face;
    void *normal;
    CellRec *cell;
    CellRec *neighbor;
    void *packet_addr;
    void *packet_code;
    void *render_input;
    s32 render_arg;
    s32 minus_one;
    register s32 neighbor_row_step ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    scene = (u8 *)((void * *)(&gameWork));
    render_flags = D_80013714;
    view_scratch = (RenderScratch *)0x1F800000;
    view = scene + 0x18;
    map = scene + 0x1DC;
    cells = (CellRec *)((S_800CF8E4_0 *)scene)->unk_1DC;
    vertices = (u8 *)((S_800CF8E4_1 *)map)->unk_08;
    normals = (u8 *)((S_800CF8E4_1 *)map)->unk_0C;
    if (!(render_flags & 2)) {
        s32 corner_arg;

        coord = func_800BCB04(((S_800CF8E4_2 *)view)->unk_A4, ((S_800CF8E4_2 *)view)->unk_A6,
            (s16) (((S_800CF8E4_2 *)view)->unk_A8 - 0x20));
        if (coord < 0x201) {
            view_scratch->view_height = coord;
        } else {
            view_scratch->view_height = 0;
        }
        func_80064D50(((void **)((s8 *)((void **)((s8 *)view + 0x58)))));
        func_80064624(((S_800CF8E4_2 *)view)->unk_84, ((S_800CF8E4_2 *)view)->unk_88);
        func_80064D20(((void **)((s8 *)((void **)((s8 *)view + 0x38)))));
        corner_arg = (s32)(view_corners);
        scratch = view_scratch;
        render_arg = scratch->view_height;
        ((S_800CF8E4_0 *)scene)->unk_1E = 0x1BA;
        func_80046884(view, (void *)corner_arg, render_arg);
        packet = view;
        reset_page = (u8 *)0x800E0000;
        if (reset_page[-0x30A8] != 0) {
            corner_0_x = view_corners[0];
            corner_0_y = view_corners[1];
            corner_0_z = view_corners[2];
            corner_1_x = ((S_800CF8E4_2 *)packet)->unk_10;
            corner_1_y = ((S_800CF8E4_2 *)packet)->unk_12;
            corner_1_z = ((S_800CF8E4_2 *)packet)->unk_14;
            corner_2_x = ((S_800CF8E4_2 *)packet)->unk_18;
            corner_2_y = ((S_800CF8E4_2 *)packet)->unk_1A;
            corner_2_z = ((S_800CF8E4_2 *)packet)->unk_1C;
            corner_3_x = ((S_800CF8E4_2 *)packet)->unk_20;
            corner_3_y = ((S_800CF8E4_2 *)packet)->unk_22;
            corner_3_z = ((S_800CF8E4_2 *)packet)->unk_24;
            reset_page[-0x30A8] = 0;
            ((S_800CF8E4_2 *)packet)->unk_08 = corner_0_x;
            ((S_800CF8E4_2 *)packet)->unk_28 = corner_0_x;
            ((S_800CF8E4_2 *)packet)->unk_0A = corner_0_y;
            ((S_800CF8E4_2 *)packet)->unk_0C = corner_0_z;
            ((S_800CF8E4_2 *)packet)->unk_2C = corner_0_z;
            ((S_800CF8E4_2 *)packet)->unk_10 = corner_1_x;
            ((S_800CF8E4_2 *)packet)->unk_12 = corner_1_y;
            ((S_800CF8E4_2 *)packet)->unk_14 = corner_1_z;
            ((S_800CF8E4_2 *)packet)->unk_18 = corner_2_x;
            ((S_800CF8E4_2 *)packet)->unk_1A = corner_2_y;
            ((S_800CF8E4_2 *)packet)->unk_1C = corner_2_z;
            ((S_800CF8E4_2 *)packet)->unk_20 = corner_3_x;
            ((S_800CF8E4_2 *)packet)->unk_22 = corner_3_y;
            ((S_800CF8E4_2 *)packet)->unk_24 = corner_3_z;
        } else {
            {
                s32 blended_coord;
                s32 coord_delta;
                s32 next_delta;
                s32 old_coord;

                coord_delta = (s16)view_corners[0];
                blended_coord = (s16)((S_800CF8E4_2 *)packet)->unk_08;
                next_delta = (s16)view_corners[1];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_0A;
                coord_delta -= blended_coord;
                coord_delta >>= 1;
                next_delta -= old_coord;
                next_delta >>= 1;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_08;
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_0C;
                blended_coord += coord_delta;
                ((S_800CF8E4_2 *)packet)->unk_08 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_0A;
                coord_delta = (s16)view_corners[2];
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_0A = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_0C;
                next_delta = (s16)view_corners[4];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_10;
                blended_coord += coord_delta;
                next_delta -= old_coord;
                next_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_0C = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_10;
                coord_delta = (s16)view_corners[5];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_12;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_10 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_12;
                next_delta = (s16)view_corners[6];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_14;
                blended_coord += coord_delta;
                next_delta -= old_coord;
                next_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_12 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_14;
                coord_delta = (s16)view_corners[8];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_18;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_14 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_18;
                next_delta = (s16)view_corners[9];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_1A;
                blended_coord += coord_delta;
                next_delta -= old_coord;
                next_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_18 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_1A;
                coord_delta = (s16)view_corners[10];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_1C;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                ((S_800CF8E4_2 *)packet)->unk_1A = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_1C;
                coord_delta >>= 1;
                blended_coord += coord_delta;
                do {
                    ((S_800CF8E4_2 *)packet)->unk_1C = (u16)blended_coord;
                } while (0);
                coord_delta = (s16)view_corners[12];
                blended_coord = (s16)((S_800CF8E4_2 *)packet)->unk_20;
                next_delta = (s16)view_corners[13];
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_22;
                render_arg = ((S_800CF8E4_2 *)packet)->unk_0C;
                coord_delta -= blended_coord;
                coord_delta >>= 1;
                next_delta -= old_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_20;
                old_coord = (s16)((S_800CF8E4_2 *)packet)->unk_24;
                blended_coord += coord_delta;
                ((S_800CF8E4_2 *)packet)->unk_20 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_22;
                coord_delta = (s16)view_corners[14];
                next_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_2C = (u16)render_arg;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((S_800CF8E4_2 *)packet)->unk_22 = (u16)blended_coord;
                blended_coord = ((S_800CF8E4_2 *)packet)->unk_24;
                next_delta = ((S_800CF8E4_2 *)packet)->unk_08;
                old_coord = ((S_800CF8E4_2 *)packet)->unk_0A;
                blended_coord += coord_delta;
                ((S_800CF8E4_2 *)packet)->unk_24 = (u16)blended_coord;
                ((S_800CF8E4_2 *)packet)->unk_28 = (u16)next_delta;
                ((S_800CF8E4_2 *)packet)->unk_2A = (u16)old_coord;
            }
        }
        {
            s32 setup_arg;
            s32 setup_render;
            s32 setup_value;
            s32 setup_base;
            s32 width_shift_or_end;
            register s32 height_shift ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 column_mask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 row_mask ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 base_color ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 draw_mode ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            render_input = packet + 8;
            setup_arg = (s32)((u32)scratch | 0x01C);
            setup_value = ((S_800CF8E4_2 *)packet)->unk_90;
            setup_render = (s32)((u32)scratch | 0x174);
            scratch->color = setup_value;
            setup_value = (s32)0x80010000;
            setup_base = (s32)((S_800CF8E4_0 *)scene)->unk_00;
            width_shift_or_end = ((S_800CF8E4_1 *)map)->unk_14;
            height_shift = ((S_800CF8E4_1 *)map)->unk_16;
            column_mask = ((S_800CF8E4_1 *)map)->unk_18;
            row_mask = ((S_800CF8E4_1 *)map)->unk_1A;
            ASM_KEEP4(width_shift_or_end, height_shift, column_mask, row_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            base_color = *(s32 *)(setup_value + 0x3180);
            draw_mode = *(u8 *)(setup_value + 0x3184);
            setup_value = *(u8 *)(setup_value + 0x3185);
            setup_base += 0xB8;
            do {
                scratch->width_shift = width_shift_or_end;
            } while (0);
            scratch->blend = (u16)setup_value;
            setup_value = scratch->width_shift;
            scratch->ot_base = setup_base;
            setup_base = 0x40;
            setup_value = setup_base << setup_value;
            scratch->height_shift = height_shift;
            scratch->map_width = setup_value;
            do {
                setup_value = scratch->height_shift;
            } while (0);
            setup_base <<= setup_value;
            scratch->column_mask = column_mask;
            scratch->row_mask = row_mask;
            scratch->overlay_color = base_color;
            scratch->draw_mode = (u16)draw_mode;
            width_shift_or_end = (s32)((S_800CF8E4_0 *)scene)->unk_00;
            setup_value = 0xAF3A;
            scratch->map_height = setup_base;
            packet = (u8 *)((S_800CF8E4_3 *)((void *)width_shift_or_end))->unk_8D0;
            width_shift_or_end += setup_value;
            setup_value = 0xFFFF;
            scratch->last_normal = setup_value;
            scratch->packet_end = width_shift_or_end;
            scratch->active_edges = 4U;
            scratch->cur_y = (s16)func_80046C20(render_input, (void *)setup_arg, setup_render,
                (void *)width_shift_or_end);
        }
        if (scratch->active_edges != 0) {
            s32 address_mask;
            s32 one;
            s32 max_height;
            s32 tag_mask;
            register s32 edge_progress ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 error_step;

            one = 1;
            max_height = 0x7FFF;
            address_mask = 0xFFFFFF;
            tag_mask = (s32)0xFF000000;
            do {
            for (render_arg = 3; render_arg >= 0; render_arg--) {
                if (scratch->edges[render_arg].state == 0) {
                    s32 edge_start_y;
                    s32 current_y;

                    edge_start_y = scratch->edges[render_arg].start_y;
                    current_y = scratch->cur_y;
                    if (current_y >= edge_start_y) {
                        scratch->edges[render_arg].state = one;
                    }
                }
            }
            render_arg = 3;
            scratch->min_x.word = max_height;
            scratch->max_x = -0x7FFF;
            for (; render_arg >= 0; render_arg--) {
                if (scratch->edges[render_arg].state > 0) {
                    coord = scratch->edges[render_arg].x;
                    scratch->cur_x = coord;
                    if (coord < scratch->min_x.word) {
                        scratch->min_x.word = coord;
                    } else {
                        if (scratch->max_x < coord) {
                            scratch->max_x = coord;
                        }
                    }
                    {
                        s32 edge_error;

                        edge_progress = scratch->edges[render_arg].error;
                        edge_error = scratch->edges[render_arg].error_inc;
                        edge_progress += edge_error;
                        scratch->edges[render_arg].error = edge_progress;
                        if (edge_progress >= 0) {
loop_22:
                            {
                                edge_progress = scratch->edges[render_arg].x;
                                edge_error = scratch->edges[render_arg].x_inc;
                                error_step = scratch->edges[render_arg].error_dec;
                                edge_progress += edge_error;
                                edge_error = scratch->edges[render_arg].error;
                                scratch->edges[render_arg].x = edge_progress;
                                edge_progress = scratch->edges[render_arg].height;
                                edge_error -= error_step;
                                edge_progress -= 0x40;
                                scratch->edges[render_arg].error = edge_error;
                                scratch->edges[render_arg].height = edge_progress;
                            }
                            if ((edge_progress > 0) && (edge_error >= 0)) {
                                goto loop_22;
                            }
                        }
                    }
                    edge_x = scratch->edges[render_arg].x;
                    scratch->cur_x = edge_x;
                    if (edge_x < scratch->min_x.word) {
                        scratch->min_x.word = edge_x;
                    }
                    scan_x = scratch->cur_x;
                    if (scratch->max_x < scan_x) {
                        scratch->max_x = scan_x;
                    }
                }
            }
            {
                scan_y = scratch->cur_y;
                if ((scan_y >= 0) && (scratch->map_height >= scan_y)) {
                    min_x = (scratch->min_x.word - 0x20) & ~0x3F;
                    scratch->min_x.word = min_x;
                    if (min_x < 0) {
                        scratch->min_x.word = 0;
                    }
                    map_width = scratch->map_width;
                    max_x = (scratch->max_x + 0x20) & ~0x3F;
                    scratch->max_x = max_x;
                    if (map_width < max_x) {
                        scratch->max_x = map_width;
                    }
                    scratch->row_base = (((u32) scratch->cur_y >> 6) & scratch->row_mask)
                    << scratch->width_shift;
                    scratch->column = ((u32) scratch->min_x.word >> 6) & scratch->column_mask;
                    while (scratch->max_x >= scratch->min_x.word) {
                        cell_index = scratch->row_base + scratch->column;
                        scratch->cell_index = cell_index;
                        cell = (CellRec *)((cell_index * 6) + (s32)cells);
                        packet_code = packet + 7;
                        if (cell->index != 0) {
                            scratch->cell_height.word = (s32) cell->offset;
                            face = ((void **)((S_800CF8E4_1 *)map)->unk_04)[cells[scratch->cell_index].index];
L_CFE98:
                            {
                                s32 vertex_value;
                                s32 vertex_offset;
                                s32 vertex_xy;
                                u16 cell_x;
                                register u16 vertex_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                                u16 third_x;

                                vertex_value = ((S_800CF8E4_6 *)face)->unk_10;
                                cell_x = scratch->min_x.h.x;
                                scratch->face_attr.word = vertex_value;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_00;
                                vertex_offset = ((S_800CF8E4_6 *)face)->unk_14;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                scratch->face_info.word = vertex_offset;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_00;
                                vertex_offset = scratch->cell_height.h.x;
                                scratch->vtx.word = vertex_value;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_00;
                                vertex_x = scratch->vtx.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_xy = cell_x + vertex_x;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_04;
                                vertex_xy &= 0xFFFF;
                                vertex_value -= vertex_offset;
                                scratch->v[0].z = (u16)vertex_value;
                                vertex_value = scratch->vtx.h.y;
                                vertex_offset = scratch->cur_y;
                                vertex_value = (s16)vertex_value;
                                vertex_offset += vertex_value;
                                vertex_offset <<= 16;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_02;
                                vertex_xy |= vertex_offset;
                                *(volatile s32 *)&scratch->v[0].xy = vertex_xy;

                                cell_x = *(volatile u16 *)&scratch->min_x.h.x;
                                vertex_offset = scratch->cell_height.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                scratch->vtx.word = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_00;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_02;
                                vertex_x = scratch->vtx.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_xy = cell_x + vertex_x;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_04;
                                vertex_xy &= 0xFFFF;
                                vertex_value -= vertex_offset;
                                scratch->v[1].z = (u16)vertex_value;
                                vertex_value = scratch->vtx.h.y;
                                vertex_offset = scratch->cur_y;
                                vertex_value = (s16)vertex_value;
                                vertex_offset += vertex_value;
                                vertex_offset <<= 16;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_04;
                                vertex_xy |= vertex_offset;
                                *(volatile s32 *)&scratch->v[1].xy = vertex_xy;

                                cell_x = *(volatile u16 *)&scratch->min_x.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_00;
                                scratch->vtx.word = vertex_value;
                                third_x = scratch->vtx.h.x;
                                vertex_offset = scratch->vtx.h.y;
                                vertex_xy = (third_x) + (cell_x);
                                vertex_xy &= 0xFFFF;
                                vertex_offset = (s16)vertex_offset;
                                vertex_value = ((scratch->cur_y) + vertex_offset) << 16;
                                vertex_xy |= vertex_value;
                                scratch->v[2].xy = vertex_xy;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_04;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_offset = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_04;
                                vertex_value = scratch->cell_height.h.x;
                                vertex_offset -= vertex_value;
                                scratch->v[2].z = (u16)vertex_offset;
                            }
                            gte_ldv3(&scratch->v[0], &scratch->v[1], &scratch->v[2]);
                            {
                                s32 cell_height;

                                edge_progress = ((S_800CF8E4_12 *)(((((S_800CF8E4_6 *)face)->unk_06 * 8)
                                    + vertices)))->unk_04;
                                cell_height = scratch->cell_height.h.x;
                                edge_progress -= cell_height;
                                scratch->v[3].z = (u16) edge_progress;
                            }
                            gte_rtpt_nn();
                            gte_nclip();
                            gte_stopz(&scratch->opz);
                            if (scratch->opz >= 0) {
                                gte_stflg(&scratch->flag);
                                if (scratch->flag == 0) {
                                    gte_stsxy3_g3(packet);
                                    gte_avsz3();
                                    gte_stotz(&scratch->otz);
                                    normal_index = scratch->face_attr.h.x;
                                    if (scratch->last_normal != normal_index) {
                                        scratch->last_normal = (s32) normal_index;
                                        normal = (void *)((normal_index * 8) + (s32)normals);
                                        if (((S_800CF8E4_8 *)normal)->unk_04 >= 0) {
                                            normal_xy = ((S_800CF8E4_8 *)normal)->unk_00;
                                            if (!(normal_xy & 0x0FFF0FFF)) {
                                                scratch->step.word = normal_xy;
                                                normal_x = scratch->step.h.x;
                                                if ((s16) normal_x > 0) {
                                                    scratch->step.h.x = (u16)one;
                                                } else {
                                                    if ((s16) normal_x < 0) {
                                                        *(s16 *)&scratch->step.h.x = -1;
                                                    }
                                                }
                                                normal_y = scratch->step.h.y;
                                                if ((s16) normal_y > 0) {
                                                    row_step = one << scratch->width_shift;
                                                    *(s16 *)&scratch->step.h.y = (s16)row_step;
                                                } else if ((s16) normal_y < 0) {
                                                    row_step = 0 - (one << scratch->width_shift);
                                                    *(s16 *)&scratch->step.h.y = (s16)row_step;
                                                }
                                                {
                                                    s32 neighbor_offset;
                                                    s32 row_offset_mask;

                                                    neighbor_offset = scratch->step.h.x;
                                                    error_step = scratch->column;
                                                    neighbor_row_step = *(volatile u16 *)&scratch->step.h.y;
                                                    row_offset_mask = *(volatile s32 *)&scratch->row_mask;
                                                    render_arg = scratch->width_shift;
                                                    neighbor_offset = (s16)neighbor_offset;
                                                    error_step += neighbor_offset;
                                                    neighbor_offset = scratch->column_mask;
                                                    neighbor_row_step = (s16)neighbor_row_step;
                                                    error_step &= neighbor_offset;
                                                    neighbor_offset = scratch->row_base;
                                                    row_offset_mask <<= render_arg;
                                                    *(volatile s32 *)&scratch->neighbor_index = error_step;
                                                    neighbor_offset += neighbor_row_step;
                                                    neighbor_offset &= row_offset_mask;
                                                    error_step += neighbor_offset;
                                                    neighbor_index = error_step;
                                                    scratch->neighbor_index = neighbor_index;
                                                }
                                                neighbor = (CellRec *)((neighbor_index * 6) + (s32)cells);
                                                neighbor_flags = neighbor->flags;
                                                if (!(neighbor_flags & 1)) {
                                                    if (neighbor_flags & 0x80) {
                                                        if (cells[scratch->cell_index].flags & 0x80) {
                                                            neighbor_face_flags = scratch->face_info.b.flags;
                                                            if (!(neighbor_face_flags & 2)) {
                                                                if ((scratch->face_info.b.skip != one)
                                                                    || ((s8) neighbor_face_flags) >= 0) {
                                                                    face = (u8 *)face + 24;
                                                                    scratch->last_normal = 0xFFFF;
                                                                    goto L_CFE98;
                                                                }
                                                                goto block_98;
                                                            }
                                                        }
                                                        scratch->min_height = max_height;
                                                    } else if (!(neighbor_flags & 0x40)) {
                                                        scratch->min_height = -(s32) neighbor->offset;
                                                    } else {
                                                        scratch->min_height = max_height;
                                                    }
                                                } else {
                                                    scratch->min_height = max_height;
                                                }
                                            } else {
                                                scratch->min_height = max_height;
                                            }
                                        } else {
                                            scratch->min_height = max_height;
                                        }
                                        gte_ldrgb(&scratch->color);
                                        gte_ldv0((u8 *)normals + (scratch->last_normal * 8));
                                        gte_nccs();
                                        gte_strgb(&scratch->lit_color);
                                    }
                                    occlusion_height = scratch->min_height;
                                    if (((s16) scratch->v[0].z >= occlusion_height)
                                        && ((s16) scratch->v[1].z >= occlusion_height)
                                        && ((s16) scratch->v[2].z >= occlusion_height)
                                        && ((s16) scratch->v[3].z >= occlusion_height)) {
                                        if (((s8) scratch->face_info.b.flags) >= 0) {
                                            face_skip = scratch->face_info.b.skip;
                                            face_skip &= 0xF;
                                            face = (u8 *)face + (face_skip * 24);
                                            goto L_CFE98;
                                        }
                                    } else {
                                        scratch->vtx.word =
                                            ((S_800CF8E4_13 *)((((S_800CF8E4_6 *)face)->unk_06 * 8) + vertices))->unk_00;
                                        scratch->v[3].xy = (((u16) scratch->min_x.word
                                            + (u16) scratch->vtx.word) & 0xFFFF)
                                        | ((scratch->cur_y + (s16) scratch->vtx.h.y) << 0x10);
                                        gte_ldv0(&scratch->v[3]);
                                        (*(s32 *)((u8 *)packet_code + 5)) = (s32) ((S_800CF8E4_6 *)face)->unk_08;
                                        gte_rtps_nn();
                                        (*(s32 *)((u8 *)packet_code + 0xD)) = (s32) ((S_800CF8E4_6 *)face)->unk_0C;
                                        (*(u16 *)((u8 *)packet_code + 0x15)) = scratch->face_attr.h.y;
                                        (*(u16 *)((u8 *)packet_code + 0x1D)) = (u16) scratch->face_info.word;
                                        gte_stsxy(packet + 0x20);
                                        gte_stszotz(&scratch->otz4);
                                        {
                                            s32 depth_sum;
                                            s32 twice_depth;
                                            s32 fourth_depth;

                                            depth_sum = scratch->otz;
                                            fourth_depth = scratch->otz4;
                                            twice_depth = depth_sum << 1;
                                            depth_sum += twice_depth;
                                            depth_sum += fourth_depth;
                                            quad_depth = depth_sum >> 2;
                                        }
                                        scratch->otz = quad_depth;
                                        if ((u32) quad_depth < 0x1BEU) {
                                            ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = 9;
                                            (*(s32 *)((u8 *)packet_code + -3)) = (s32) scratch->lit_color;
                                            face_flags = scratch->face_info.b.flags;
                                            if (face_flags & 1) {
                                                *(u8 *)packet_code = (u8) (*(u8 *)packet_code | 2);
                                            } else {
                                                if ((scratch->blend != 0)
                                                    && (cells[scratch->cell_index].flags & 0x80)
                                                    && !(face_flags & 2)
                                                    && ((view_height = scratch->view_height,
                                                    (((s16) scratch->v[0].z < view_height) != 0))
                                                        || ((s16) scratch->v[1].z < view_height)
                                                        || ((s16) scratch->v[2].z < view_height)
                                                        || ((s16) scratch->v[3].z < view_height))) {
                                                    (*(s32 *)((u8 *)packet_code + 5)) =
                                                        (s32) (*(s32 *)((u8 *)packet_code + 9));
                                                    (*(s32 *)((u8 *)packet_code + 9)) =
                                                        (s32) (*(s32 *)((u8 *)packet_code + 0x11));
                                                    (*(s32 *)((u8 *)packet_code + 0xD)) =
                                                        (s32) (*(s32 *)((u8 *)packet_code + 0x19));
                                                    overlay_color = scratch->overlay_color;
                                                    ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = 5;
                                                    (*(s32 *)((u8 *)packet_code + -3)) = overlay_color;
                                                    packet_code += 0x28;
                                                    *(s32 *)packet = (*(s32 *)packet & tag_mask)
                                                    | (*(s32 *)((scratch->otz * 4)
                                                        + scratch->ot_base) & address_mask);
                                                    overlay_ot_entry =
                                                        (s32 *)((scratch->otz * 4)
                                                        + scratch->ot_base);
                                                    {
                                                        s32 overlay_addr;

                                                        overlay_addr = (s32) packet & address_mask;
                                                        edge_progress = *overlay_ot_entry;
                                                        packet += 0x28;
                                                        edge_progress &= tag_mask;
                                                        edge_progress |= overlay_addr;
                                                        *overlay_ot_entry = edge_progress;
                                                    }
                                                    ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = one;
                                                    {

                                                        edge_progress = scratch->draw_mode;
                                                        edge_progress &= 0x9FF;
                                                        edge_progress |= 0xE1000000;
                                                        (*(s32 *)((u8 *)packet_code + -3)) = edge_progress;
                                                    }
                                                }
                                            }
                                            packet_code += 0x28;
                                            packet_addr = (void *) ((s32) packet & address_mask);
                                        } else if ((u32) quad_depth < 0x1DEU) {
                                            ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = 9;
                                            (*(s32 *)((u8 *)packet_code + -3)) = (s32) scratch->lit_color;
                                            packet_addr = (void *) ((s32) packet & address_mask);
                                            ((S_800CF8E4_9 *)packet_code)->unk_00 =
                                                (u8) (((S_800CF8E4_9 *)packet_code)->unk_00 | 2);
                                            packet_code += 0x28;
                                        } else {
                                            goto block_98;
                                        }
                                        *(s32 *)packet = (*(s32 *)packet & tag_mask) | (*(s32 *)((scratch->otz * 4) + scratch->ot_base) & address_mask);
                                        ot_entry = (scratch->otz * 4) + scratch->ot_base;
                                        *ot_entry = (*ot_entry & tag_mask) | (s32) packet_addr;
                                        packet += 0x28;
                                        face_skip = scratch->face_info.b.skip;
                                        if ((face_skip & 0xF) == one) {
                                            if (((s8) scratch->face_info.b.flags) >= 0) {
                                                face = (u8 *)face + ((((u32)face_skip >> 4) * 24) + 24);
                                                goto L_CFE98;
                                            }
                                        } else {
                                            face = (u8 *)face + 24;
                                            goto L_CFE98;
                                        }
                                    }
                                }
                            } else {
                                if (((S_800CF8E4_10 *)(((scratch->face_attr.h.x * 8) + normals)))->unk_04 < 0) {
                                    s32 end_marker;

                                    end_marker = 0x8001;
                                    edge_progress = scratch->face_info.h.mode & 0x80FF;
                                    if (edge_progress != end_marker) {
                                        face = (u8 *)face + 24;
                                        goto L_CFE98;
                                    }
                                } else {
                                    face_skip = scratch->face_info.b.skip;
                                    if ((face_skip & 0xF0) || ((s8) scratch->face_info.b.flags) >= 0) {
                                        face_skip &= 0xF;
                                        face = (u8 *)face + (face_skip * 24);
                                        goto L_CFE98;
                                    }
                                }
                            }
block_98:
                            if ((u32) scratch->packet_end < (u32) packet) {
                                goto block_106;
                            }
                        }
                        next_column = scratch->column + 1;
                        scratch->column = next_column;
                        scratch->column = next_column & scratch->column_mask;
                        next_x = scratch->min_x.word + 0x40;
                        scratch->min_x.word = next_x;
                    }
                }
                render_arg = 3;
                minus_one = -1;
                scratch->cur_y += 0x40;
                for (; render_arg >= 0; render_arg--) {
                    if (scratch->edges[render_arg].state > 0) {
                        edge_remaining = scratch->edges[render_arg].remaining - 0x40;
                        scratch->edges[render_arg].remaining = edge_remaining;
                        if (edge_remaining < -0x7F) {
                            scratch->edges[render_arg].state = minus_one;
                            scratch->active_edges = (u16) (scratch->active_edges - 1);
                        }
                    }
                }
            }
            } while (scratch->active_edges != 0);
        }
block_106:
        ((S_800CF8E4_14 *)(((S_800CF8E4_0 *)scene)->unk_00))->unk_8D0 = packet;
    }
}
