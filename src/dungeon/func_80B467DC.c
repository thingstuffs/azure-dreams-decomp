#include "common.h"

typedef struct {
    u8 bytes[8];
} Header8;

typedef struct {
    s16 x;
    u16 y;
    s16 z;
    s16 pad;
} GridPoint;

typedef struct {
    GridPoint *points0;
    GridPoint *points1;
    s16 value;
    s16 zero;
    s16 angle;
    s16 pad0E;
    Header8 header;
    s16 count;
    s16 one;
    s32 pad1C;
} WorkDesc;

typedef struct {
    WorkDesc desc;
    GridPoint points[8][8];
} Frame;

typedef struct {
    u8 *ptr;
} RootSlot;

typedef struct {
    u32 tag;
    u32 color0;
    u32 xy0;
    u32 color1;
    u32 xy1;
} LineG2;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80065770(void *, void *, void *, void *, void *, s32);
extern s16 func_80065F90(s32, s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_800667D0(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern void func_800DBA90(void *);
extern u8 D_80083160[];

#define desc       (frame.desc)
#define points     (frame.points)
#define ROOT       (((RootSlot *)display_root)->ptr)


typedef struct S_80173FDC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_80173FDC_0_pre;   /* the 0x8 bytes before arg0 in func_80173FDC, addressed as arg0[-1] */

typedef struct S_80173FDC_0 {
    u8 pad_00[0x10];
    u16 unk_10;
    s16 unk_12;
} S_80173FDC_0;   /* arg0 in func_80173FDC */

typedef struct S_80173FDC_1 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x2];
    s16 unk_0E;
} S_80173FDC_1;   /* input in func_80173FDC */

typedef struct S_80173FDC_2_pre {
    s16 unk_00;
    u8 pad_02[0xE];
} S_80173FDC_2_pre;   /* the 0x10 bytes before depth_base1 in func_80173FDC, addressed as depth_base1[-1] */

typedef struct S_80173FDC_2 {
    s16 unk_00;
} S_80173FDC_2;   /* depth_base1 in func_80173FDC */

typedef struct S_80173FDC_3 {
    u8 pad_00[0x8D0];
    union { LineG2 * p; u8 * p2; } unk_8D0;   /* accessed as both */
} S_80173FDC_3;   /* state in func_80173FDC */

typedef struct S_80173FDC_4_pre {
    u32 unk_00;
    u8 pad_04[0x1C];
} S_80173FDC_4_pre;   /* the 0x20 bytes before xy in func_80173FDC, addressed as xy[-1] */

typedef struct S_80173FDC_4 {
    u32 unk_00;
} S_80173FDC_4;   /* xy in func_80173FDC */

typedef struct S_80173FDC_5 {
    u32 unk_00;
} S_80173FDC_5;   /* tpage in func_80173FDC */

typedef struct S_80173FDC_6 {
    s16 unk_00;
} S_80173FDC_6;   /* xy3 in func_80173FDC */

typedef struct S_80173FDC_7 {
    u32 unk_00;
} S_80173FDC_7;   /* depth in func_80173FDC */

typedef struct S_80173FDC_8 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_80173FDC_8;   /* tail in func_80173FDC */

/* Builds and draws a curved wireframe grid for each linked effect. */
s32 func_80173FDC(u8 *node)
{
    Frame frame;
    u8 *effect;
    u8 *vertex_depths;
    u8 *transform_work;
    u8 *depth_base;
    u8 *xy_base;
    u8 *xy_row;
    u8 *ring_depth_row;
    u8 *vertical_xy_row;
    u8 *screen_xy;
    GridPoint *point_base;
    u8 *vertical_depth_row;
    u8 *ring_xy;
    LineG2 *line;
    u8 *tpage;
    u8 *display;
    s32 row;
    s32 col;
    s32 ot_index;
    s32 sin_angle;
    s32 cos_angle;
    s32 addr_mask;
    u8 **display_root = (u8 **)D_80083160;

    screen_xy = (u8 *)0x1F800000;
    vertex_depths = (u8 *)0x1F800100;
    transform_work = (u8 *)0x1F800180;
    addr_mask = 0x00FFFFFF;

    for (;;) {
        desc.points0 = &points[0][0];
        desc.points1 = &points[0][0];
        desc.zero = 0;
        desc.angle = ((S_80173FDC_0 *)node)->unk_10 - 0x400;
        effect = node;
        ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        desc.value = func_80065F90(((S_80173FDC_0 *)node)->unk_12, 0x40);
        row = 0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        col = 7;
    grid_loop:
        {
            GridPoint *point;
            s32 height;
            s32 angle;
            s32 point_offset;

            height = row * ((8 - ((S_80173FDC_1 *)effect)->unk_0E) << 4);
            point_base = &points[0][0];
            point_offset = col << 3;
            point_offset += row << 6;
            point = (GridPoint *)((u8 *)point_base + point_offset);

            if (height < 0) {
                height += 7;
            }
            point->y = height >> 3;
            angle = col << 9;
            sin_angle = func_800644B8(angle);
            point->x = (sin_angle * func_800644B8(
                ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
            cos_angle = func_80064584(angle);
            point->z = (cos_angle * func_800644B8(
                ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
        }
        col--;
        if (col >= 0) {
            goto grid_loop;
        }
        row++;
        if (row < 8) {
            col = 7;
            goto grid_loop;
        }

        desc.count = 0x40;
        desc.header = *(Header8 *)effect;
        desc.one = 1;
        func_800DBA90(&desc);

        {
            u8 *vertex_depth;
            u8 *xy;

            func_80065770(points, screen_xy, vertex_depths, transform_work, transform_work, desc.count);
            row = 0x38;
            vertical_xy_row = screen_xy + 0xE0;
            vertical_depth_row = vertex_depths + 0x70;
            while (row > 0) {
                col = 7;
                xy = vertical_xy_row + 0x1C;
                vertex_depth = vertical_depth_row + 0x0E;
                while (col >= 0) {
                    ot_index = ((s16)((S_80173FDC_2 *)vertex_depth)->unk_00 +
                        (s16)((S_80173FDC_2_pre *)vertex_depth)[-1].unk_00) >> 3;
                    if ((u32)ot_index < 0x1E0) {
                        display = *(u8 * volatile *)display_root;
                        line = ((S_80173FDC_3 *)display)->unk_8D0.p;
                        ((S_80173FDC_3 *)display)->unk_8D0.p2 = (u8 *)line + 0x14;

                        display = *(u8 * volatile *)display_root;
                        tpage = ((S_80173FDC_3 *)display)->unk_8D0.p2;
                        ((S_80173FDC_3 *)display)->unk_8D0.p2 = tpage + 0x0C;

                        func_80067F20(tpage, 0, 0,
                            func_80066460(0, 1, 0, 0), 0);

                        line->color0 = ((S_80173FDC_1 *)effect)->unk_08;
                        line->color1 = ((S_80173FDC_1 *)effect)->unk_08;
                        func_800667D0(line);
                        func_80066640(line, 1);

                        line->xy0 = ((S_80173FDC_4 *)xy)->unk_00;
                        line->xy1 = ((S_80173FDC_4_pre *)xy)[-1].unk_00;

                        line->tag = (line->tag & 0xFF000000) |
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)line & addr_mask);

                        ((S_80173FDC_5 *)tpage)->unk_00 = (((S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)tpage & addr_mask);
                    }
                    xy -= 4;
                    vertex_depth -= 2;
                    col--;
                }
                vertical_depth_row -= 0x10;
                vertical_xy_row -= 0x20;
                row -= 8;
            }
        }

        {
            u8 *ring_depth;

            row = 0x30;
            xy_row = screen_xy + 0xC0;
            ring_depth_row = vertex_depths + 0x60;
            while (row > 0) {
                depth_base = ring_depth_row;
                ring_xy = xy_row + 0x1C;
                xy_base = xy_row;
                col = 7;
                ring_depth = ring_depth_row + 0x0E;
                while (col >= 0) {
                    s32 next_col = (col + 1) & 7;
                    ot_index = ((s16)((S_80173FDC_6 *)ring_depth)->unk_00 +
                        (*(s16 *)((u8 *)depth_base + next_col * 2))) >> 3;
                    if ((u32)ot_index < 0x1E0) {
                        display = *(u8 * volatile *)display_root;
                        line = ((S_80173FDC_3 *)display)->unk_8D0.p;
                        ((S_80173FDC_3 *)display)->unk_8D0.p2 = (u8 *)line + 0x14;

                        display = *(u8 * volatile *)display_root;
                        tpage = ((S_80173FDC_3 *)display)->unk_8D0.p2;
                        ((S_80173FDC_3 *)display)->unk_8D0.p2 = tpage + 0x0C;

                        func_80067F20(tpage, 0, 0,
                            func_80066460(0, 1, 0, 0), 0);

                        line->color0 = ((S_80173FDC_1 *)effect)->unk_08;
                        line->color1 = ((S_80173FDC_1 *)effect)->unk_08;
                        func_800667D0(line);
                        func_80066640(line, 1);

                        line->xy0 = ((S_80173FDC_7 *)ring_xy)->unk_00;
                        line->xy1 = (*(u32 *)((u8 *)xy_base + next_col * 4));

                        line->tag = (line->tag & 0xFF000000) |
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)line & addr_mask);

                        ((S_80173FDC_5 *)tpage)->unk_00 = (((S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)ROOT + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)tpage & addr_mask);
                    }
                    ring_xy -= 4;
                    ring_depth -= 2;
                    col--;
                }
                xy_row -= 0x20;
                ring_depth_row -= 0x10;
                row -= 8;
            }
        }

        {
            register u8 *next_node ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            next_node = ((S_80173FDC_0_pre *)node)[-1].unk_00;
            if (next_node == 0) {
                break;
            }
            node = next_node + 0x20;
            next_node = ((S_80173FDC_8 *)next_node)->unk_08;
            ASM_KEEP(next_node);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        }
    }
    return 0;
}
