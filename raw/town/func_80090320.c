#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Scratch80090320 {
    u8 pad00[4]; u16 tile; u8 pad06[0x12]; u8 *height_data;
    s16 result; u16 origin_y; u16 origin_z; u8 pad22[0xE];
    s32 best; s32 lower_bound; s32 block_base; u8 pad3C[0xC];
    u16 inner_index; u8 pad4A[4]; u16 saved_y; u16 start_x; u16 start_y;
    s32 x_step; s32 y_step; s32 inner_count; s32 outer_count;
    s32 inner_offset; s32 outer_offset;
    s16 d0; s16 d1; s16 d2; s16 d3; s16 d4; s16 d5; s16 d6; s16 d7;
} Scratch80090320;

typedef struct Grid80090320 {
    u16 *occupancy; u8 **entries; u8 *vertices; u8 *height_data;
    u8 pad10[4]; s16 shift; u16 pad16; u16 x_mask; u16 y_mask;
} Grid80090320;

extern u8 D_80083160[];
extern s32 D_800FE480;
extern s32 D_800FE484;
extern s32 func_8008CE08();

s16 func_8008DA80(s32 arg0, s32 arg1, s32 arg2)
{
    Scratch80090320 *scratch;
    Grid80090320 *grid;
    u16 *occupancy;
    u8 *base;
    u8 *vertices;
    u8 *entry;
    u8 *plane;
    u8 *vertex;
    s16 block_base;
    s16 tile;
    s16 value;
    s16 x;
    u16 y;
    s32 ysum;
    s32 quotient;
    s16 xsum;

    x = arg0;
    y = arg1;
    scratch = (Scratch80090320 *)0x1F800000;
    scratch->best = 0x7FFF;
    block_base = arg0 & ~0x3F;
    scratch->block_base = block_base;
    scratch->lower_bound = (s16)arg0 - block_base - 0x14;
    scratch->origin_y = arg1 & 0x3F;
    scratch->origin_z = arg2;
    base = D_80083160;
    grid = (Grid80090320 *)(base + 0x1DC);
    ASM_USE(arg0);
    scratch->result = (arg0 &= 0x3F);
    scratch->saved_y = arg1 & 0x3F;
    scratch->height_data = grid->height_data;
    occupancy = FIELD(base, u16 *, 0x1DC);
    vertices = grid->vertices;
    if (arg0 >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }
    if ((s16)*(volatile u16 *)((u8 *)scratch + 0x1E) >= 0x20) {
        s32 ystep_pos = 0x40;
        scratch->y_step = ystep_pos;
    } else {
        s32 ystep_neg = -0x40;
        scratch->y_step = ystep_neg;
    }

    scratch->outer_count = 0;
    scratch->start_x = x;
    scratch->start_y = y;
    scratch->outer_offset = 0;
    while (scratch->outer_count < 2) {
        ysum = (u16)scratch->start_y + (u16)scratch->outer_offset;
        y = ysum;
        if (scratch->y_step >= 0) {
            if ((s16)ysum >= D_800FE484)
                goto outer_done;
        } else if ((s16)ysum < 0) {
            goto outer_done;
        }
        scratch->inner_count = 0;
        scratch->inner_offset = 0;
        scratch->origin_y = scratch->saved_y - (u16)scratch->outer_offset;
        while (scratch->inner_count < 2) {
            xsum = (u16)scratch->start_x + (u16)scratch->inner_offset;
            x = xsum;
            if (scratch->x_step >= 0) {
                if ((s16)xsum >= D_800FE480)
                    goto inner_done;
            } else if ((s16)xsum < 0) {
                goto inner_done;
            }

            scratch->tile = grid->x_mask &
                ((s16)x / 64);
            tile = scratch->tile +
                ((s16)(grid->y_mask & ((s16)y / 64)) << grid->shift);
            scratch->tile = tile;
            if (occupancy[tile] != 0) {
                scratch->inner_index = scratch->inner_offset;
                entry = grid->entries[occupancy[(s16)scratch->tile] & 0x3FFF];
                for (;;) {
                    if (FIELD(FIELD(entry, u16, 0x10) * 8 + scratch->height_data,
                              s16, 0) < 0 &&
                        !(FIELD(entry, u8, 0x17) & 1)) {
                        scratch->d0 = FIELD(FIELD(entry, u16, 0x00) * 8 + vertices, u16, 2) - scratch->origin_y;
                        scratch->d1 = FIELD(FIELD(entry, u16, 0x00) * 8 + vertices, u16, 4) - scratch->origin_z;
                        scratch->d2 = FIELD(FIELD(entry, u16, 0x02) * 8 + vertices, u16, 2) - scratch->origin_y;
                        scratch->d3 = FIELD(FIELD(entry, u16, 0x02) * 8 + vertices, u16, 4) - scratch->origin_z;
                        scratch->d4 = FIELD(FIELD(entry, u16, 0x06) * 8 + vertices, u16, 2) - scratch->origin_y;
                        scratch->d5 = FIELD(FIELD(entry, u16, 0x06) * 8 + vertices, u16, 4) - scratch->origin_z;
                        scratch->d6 = FIELD(FIELD(entry, u16, 0x04) * 8 + vertices, u16, 2) - scratch->origin_y;
                        scratch->d7 = FIELD(FIELD(entry, u16, 0x04) * 8 + vertices, u16, 4) - scratch->origin_z;

                        if (func_8008CE08(scratch) != 0) {
                            plane = (u8 *)(FIELD(entry, u16, 0x10) * 8 +
                                           (u32)scratch->height_data);
                            vertex = (u8 *)(FIELD(entry, u16, 0x00) * 8 +
                                            (u32)vertices);
                            quotient =
                                (FIELD(plane, s16, 2) *
                                     (FIELD(vertex, s16, 2) -
                                      (s16)*(volatile u16 *)((u8 *)scratch + 0x1E)) +
                                 FIELD(plane, s16, 4) *
                                     (FIELD(vertex, s16, 4) -
                                      (s16)*(volatile u16 *)((u8 *)scratch + 0x20)) +
                                 FIELD(plane, s16, 0) * FIELD(vertex, s16, 0)) /
                                FIELD(plane, s16, 0);
                            scratch->result = quotient;
                            quotient += scratch->inner_index;
                            scratch->result = quotient;
                            value = quotient;
                            if (value >= scratch->lower_bound && value < scratch->best)
                                scratch->best = value;
                        }
                    }
                    if ((FIELD(entry, u16, 0x16) & 0x80FF) == 0x8001)
                        break;
                    entry += 0x18;
                }
            }
            scratch->inner_count++;
            scratch->inner_offset += scratch->x_step;
        }
inner_done:
        scratch->outer_count++;
        scratch->outer_offset += scratch->y_step;
    }
outer_done:
    if (scratch->best == 0x7FFF)
        return 0x7FFF;
    return (s16)((u16)scratch->block_base + (u16)scratch->best);
}
