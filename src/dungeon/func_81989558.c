#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_80024D58_Point {
    s16 unk_00;
    s16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
} S_80024D58_Point;   /* source_points / rotated_points entry (8 bytes) in func_80024D58 */

typedef struct S_80024D58_Obj {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    s32 unk_0C;
} S_80024D58_Obj;   /* obj in func_80024D58 */

typedef struct S_80024D58_RingParam {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
} S_80024D58_RingParam;   /* ring_params entry (6 bytes apart) in func_80024D58 */



typedef struct S_80024D58_Pair {
    s32 unk_00;
    s32 unk_04;
} S_80024D58_Pair;   /* r1 / r1b in func_80024D58 */

typedef struct S_80024D58_11_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80024D58_11_pre;   /* the 0x8 bytes before arg0 in func_80024D58, addressed as arg0[-1] */


typedef struct Blk8 {
    s32 w0;
    s32 w1;
} __attribute__((packed)) Blk8;

typedef struct Params {
    void *f510;
    void *f514;
    s16 f518;
    s16 f51A;
    u16 f51C;
    u8 pad0E[2];
    Blk8 blk;
    s16 f528;
    s16 f52A;
    u8 pad1C[4];
    s32 f530;
    s32 f534;
} Params;

typedef struct Frame {
    u8 space[1280];
    Params p;
} Frame;

/* Address of cell (row, col) of the 16 x 16 grid of 4-byte points. */
static __inline__ u8 *grid_cell(u8 *grid, s32 row, s32 col)
{
    grid += row << 6;
    col <<= 2;
    return grid + col;
}

extern void func_800DBA90();
extern void func_80065420();
extern void func_800666F4();
extern void func_80066640();
extern s16 func_80066460();
extern s16 func_8006649C();

/* Build a textured quad grid for each object in the linked list. */
s32 func_80024D58(void *node) {
    Frame frame;
    void *object;
    u8 *source_points;
    u8 *grid_row;
    s32 ring_x;
    void **render_context;
    s32 grid_origin;
    u8 *rotated_points;
    u8 *grid;
    u32 address_mask;
    s32 point_index;
    s32 ring;
    s32 side;
    s32 span_base;
    u8 *ring_params;
    u16 point_count;
    s32 edge_base;

    source_points = frame.space;
    rotated_points = frame.space + 128;
    grid = frame.space + 256;
    render_context = &gameWork.unk_000;
    grid_origin = -720;
    for (;;) {
        object = node;
        {
            s16 point_y = grid_origin + 1440;
            u8 *source_point = source_points + 120;
            point_index = 15;
            do {
                ((S_80024D58_Point *)source_point)->unk_02 = point_y;
                point_y -= 96;
                point_index -= 1;
                source_point -= 8;
            } while (point_index >= 0);
        }
        ring = 7;
        frame.p.f51A = 0;
        frame.p.f518 = 0;
        frame.p.blk = *(Blk8 *)((u8 *)object + 4);
        grid_row = grid + 0x1C0;
        span_base = 0xE;
        frame.p.f52A = 0;
        ring_params = (u8 *)object + 0x2A;
        do {
            s32 point_offset = ring * 8;
            s32 half_count = 8 - ring;
            u8 *ring_points = source_points + point_offset;
            ring_x = grid_origin + span_base * 48;
            frame.p.f51C = ((S_80024D58_RingParam *)ring_params)->unk_12;
            frame.p.f510 = ring_points;
            frame.p.f514 = rotated_points + point_offset;
            frame.p.f528 = half_count * 2;
            {
                s32 height = ((S_80024D58_Obj *)object)->unk_04;
                *(s16 *)frame.space = (height + ring) << 6;
            }
            point_index = ring;
            if (point_index < (point_index + (s16) (half_count * 2))) {
                s32 point_x = ring_x;
                u8 *params = ring_params;
                u8 *point = ring_points;
                do {
                    ((S_80024D58_Point *)point)->unk_00 = (s16) point_x;
                    point_index += 1;
                    ((S_80024D58_Point *)point)->unk_04 = ((S_80024D58_RingParam *)params)->unk_10;
                    point += 8;
                } while (point_index < (ring + frame.p.f528));
            }
            side = 0;
            do {
                func_800DBA90(&frame.p.f510);
                switch (side) {
                case 0:
                    point_index = ring;
                    if (point_index < (ring + frame.p.f528)) {
                        s32 offset;
                        u8 *grid_point;
                        u8 *rotated_point;
                        offset = point_index * 4;
                        grid_point = (u8 *) (offset + (s32) grid_row);
                        offset = point_index * 8;
                        rotated_point = (u8 *) (offset + (s32) rotated_points);
                        do {
                            func_80065420(rotated_point, grid_point, &frame.p.f530, &frame.p.f534);
                            grid_point += 4;
                            rotated_point += 8;
                            point_index += 1;
                        } while (point_index < (ring + frame.p.f528));
                    }
                    break;
                case 1:
                    point_index = ring;
                    point_count = frame.p.f528;
                    if (point_index < (point_index + frame.p.f528)) {
                        edge_base = span_base;
                        do {
                            s32 next_index;
                            ring_points = grid_cell(grid, (edge_base + (s16) point_count) - (next_index = point_index + 1), ring);
                            func_80065420(rotated_points + point_index * 8, ring_points,
                                          &frame.p.f530, &frame.p.f534);
                            point_index = next_index;
                            point_count = frame.p.f528;
                        } while (point_index < (ring + frame.p.f528));
                    }
                    break;
                case 2:
                    point_index = ring;
                    point_count = frame.p.f528;
                    if (point_index < (point_index + frame.p.f528)) {
                        do {
                            s32 next_index;
                            func_80065420(rotated_points + point_index * 8,
                                          grid + (((ring + (s16) point_count) << 6) - 0x40)
                                          + (((span_base + (s16) point_count)
                                              - (next_index = point_index + 1)) * 4),
                                          &frame.p.f530, &frame.p.f534);
                            point_index = next_index;
                            point_count = frame.p.f528;
                        } while (point_index < (ring + frame.p.f528));
                    }
                    break;
                case 3:
                    point_index = ring;
                    point_count = frame.p.f528;
                    if (point_index < (point_index + frame.p.f528)) {
                        u8 *grid_row = (u8 *) ((point_index << 6) + (s32) grid);
                        u8 *rotated_point = (u8 *) ((point_index * 8) + (s32) rotated_points);
                        do {
                            func_80065420(rotated_point, grid_row + (((ring + (s16) point_count) * 4) - 4),
                                          &frame.p.f530, &frame.p.f534);
                            grid_row += 0x40;
                            point_index += 1;
                            point_count = frame.p.f528;
                            rotated_point += 8;
                        } while (point_index < (ring + frame.p.f528));
                    }
                    break;
                }
                side += 1;
                frame.p.f51C += 0x400;
            } while (side < 4);
            grid_row -= 0x40;
            span_base -= 2;
            ring_params -= 6;
            ring -= 1;
        } while (ring >= 0);
        {
            s32 tag_mask;

            side = 0;
            address_mask = 0xFFFFFF;
            tag_mask = (s32) 0xFF000000;
            do {
                point_index = 0;
                ring = side * 4;
                do {
                    {
                        void *context = *render_context;
                        u8 *quad = ((GpuContext *)context)->packetCursor;
                        u8 *top_pair;
                        u8 *bottom_pair;
                        u8 *src_base;
                        u8 *src_row;
                        u8 *src_pair;
                        u8 *dst_row;
                        u8 *dst_pair;
                        s32 row_offset;
                        ((GpuContext *)context)->packetCursor = quad + 0x28;
                        ((PolyFT4 *)quad)->colorCode = ((S_80024D58_Obj *)object)->unk_0C;
                        func_800666F4(quad);
                        func_80066640(quad, 1);
                        ((PolyFT4 *)quad)->tpage = func_80066460(0, 3, 0x300, 0x100);
                        ((PolyFT4 *)quad)->clut = func_8006649C(0x10, 0x1F8);
                        row_offset = point_index << 6;
                        src_base = (u8 *) (row_offset + (s32) source_points);
                        src_row = src_base + 0x100;
                        src_pair = (u8 *) (ring + (s32) src_row);
                        ((PolyFT4 *)quad)->xy0 = ((S_80024D58_Pair *)src_pair)->unk_00;
                        ((PolyFT4 *)quad)->xy1 = ((S_80024D58_Pair *)src_pair)->unk_04;
                        top_pair = frame.space + 320;
                        dst_row = top_pair + row_offset;
                        dst_pair = (u8 *) (ring + (s32) dst_row);
                        ((PolyFT4 *)quad)->xy2 = ((S_80024D58_Pair *)dst_pair)->unk_00;
                        {
                            s32 bottom_right = ((S_80024D58_Pair *)dst_pair)->unk_04;
                            ((PolyFT4 *)quad)->u1 = 0xC0;
                            ((PolyFT4 *)quad)->u0 = 0xC0;
                            ((PolyFT4 *)quad)->u3 = 0xDF;
                            ((PolyFT4 *)quad)->u2 = 0xDF;
                            ((PolyFT4 *)quad)->v2 = 0;
                            ((PolyFT4 *)quad)->v0 = 0;
                            ((PolyFT4 *)quad)->v3 = 0x1F;
                            ((PolyFT4 *)quad)->v1 = 0x1F;
                            ((PolyFT4 *)quad)->xy3 = bottom_right;
                        }
                        bottom_pair = (u8 *)((((PolyFT4 *)quad)->tag & tag_mask)
                            | (((GpuContext *)(*render_context))->orderTag & address_mask));
                        (*(s32 *)quad) = (s32)bottom_pair;
                        point_index += 1;
                        ((GpuContext *)(*render_context))->orderTag =
                            (((GpuContext *)(*render_context))->orderTag & tag_mask) | ((s32) quad & address_mask);
                    }
                } while (point_index < 0xF);
                side += 1;
            } while (side < 0xF);
        }
        {
            void *next_node = ((S_80024D58_11_pre *)node)[-1].unk_00;
            if (next_node != 0) {
                node = (u8 *) next_node + 0x20;
                continue;
            }
        }
        break;
    }
    return 0;
}
