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

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    desc.angle = FIELD(arg0, u16, 0x10) - 0x400;
    input = arg0;
    ASM_KEEP(input);
    desc.value = func_80065F90(FIELD(arg0, s16, 0x12), 0x40);
    row = 0;
    ASM_SCHED_BARRIER();
    col = 7;
grid_loop:
    {
        GridPoint *point;
        s32 height;
        s32 angle;
        s32 point_index;

        height = row * ((8 - FIELD(input, s16, 0xE)) << 4);
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
            index = ((s16)FIELD(depth_base1, s16, 0) +
                     (s16)FIELD(depth_base1, s16, -0x10)) >> 3;
            if ((u32)index < 0x1E0) {
                state = *(u8 * volatile *)global;
                line = FIELD(state, LineG2 *, 0x8D0);
                FIELD(state, u8 *, 0x8D0) = (u8 *)line + 0x14;

                state = *(u8 * volatile *)global;
                tpage = FIELD(state, u8 *, 0x8D0);
                FIELD(state, u8 *, 0x8D0) = tpage + 0x0C;

                func_80067F20(tpage, 0, 0,
                              func_80066460(0, 1, 0, 0), 0);

                line->color0 = FIELD(input, u32, 8);
                line->color1 = FIELD(input, u32, 8);
                func_800667D0(line);
                func_80066640(line, 1);

                line->xy0 = FIELD(xy, u32, 0);
                line->xy1 = FIELD(xy, u32, -0x20);

                line->tag = (line->tag & 0xFF000000) |
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & mask);
                FIELD(ROOT, u32, 0xB0 + index * 4) =
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & 0xFF000000) |
                    ((u32)line & mask);

                FIELD(tpage, u32, 0) = (FIELD(tpage, u32, 0) & 0xFF000000) |
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & mask);
                FIELD(ROOT, u32, 0xB0 + index * 4) =
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & 0xFF000000) |
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
            index = ((s16)FIELD(xy3, s16, 0) +
                     FIELD(depth_base, s16, next * 2)) >> 3;
            if ((u32)index < 0x1E0) {
                state = *(u8 * volatile *)global;
                line = FIELD(state, LineG2 *, 0x8D0);
                FIELD(state, u8 *, 0x8D0) = (u8 *)line + 0x14;

                state = *(u8 * volatile *)global;
                tpage = FIELD(state, u8 *, 0x8D0);
                FIELD(state, u8 *, 0x8D0) = tpage + 0x0C;

                func_80067F20(tpage, 0, 0,
                              func_80066460(0, 1, 0, 0), 0);

                line->color0 = FIELD(input, u32, 8);
                line->color1 = FIELD(input, u32, 8);
                func_800667D0(line);
                func_80066640(line, 1);

                line->xy0 = FIELD(depth, u32, 0);
                line->xy1 = FIELD(xy_base, u32, next * 4);

                line->tag = (line->tag & 0xFF000000) |
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & mask);
                FIELD(ROOT, u32, 0xB0 + index * 4) =
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & 0xFF000000) |
                    ((u32)line & mask);

                FIELD(tpage, u32, 0) = (FIELD(tpage, u32, 0) & 0xFF000000) |
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & mask);
                FIELD(ROOT, u32, 0xB0 + index * 4) =
                    (FIELD(ROOT, u32, 0xB0 + index * 4) & 0xFF000000) |
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
        register u8 *tail ASM_REG("$5");

        tail = FIELD(arg0, u8 *, -8);
        if (tail == 0) {
            break;
        }
        arg0 = tail + 0x20;
        tail = FIELD(tail, u8 *, 8);
        ASM_KEEP(tail);
    }

    }
    return 0;
}
