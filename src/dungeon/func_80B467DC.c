#include "common.h"

/* Row row-0x80B467DC -- DUNGEON, true base 0x80173FDC, 1456 B; byte-exact @2.7.2-cdk-G0.
 *
 * Two shape facts carry this row (see close_80B467DC_2/REPORT.md):
 *  1. The four tag-splice reads of the display root go through a STRUCT member
 *     (RootSlot::ptr).  gcc-2.7.2 sched.c true_dependence() (:836-861) lets a
 *     MEM_IN_STRUCT store at a varying address float past a NON-struct read at a
 *     fixed (canonicalised symbol) address, so with a plain `*(u8 **)D_80083160`
 *     read each `lui %hi` / `addiu %lo` / `lw` group is either glued below the
 *     preceding `sw line->tag` (with a scheduling fence) or hoisted whole above
 *     it (without one).  Making the read a struct member restores the real
 *     store->load dependence: the page halves float up, the dereference stays
 *     put -- exactly retail's interleave.  No fence is needed at that point.
 *  2. `scratch0` is set up once with the other scratch pointers, OUTSIDE the
 *     outer list loop.  Inside the loop cse cannot see the constant, so
 *     `xy_row2 = scratch0 + 0xE0` stays a PLUS (`addiu t0,t0,224`); assigned
 *     inside the loop it folds to the literal 0x1F8000E0 and is materialised as
 *     `lui`+`ori` instead.
 *
 * `j 0x8017402C` at retail word 348 is offset 0x50 of this row -- a local
 * backward jump, i.e. the outer `for (;;)` back-edge, NOT a noreturn tail call.
 */


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
#define ROOT       (((RootSlot *)global)->ptr)


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

s32 func_80173FDC(u8 *arg0)
{
    Frame frame;
    u8 *input;
    u8 *scratch100;
    u8 *scratch180;
    u8 *depth_base;
    u8 *xy_base;
    u8 *xy_row;
    u8 *dep_row;
    u8 *xy_row2;
    u8 *scratch0;
    GridPoint *point_base;
    u8 *depth;
    LineG2 *line;
    u8 *tpage;
    u8 *state;
    s32 row;
    s32 col;
    s32 index;
    s32 trig;
    s32 trig2;
    s32 mask;
    u8 **global = (u8 **)D_80083160;

    scratch0 = (u8 *)0x1F800000;
    scratch100 = (u8 *)0x1F800100;
    scratch180 = (u8 *)0x1F800180;
    mask = 0x00FFFFFF;

    for (;;) {

    desc.points0 = &points[0][0];
    desc.points1 = &points[0][0];
    desc.zero = 0;
    desc.angle = ((S_80173FDC_0 *)arg0)->unk_10 - 0x400;
    input = arg0;
    ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    desc.value = func_80065F90(((S_80173FDC_0 *)arg0)->unk_12, 0x40);
    row = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    col = 7;
grid_loop:
    {
        GridPoint *point;
        s32 height;
        s32 angle;
        s32 point_index;

        height = row * ((8 - ((S_80173FDC_1 *)input)->unk_0E) << 4);
        point_base = &points[0][0];
        point_index = col << 3;
        point_index += row << 6;
        point = (GridPoint *)((u8 *)point_base + point_index);

        if (height < 0) {
            height += 7;
        }
        point->y = height >> 3;
        angle = col << 9;
        trig = func_800644B8(angle);
        point->x = (trig * func_800644B8(
            ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
        trig2 = func_80064584(angle);
        point->z = (trig2 * func_800644B8(
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
    desc.header = *(Header8 *)input;
    desc.one = 1;
    func_800DBA90(&desc);

    {
    u8 *depth_base1;
    u8 *xy;
    func_80065770(points, scratch0, scratch100, scratch180, scratch180, desc.count);
    row = 0x38;
    xy_row2 = scratch0 + 0xE0;
    depth = scratch100 + 0x70;
    while (row > 0) {
        col = 7;
        xy = xy_row2 + 0x1C;
        depth_base1 = depth + 0x0E;
        while (col >= 0) {
            index = ((s16)((S_80173FDC_2 *)depth_base1)->unk_00 +
                     (s16)((S_80173FDC_2_pre *)depth_base1)[-1].unk_00) >> 3;
            if ((u32)index < 0x1E0) {
                state = *(u8 * volatile *)global;
                line = ((S_80173FDC_3 *)state)->unk_8D0.p;
                ((S_80173FDC_3 *)state)->unk_8D0.p2 = (u8 *)line + 0x14;

                state = *(u8 * volatile *)global;
                tpage = ((S_80173FDC_3 *)state)->unk_8D0.p2;
                ((S_80173FDC_3 *)state)->unk_8D0.p2 = tpage + 0x0C;

                func_80067F20(tpage, 0, 0,
                              func_80066460(0, 1, 0, 0), 0);

                line->color0 = ((S_80173FDC_1 *)input)->unk_08;
                line->color1 = ((S_80173FDC_1 *)input)->unk_08;
                func_800667D0(line);
                func_80066640(line, 1);

                line->xy0 = ((S_80173FDC_4 *)xy)->unk_00;
                line->xy1 = ((S_80173FDC_4_pre *)xy)[-1].unk_00;

                line->tag = (line->tag & 0xFF000000) |
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & mask);
                (*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) =
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & 0xFF000000) |
                    ((u32)line & mask);

                ((S_80173FDC_5 *)tpage)->unk_00 = (((S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & mask);
                (*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) =
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & 0xFF000000) |
                    ((u32)tpage & mask);
            }
            xy -= 4;
            depth_base1 -= 2;
            col--;
        }
        depth -= 0x10;
        xy_row2 -= 0x20;
        row -= 8;
    }
    }

    {
    s32 next2;
    u8 *xy3;
    row = 0x30;
    xy_row = scratch0 + 0xC0;
    dep_row = scratch100 + 0x60;
    while (row > 0) {
        depth_base = dep_row;
        depth = xy_row + 0x1C;
        xy_base = xy_row;
        col = 7;
        xy3 = dep_row + 0x0E;
        while (col >= 0) {
            s32 next = (col + 1) & 7;
            index = ((s16)((S_80173FDC_6 *)xy3)->unk_00 +
                     (*(s16 *)((u8 *)depth_base + next * 2))) >> 3;
            if ((u32)index < 0x1E0) {
                state = *(u8 * volatile *)global;
                line = ((S_80173FDC_3 *)state)->unk_8D0.p;
                ((S_80173FDC_3 *)state)->unk_8D0.p2 = (u8 *)line + 0x14;

                state = *(u8 * volatile *)global;
                tpage = ((S_80173FDC_3 *)state)->unk_8D0.p2;
                ((S_80173FDC_3 *)state)->unk_8D0.p2 = tpage + 0x0C;

                func_80067F20(tpage, 0, 0,
                              func_80066460(0, 1, 0, 0), 0);

                line->color0 = ((S_80173FDC_1 *)input)->unk_08;
                line->color1 = ((S_80173FDC_1 *)input)->unk_08;
                func_800667D0(line);
                func_80066640(line, 1);

                line->xy0 = ((S_80173FDC_7 *)depth)->unk_00;
                line->xy1 = (*(u32 *)((u8 *)xy_base + next * 4));

                line->tag = (line->tag & 0xFF000000) |
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & mask);
                (*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) =
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & 0xFF000000) |
                    ((u32)line & mask);

                ((S_80173FDC_5 *)tpage)->unk_00 = (((S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & mask);
                (*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) =
                    ((*(u32 *)((u8 *)ROOT + 0xB0 + index * 4)) & 0xFF000000) |
                    ((u32)tpage & mask);
            }
            depth -= 4;
            xy3 -= 2;
            col--;
        }
        xy_row -= 0x20;
        dep_row -= 0x10;
        row -= 8;
    }
    }

    {
        register u8 *tail ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        tail = ((S_80173FDC_0_pre *)arg0)[-1].unk_00;
        if (tail == 0) {
            break;
        }
        arg0 = tail + 0x20;
        tail = ((S_80173FDC_8 *)tail)->unk_08;
        ASM_KEEP(tail);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }

    }
    return 0;
}
