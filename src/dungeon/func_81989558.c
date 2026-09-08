#include "common.h"

typedef struct S_80024D58_0 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80024D58_0;   /* q in func_80024D58 */

typedef struct S_80024D58_1 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80024D58_1;   /* var_fp in func_80024D58 */

typedef struct S_80024D58_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    s32 unk_0C;
} S_80024D58_2;   /* obj in func_80024D58 */

typedef struct S_80024D58_3 {
    s16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_80024D58_3;   /* w in func_80024D58 */

typedef struct S_80024D58_4 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024D58_4;   /* fq in func_80024D58 */

typedef struct S_80024D58_5 {
    u8 pad_00[0x18];
    u16 unk_18;
} S_80024D58_5;   /* &frame.p in func_80024D58 */

typedef struct S_80024D58_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80024D58_6;   /* ctx in func_80024D58 */

typedef struct S_80024D58_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    s32 unk_10;
    u8 unk_14;
    u8 unk_15;
    s16 unk_16;
    s32 unk_18;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[0x2];
    s32 unk_20;
    u8 unk_24;
    u8 unk_25;
} S_80024D58_7;   /* o in func_80024D58 */

typedef struct S_80024D58_8 {
    s32 unk_00;
    s32 unk_04;
} S_80024D58_8;   /* r1 in func_80024D58 */

typedef struct S_80024D58_9 {
    s32 unk_00;
    s32 unk_04;
} S_80024D58_9;   /* r1b in func_80024D58 */

typedef struct S_80024D58_10 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80024D58_10;   /* *gp0 in func_80024D58 */

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

extern void func_800DBA90();
extern void func_80065420();
extern void func_800666F4();
extern void func_80066640();
extern s16 func_80066460();
extern s16 func_8006649C();
extern void *D_80083160[3];

/* Build a textured quad grid for each object in the linked list. */
s32 func_80024D58(void *node) {
    Frame frame;
    void *object;
    u8 *source_points;
    u8 *grid_row;
    s32 ring_x;
    void **render_context;
    s32 grid_origin;
    register u8 *rotated_points ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
    render_context = &D_80083160[0];
    grid_origin = -720;
next_object:
    object = node;
    {
        s16 point_y = grid_origin + 1440;
        u8 *source_point = source_points + 120;
        point_index = 15;
        do {
            ((S_80024D58_0 *)source_point)->unk_02 = point_y;
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
    ASM_KEEP_NV(ring_params);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ring_x = grid_origin + 672;
    do {
        s32 point_offset = ring * 8;
        s32 half_count = 8 - ring;
        u8 *ring_points = source_points + point_offset;
        ASM_KEEP_NV(ring_points);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        frame.p.f51C = ((S_80024D58_1 *)ring_params)->unk_12;
        frame.p.f514 = rotated_points + point_offset;
        frame.p.f510 = ring_points;
        frame.p.f528 = half_count * 2;
        {
            s32 height = ((S_80024D58_2 *)object)->unk_04;
            *(s16 *)frame.space = (height + ring) << 6;
        }
        point_index = ring;
        if (point_index < (point_index + (s16) (half_count * 2))) {
            s32 point_x = ring_x;
            u8 *params = ring_params;
            u8 *point = ring_points;
            do {
                ((S_80024D58_3 *)point)->unk_00 = (s16) point_x;
                point_index += 1;
                ((S_80024D58_3 *)point)->unk_04 = ((S_80024D58_4 *)params)->unk_10;
                point += 8;
            } while (point_index < (ring + frame.p.f528));
        }
        side = 0;
next_side:
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
            point_count = ((S_80024D58_5 *)(&frame.p))->unk_18;
            if (point_index < (point_index + frame.p.f528)) {
                edge_base = span_base;
                do {
                    s32 next_index;
                    func_80065420(rotated_points + point_index * 8,
                                  grid + (((edge_base + (s16) point_count) - (next_index = point_index + 1)) << 6) + (ring * 4),
                                  &frame.p.f530, &frame.p.f534);
                    point_index = next_index;
                    ASM_KEEP_NV(ring);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    ASM_USE2_NV(grid, grid);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    point_count = ((S_80024D58_5 *)(&frame.p))->unk_18;
                } while (point_index < (ring + frame.p.f528));
            }
            break;
        case 2:
            point_index = ring;
            point_count = ((S_80024D58_5 *)(&frame.p))->unk_18;
            if (point_index < (point_index + frame.p.f528)) {
                do {
                    s32 next_index;
                    func_80065420(rotated_points + point_index * 8,
                                  grid + (((ring + (s16) point_count) << 6) - 0x40) + (((span_base + (s16) point_count) - (next_index = point_index + 1)) * 4),
                                  &frame.p.f530, &frame.p.f534);
                    point_index = next_index;
                    point_count = ((S_80024D58_5 *)(&frame.p))->unk_18;
                } while (point_index < (ring + frame.p.f528));
            }
            break;
        case 3:
            point_index = ring;
            point_count = ((S_80024D58_5 *)(&frame.p))->unk_18;
            if (point_index < (point_index + frame.p.f528)) {
                u8 *grid_row = (u8 *) ((point_index << 6) + (s32) grid);
                u8 *rotated_point = (u8 *) ((point_index * 8) + (s32) rotated_points);
                do {
                    func_80065420(rotated_point, grid_row + (((ring + (s16) point_count) * 4) - 4),
                                  &frame.p.f530, &frame.p.f534);
                    grid_row += 0x40;
                    point_index += 1;
                    point_count = ((S_80024D58_5 *)(&frame.p))->unk_18;
                    rotated_point += 8;
                } while (point_index < (ring + frame.p.f528));
            }
            break;
        }
        side += 1;
        frame.p.f51C += 0x400;
        if (side < 4) {
            goto next_side;
        }
        span_base -= 2;
        ASM_USE2_NV(span_base, span_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ring_params -= 6;
        grid_row -= 0x40;
        ring -= 1;
        ring_x -= 0x60;
    } while (ring >= 0);
    {
        s32 tag_mask;

        side = 0;
        address_mask = 0xFFFFFF;
        tag_mask = (s32) 0xFF000000;
        do {
            point_index = 0;
            ring = side * 4;
next_quad:
            {
                void *context = *render_context;
                u8 *quad = ((S_80024D58_6 *)context)->unk_8D0;
                u8 *top_pair;
                u8 *bottom_pair;
                register s32 row_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ((S_80024D58_6 *)context)->unk_8D0 = quad + 0x28;
                ((S_80024D58_7 *)quad)->unk_04 = ((S_80024D58_2 *)object)->unk_0C;
                func_800666F4(quad);
                func_80066640(quad, 1);
                ((S_80024D58_7 *)quad)->unk_16 = func_80066460(0, 3, 0x300, 0x100);
                ((S_80024D58_7 *)quad)->unk_0E = func_8006649C(0x10, 0x1F8);
                ASM_USE(quad);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                row_offset = point_index << 6;
                bottom_pair = (u8 *) (row_offset + (s32) source_points);
                bottom_pair = bottom_pair + 0x100;
                top_pair = (u8 *) (ring + (s32) bottom_pair);
                ((S_80024D58_7 *)quad)->unk_08 = ((S_80024D58_8 *)top_pair)->unk_00;
                ((S_80024D58_7 *)quad)->unk_10 = ((S_80024D58_8 *)top_pair)->unk_04;
                top_pair = frame.space + 320;
                top_pair = top_pair + row_offset;
                bottom_pair = (u8 *) (ring + (s32) top_pair);
                ((S_80024D58_7 *)quad)->unk_18 = ((S_80024D58_9 *)bottom_pair)->unk_00;
                {
                    s32 bottom_right = ((S_80024D58_9 *)bottom_pair)->unk_04;
                    ((S_80024D58_7 *)quad)->unk_14 = 0xC0;
                    ((S_80024D58_7 *)quad)->unk_0C = 0xC0;
                    ((S_80024D58_7 *)quad)->unk_24 = 0xDF;
                    ((S_80024D58_7 *)quad)->unk_1C = 0xDF;
                    ((S_80024D58_7 *)quad)->unk_1D = 0;
                    ((S_80024D58_7 *)quad)->unk_0D = 0;
                    ((S_80024D58_7 *)quad)->unk_25 = 0x1F;
                    ((S_80024D58_7 *)quad)->unk_15 = 0x1F;
                    ((S_80024D58_7 *)quad)->unk_20 = bottom_right;
                }
                (*(s32 *)((u8 *)quad + 0)) = (((S_80024D58_7 *)quad)->unk_00 & tag_mask) | (((S_80024D58_10 *)(*render_context))->unk_B0 & address_mask);
                point_index += 1;
                ((S_80024D58_10 *)(*render_context))->unk_B0 = (((S_80024D58_10 *)(*render_context))->unk_B0 & tag_mask) | ((s32) quad & address_mask);
            }
            if (point_index < 0xF) {
                goto next_quad;
            }
            side += 1;
        } while (side < 0xF);
    }
    {
        void *next_node = ((S_80024D58_11_pre *)node)[-1].unk_00;
        if (next_node != 0) {
            node = (u8 *) next_node + 0x20;
            goto next_object;
        }
    }
    return 0;
}
