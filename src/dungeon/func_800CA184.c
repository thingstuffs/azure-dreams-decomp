#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/ot_link.h"
#include "shared/gpu_packets.h"


/* One face of a cell's face list (0x18 bytes): four vertex indices, the packet's UV/CLUT and UV/tpage words, then the
 * attribute word (normal index in the low half) and the info word (texture, skip count, flags). */
typedef struct CellFace {
    u16 v0;             /* 0x00 */
    u16 v1;             /* 0x02 */
    u16 v2;             /* 0x04 */
    u16 v3;             /* 0x06 */
    s32 uv0_clut;       /* 0x08 */
    s32 uv1_tpage;      /* 0x0C */
    s32 attr;           /* 0x10 */
    s32 info;           /* 0x14 */
} CellFace;

/* A map vertex (8 bytes): packed x/y word and height. */
typedef struct MapVertex {
    s32 xy;
    u16 z;
    u16 pad_06;
} MapVertex;

/* A map normal (8 bytes): packed x/y word and height sign. */
typedef struct MapNormal {
    s32 xy;
    s16 z;
    s16 pad_06;
} MapNormal;

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
    MapVertex *vertices;
    CellRec *cells;
    MapNormal *normals;
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
    GameView *view;
    u8 *packet;
    MapGrid *map;
    GameWork *scene;
    CellFace *face;
    MapNormal *normal;
    CellRec *cell;
    CellRec *neighbor;
    void *packet_addr;
    u8 *packet_code;
    void *render_input;
    s32 loop_tmp;
    s32 view_depth;
    s32 minus_one;
    s32 vertex_x;

    scene = &gameWork;
    render_flags = D_80013714;
    view_scratch = (RenderScratch *)0x1F800000;
    view = &scene->view;
    map = &scene->map;
    cells = (CellRec *)scene->map.cells;
    vertices = map->unk_08;
    normals = map->unk_0C;
    if (!(render_flags & 2)) {
        s32 corner_arg;
        s32 column_mask;
        s32 row_mask;
        s32 max_height;

        coord = func_800BCB04((u16)view->unk_0A4, (u16)view->unk_0A6,
            (s16) (view->unk_0A8 - 0x20));
        if (coord < 0x201) {
            view_scratch->view_height = coord;
        } else {
            view_scratch->view_height = 0;
        }
        func_80064D50(&view->unk_058);
        func_80064624(view->unk_084, view->unk_088);
        func_80064D20(&view->unk_038);
        corner_arg = (s32)(view_corners);
        scratch = view_scratch;
        view_depth = scratch->view_height;
        scene->view.unk_006 = 0x1BA;
        func_80046884(view, (void *)corner_arg, view_depth);
        packet = (u8 *)view;
        reset_page = (u8 *)0x800E0000;
        if (reset_page[-0x30A8] != 0) {
            corner_0_x = view_corners[0];
            corner_0_y = view_corners[1];
            corner_0_z = view_corners[2];
            corner_1_x = (u16)((GameView *)packet)->unk_010;
            corner_1_y = (u16)((GameView *)packet)->unk_012;
            corner_1_z = (u16)((GameView *)packet)->unk_014;
            corner_2_x = (u16)((GameView *)packet)->unk_018;
            corner_2_y = (u16)((GameView *)packet)->unk_01A;
            corner_2_z = (u16)((GameView *)packet)->unk_01C;
            corner_3_x = (u16)((GameView *)packet)->unk_020;
            corner_3_y = (u16)((GameView *)packet)->unk_022;
            corner_3_z = (u16)((GameView *)packet)->unk_024;
            reset_page[-0x30A8] = 0;
            ((GameView *)packet)->unk_008 = corner_0_x;
            ((GameView *)packet)->unk_028 = corner_0_x;
            ((GameView *)packet)->unk_00A = corner_0_y;
            ((GameView *)packet)->unk_00C = corner_0_z;
            ((GameView *)packet)->unk_02C = corner_0_z;
            ((GameView *)packet)->unk_010 = corner_1_x;
            ((GameView *)packet)->unk_012 = corner_1_y;
            ((GameView *)packet)->unk_014 = corner_1_z;
            ((GameView *)packet)->unk_018 = corner_2_x;
            ((GameView *)packet)->unk_01A = corner_2_y;
            ((GameView *)packet)->unk_01C = corner_2_z;
            ((GameView *)packet)->unk_020 = corner_3_x;
            ((GameView *)packet)->unk_022 = corner_3_y;
            ((GameView *)packet)->unk_024 = corner_3_z;
        } else {
            {
                s32 blended_coord;
                s32 coord_delta;
                s32 next_delta;
                s32 old_coord;

                coord_delta = (s16)view_corners[0];
                blended_coord = ((GameView *)packet)->unk_008;
                next_delta = (s16)view_corners[1];
                old_coord = ((GameView *)packet)->unk_00A;
                coord_delta -= blended_coord;
                coord_delta >>= 1;
                next_delta -= old_coord;
                next_delta >>= 1;
                blended_coord = (u16)((GameView *)packet)->unk_008;
                old_coord = ((GameView *)packet)->unk_00C;
                blended_coord += coord_delta;
                ((GameView *)packet)->unk_008 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_00A;
                coord_delta = (s16)view_corners[2];
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((GameView *)packet)->unk_00A = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_00C;
                next_delta = (s16)view_corners[4];
                old_coord = ((GameView *)packet)->unk_010;
                blended_coord += coord_delta;
                next_delta -= old_coord;
                next_delta >>= 1;
                ((GameView *)packet)->unk_00C = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_010;
                coord_delta = (s16)view_corners[5];
                old_coord = ((GameView *)packet)->unk_012;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((GameView *)packet)->unk_010 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_012;
                next_delta = (s16)view_corners[6];
                old_coord = ((GameView *)packet)->unk_014;
                blended_coord += coord_delta;
                next_delta -= old_coord;
                next_delta >>= 1;
                ((GameView *)packet)->unk_012 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_014;
                coord_delta = (s16)view_corners[8];
                old_coord = ((GameView *)packet)->unk_018;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((GameView *)packet)->unk_014 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_018;
                next_delta = (s16)view_corners[9];
                old_coord = ((GameView *)packet)->unk_01A;
                blended_coord += coord_delta;
                next_delta -= old_coord;
                next_delta >>= 1;
                ((GameView *)packet)->unk_018 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_01A;
                coord_delta = (s16)view_corners[10];
                old_coord = ((GameView *)packet)->unk_01C;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                ((GameView *)packet)->unk_01A = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_01C;
                coord_delta >>= 1;
                blended_coord += coord_delta;
                do {
                    ((GameView *)packet)->unk_01C = blended_coord;
                } while (0);
                coord_delta = (s16)view_corners[12];
                blended_coord = ((GameView *)packet)->unk_020;
                next_delta = (s16)view_corners[13];
                old_coord = ((GameView *)packet)->unk_022;
                loop_tmp = (u16)((GameView *)packet)->unk_00C;
                coord_delta -= blended_coord;
                coord_delta >>= 1;
                next_delta -= old_coord;
                blended_coord = (u16)((GameView *)packet)->unk_020;
                old_coord = ((GameView *)packet)->unk_024;
                blended_coord += coord_delta;
                ((GameView *)packet)->unk_020 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_022;
                coord_delta = (s16)view_corners[14];
                next_delta >>= 1;
                ((GameView *)packet)->unk_02C = loop_tmp;
                blended_coord += next_delta;
                coord_delta -= old_coord;
                coord_delta >>= 1;
                ((GameView *)packet)->unk_022 = blended_coord;
                blended_coord = (u16)((GameView *)packet)->unk_024;
                next_delta = (u16)((GameView *)packet)->unk_008;
                old_coord = (u16)((GameView *)packet)->unk_00A;
                blended_coord += coord_delta;
                ((GameView *)packet)->unk_024 = blended_coord;
                ((GameView *)packet)->unk_028 = next_delta;
                ((GameView *)packet)->unk_02A = old_coord;
            }
        }
        {
            s32 setup_arg;
            s32 setup_render;
            s32 setup_value;
            s32 setup_base;
            s32 width_shift_or_end;
            register s32 draw_mode ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            render_input = packet + 8;
            setup_arg = (s32)((u32)scratch | 0x01C);
            setup_value = *(s32 *)&((GameView *)packet)->unk_090;
            setup_render = (s32)((u32)scratch | 0x174);
            scratch->color = setup_value;
            setup_value = (s32)0x80010000;
            setup_base = (s32)scene->unk_000;
            width_shift_or_end = map->shiftX;
            face = (CellFace *)(s32)map->shiftY;   /* the height shift word, parked in the face register (ASM_KEEP4 pin) */
            column_mask = map->maskX;
            row_mask = map->maskY;
            ASM_KEEP4(width_shift_or_end, face, column_mask, row_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            max_height = *(s32 *)(setup_value + 0x3180);
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
            scratch->height_shift = (s32)face;
            scratch->map_width = setup_value;
            do {
                setup_value = scratch->height_shift;
            } while (0);
            setup_base <<= setup_value;
            scratch->column_mask = column_mask;
            scratch->row_mask = row_mask;
            scratch->overlay_color = max_height;
            scratch->draw_mode = (u16)draw_mode;
            width_shift_or_end = (s32)scene->unk_000;
            setup_value = 0xAF3A;
            scratch->map_height = setup_base;
            packet = ((GpuContext *)width_shift_or_end)->packetCursor;
            width_shift_or_end += setup_value;
            setup_value = 0xFFFF;
            scratch->last_normal = setup_value;
            scratch->packet_end = width_shift_or_end;
            scratch->active_edges = 4U;
            scratch->cur_y = (s16)func_80046C20(render_input, (void *)setup_arg, setup_render,
                (void *)width_shift_or_end);
        }
        if (scratch->active_edges != 0) {
            s32 tag_mask;
            s32 edge_progress;
            s32 error_step;

            row_mask = 1;
            max_height = 0x7FFF;
            column_mask = 0xFFFFFF;
            tag_mask = (s32)0xFF000000;
            do {
            for (loop_tmp = 3; loop_tmp >= 0; loop_tmp--) {
                if (scratch->edges[loop_tmp].state == 0) {
                    s32 edge_start_y;
                    s32 current_y;

                    edge_start_y = scratch->edges[loop_tmp].start_y;
                    current_y = scratch->cur_y;
                    if (current_y >= edge_start_y) {
                        scratch->edges[loop_tmp].state = row_mask;
                    }
                }
            }
            loop_tmp = 3;
            scratch->min_x.word = max_height;
            scratch->max_x = -0x7FFF;
            for (; loop_tmp >= 0; loop_tmp--) {
                if (scratch->edges[loop_tmp].state > 0) {
                    coord = scratch->edges[loop_tmp].x;
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

                        edge_progress = scratch->edges[loop_tmp].error;
                        edge_error = scratch->edges[loop_tmp].error_inc;
                        edge_progress += edge_error;
                        scratch->edges[loop_tmp].error = edge_progress;
                        if (edge_progress >= 0) {
loop_22:
                            {
                                edge_progress = scratch->edges[loop_tmp].x;
                                edge_error = scratch->edges[loop_tmp].x_inc;
                                error_step = scratch->edges[loop_tmp].error_dec;
                                edge_progress += edge_error;
                                edge_error = scratch->edges[loop_tmp].error;
                                scratch->edges[loop_tmp].x = edge_progress;
                                edge_progress = scratch->edges[loop_tmp].height;
                                edge_error -= error_step;
                                edge_progress -= 0x40;
                                scratch->edges[loop_tmp].error = edge_error;
                                scratch->edges[loop_tmp].height = edge_progress;
                            }
                            if ((edge_progress > 0) && (edge_error >= 0)) {
                                goto loop_22;
                            }
                        }
                    }
                    edge_x = scratch->edges[loop_tmp].x;
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
                            face = (CellFace *)((void **)map->unk_04)[cells[scratch->cell_index].index];
L_CFE98:
                            {
                                s32 vertex_value;
                                s32 vertex_offset;
                                s32 vertex_xy;
                                s32 third_x;

                                vertex_value = face->attr;
                                vertex_xy = scratch->min_x.h.x;
                                scratch->face_attr.word = vertex_value;
                                vertex_value = face->v0;
                                vertex_offset = face->info;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                scratch->face_info.word = vertex_offset;
                                vertex_value = ((MapVertex *)((void *)vertex_value))->xy;
                                vertex_offset = scratch->cell_height.h.x;
                                scratch->vtx.word = vertex_value;
                                vertex_value = face->v0;
                                vertex_x = scratch->vtx.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_xy += vertex_x;
                                vertex_value = ((MapVertex *)((void *)vertex_value))->z;
                                vertex_xy &= 0xFFFF;
                                vertex_value -= vertex_offset;
                                scratch->v[0].z = (u16)vertex_value;
                                vertex_value = scratch->vtx.h.y;
                                vertex_offset = scratch->cur_y;
                                vertex_value = (s16)vertex_value;
                                vertex_offset += vertex_value;
                                vertex_offset <<= 16;
                                vertex_value = face->v1;
                                vertex_xy |= vertex_offset;
                                scratch->v[0].xy = vertex_xy;

                                vertex_xy = scratch->min_x.h.x;
                                vertex_offset = scratch->cell_height.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                scratch->vtx.word = ((MapVertex *)((void *)vertex_value))->xy;
                                vertex_value = face->v1;
                                vertex_x = scratch->vtx.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_xy += vertex_x;
                                vertex_value = ((MapVertex *)((void *)vertex_value))->z;
                                vertex_xy &= 0xFFFF;
                                vertex_value -= vertex_offset;
                                scratch->v[1].z = (u16)vertex_value;
                                vertex_value = scratch->vtx.h.y;
                                vertex_offset = scratch->cur_y;
                                vertex_value = (s16)vertex_value;
                                vertex_offset += vertex_value;
                                vertex_offset <<= 16;
                                vertex_value = face->v2;
                                vertex_xy |= vertex_offset;
                                scratch->v[1].xy = vertex_xy;

                                vertex_xy = scratch->min_x.h.x;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_value = ((MapVertex *)((void *)vertex_value))->xy;
                                scratch->vtx.word = vertex_value;
                                third_x = scratch->vtx.h.x;
                                vertex_offset = scratch->vtx.h.y;
                                vertex_xy += third_x;
                                vertex_xy &= 0xFFFF;
                                vertex_offset = (s16)vertex_offset;
                                vertex_value = ((scratch->cur_y) + vertex_offset) << 16;
                                vertex_xy |= vertex_value;
                                scratch->v[2].xy = vertex_xy;
                                vertex_value = face->v2;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_offset = ((MapVertex *)((void *)vertex_value))->z;
                                vertex_value = scratch->cell_height.h.x;
                                vertex_offset -= vertex_value;
                                scratch->v[2].z = (u16)vertex_offset;
                            }
                            gte_ldv3(&scratch->v[0], &scratch->v[1], &scratch->v[2]);
                            {
                                s32 cell_height;

                                edge_progress = vertices[face->v3].z;
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
                                        normal = (MapNormal *)((normal_index * 8) + (s32)normals);
                                        if (normal->z >= 0) {
                                            normal_xy = normal->xy;
                                            if (!(normal_xy & 0x0FFF0FFF)) {
                                                scratch->step.word = normal_xy;
                                                normal_x = scratch->step.h.x;
                                                if ((s16) normal_x > 0) {
                                                    scratch->step.h.x = (u16)row_mask;
                                                } else {
                                                    if ((s16) normal_x < 0) {
                                                        *(s16 *)&scratch->step.h.x = -1;
                                                    }
                                                }
                                                normal_y = scratch->step.h.y;
                                                if ((s16) normal_y > 0) {
                                                    row_step = row_mask << scratch->width_shift;
                                                    *(s16 *)&scratch->step.h.y = (s16)row_step;
                                                } else if ((s16) normal_y < 0) {
                                                    row_step = 0 - (row_mask << scratch->width_shift);
                                                    *(s16 *)&scratch->step.h.y = (s16)row_step;
                                                }
                                                {
                                                    s32 neighbor_offset;
                                                    s32 row_offset_mask;

                                                    neighbor_offset = scratch->step.h.x;
                                                    error_step = scratch->column;
                                                    vertex_x = scratch->step.h.y;
                                                    row_offset_mask = scratch->row_mask;
                                                    loop_tmp = scratch->width_shift;
                                                    neighbor_offset = (s16)neighbor_offset;
                                                    error_step += neighbor_offset;
                                                    neighbor_offset = scratch->column_mask;
                                                    vertex_x <<= 16;
                                                    vertex_x >>= 16;
                                                    error_step &= neighbor_offset;
                                                    row_offset_mask <<= loop_tmp;
                                                    scratch->neighbor_index = error_step;
                                                    neighbor_offset = scratch->row_base;
                                                    neighbor_offset += vertex_x;
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
                                                                if ((scratch->face_info.b.skip != row_mask)
                                                                    || ((s8) neighbor_face_flags) >= 0) {
                                                                    face++;
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
                                        gte_ldv0(&normals[scratch->last_normal]);
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
                                            face += face_skip;
                                            goto L_CFE98;
                                        }
                                    } else {
                                        scratch->vtx.word =
                                            vertices[face->v3].xy;
                                        scratch->v[3].xy = (((u16) scratch->min_x.word
                                            + (u16) scratch->vtx.word) & 0xFFFF)
                                        | ((scratch->cur_y + (s16) scratch->vtx.h.y) << 0x10);
                                        gte_ldv0(&scratch->v[3]);
                                        *(s32 *)(packet_code + 5) = (s32) face->uv0_clut;
                                        gte_rtps_nn();
                                        *(s32 *)(packet_code + 0xD) = (s32) face->uv1_tpage;
                                        *(u16 *)(packet_code + 0x15) = scratch->face_attr.h.y;
                                        *(u16 *)(packet_code + 0x1D) = (u16) scratch->face_info.word;
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
                                            packet_code[-4] = 9;
                                            *(s32 *)(packet_code - 3) = (s32) scratch->lit_color;
                                            face_flags = scratch->face_info.b.flags;
                                            if (face_flags & 1) {
                                                *packet_code |= 2;
                                            } else {
                                                if ((scratch->blend != 0)
                                                    && (cells[scratch->cell_index].flags & 0x80)
                                                    && !(face_flags & 2)
                                                    && ((view_height = scratch->view_height,
                                                    (((s16) scratch->v[0].z < view_height) != 0))
                                                        || ((s16) scratch->v[1].z < view_height)
                                                        || ((s16) scratch->v[2].z < view_height)
                                                        || ((s16) scratch->v[3].z < view_height))) {
                                                    *(s32 *)(packet_code + 5) =
                                                        *(s32 *)(packet_code + 9);
                                                    *(s32 *)(packet_code + 9) =
                                                        *(s32 *)(packet_code + 0x11);
                                                    *(s32 *)(packet_code + 0xD) =
                                                        *(s32 *)(packet_code + 0x19);
                                                    overlay_color = scratch->overlay_color;
                                                    packet_code[-4] = 5;
                                                    *(s32 *)(packet_code - 3) = overlay_color;
                                                    packet_code += 0x28;
                                                    OT_SETADDR(packet, OT_GETADDR((scratch->otz * 4) + scratch->ot_base, column_mask),
                                                        tag_mask, column_mask);
                                                    error_step = scratch->otz;
                                                    error_step *= 4;
                                                    error_step += scratch->ot_base;
                                                    {
                                                        s32 overlay_addr;

                                                        overlay_addr = (s32) packet & column_mask;
                                                        edge_progress = *(s32 *)error_step;
                                                        packet += 0x28;
                                                        edge_progress &= tag_mask;
                                                        edge_progress |= overlay_addr;
                                                        *(s32 *)error_step = edge_progress;
                                                    }
                                                    packet_code[-4] = row_mask;
                                                    {

                                                        edge_progress = scratch->draw_mode;
                                                        edge_progress &= 0x9FF;
                                                        edge_progress |= 0xE1000000;
                                                        *(s32 *)(packet_code - 3) = edge_progress;
                                                    }
                                                }
                                            }
                                            packet_code += 0x28;
                                            packet_addr = (void *) ((s32) packet & column_mask);
                                        } else if ((u32) quad_depth < 0x1DEU) {
                                            packet_code[-4] = 9;
                                            *(s32 *)(packet_code - 3) = (s32) scratch->lit_color;
                                            packet_addr = (void *) ((s32) packet & column_mask);
                                            *packet_code |= 2;
                                            packet_code += 0x28;
                                        } else {
                                            goto block_98;
                                        }
                                        OT_SETADDR(packet, OT_GETADDR((scratch->otz * 4) + scratch->ot_base, column_mask), tag_mask, column_mask);
                                        ot_entry = (scratch->otz * 4) + scratch->ot_base;
                                        *ot_entry = (*ot_entry & tag_mask) | (s32) packet_addr;
                                        packet += 0x28;
                                        face_skip = scratch->face_info.b.skip;
                                        if ((face_skip & 0xF) == row_mask) {
                                            if (((s8) scratch->face_info.b.flags) >= 0) {
                                                face += ((u32)face_skip >> 4) + 1;
                                                goto L_CFE98;
                                            }
                                        } else {
                                            face++;
                                            goto L_CFE98;
                                        }
                                    }
                                }
                            } else {
                                if (normals[scratch->face_attr.h.x].z < 0) {
                                    s32 end_marker;

                                    end_marker = 0x8001;
                                    edge_progress = scratch->face_info.h.mode;
                                    edge_progress &= 0x80FF;
                                    if (edge_progress != end_marker) {
                                        face++;
                                        goto L_CFE98;
                                    }
                                } else {
                                    face_skip = scratch->face_info.b.skip;
                                    if ((face_skip & 0xF0) || ((s8) scratch->face_info.b.flags) >= 0) {
                                        face_skip &= 0xF;
                                        face += face_skip;
                                        goto L_CFE98;
                                    }
                                }
                            }
block_98:
                            if ((u32) scratch->packet_end < (u32) packet) {
                                ((GpuContext *)scene->unk_000)->packetCursor = packet;
                                return;
                            }
                        }
                        next_column = scratch->column + 1;
                        scratch->column = next_column;
                        scratch->column = next_column & scratch->column_mask;
                        next_x = scratch->min_x.word + 0x40;
                        scratch->min_x.word = next_x;
                    }
                }
                loop_tmp = 3;
                minus_one = -1;
                scratch->cur_y += 0x40;
                for (; loop_tmp >= 0; loop_tmp--) {
                    if (scratch->edges[loop_tmp].state > 0) {
                        edge_remaining = scratch->edges[loop_tmp].remaining - 0x40;
                        scratch->edges[loop_tmp].remaining = edge_remaining;
                        if (edge_remaining < -0x7F) {
                            scratch->edges[loop_tmp].state = minus_one;
                            scratch->active_edges = (u16) (scratch->active_edges - 1);
                        }
                    }
                }
            }
            } while (scratch->active_edges != 0);
        }
        ((GpuContext *)scene->unk_000)->packetCursor = packet;
    }
}
