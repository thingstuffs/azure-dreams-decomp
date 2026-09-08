#include "common.h"


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


typedef struct S_8008DA80_0 {
    u8 pad_00[0x1DC];
    u16 * unk_1DC;
} S_8008DA80_0;   /* base in func_8008DA80 */

typedef struct S_8008DA80_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x8];
    u16 unk_10;
    u8 pad_12[0x4];
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_16;   /* overlapping accesses */
} S_8008DA80_1;   /* entry in func_8008DA80 */

typedef struct S_8008DA80_2 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_8008DA80_2;   /* plane in func_8008DA80 */

typedef struct S_8008DA80_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_8008DA80_3;   /* vertex in func_8008DA80 */

typedef struct S_8008DA80_4 {
    s16 unk_00;
} S_8008DA80_4;   /* ((S_8008DA80_1 *)entry)->unk_10 * 8 + scratch->height_data in func_8008DA80 */

typedef struct S_8008DA80_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_5;   /* ((S_8008DA80_1 *)entry)->unk_00 * 8 + vertices in func_8008DA80 */

typedef struct S_8008DA80_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_6;   /* ((S_8008DA80_1 *)entry)->unk_02 * 8 + vertices in func_8008DA80 */

typedef struct S_8008DA80_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_7;   /* ((S_8008DA80_1 *)entry)->unk_06 * 8 + vertices in func_8008DA80 */

typedef struct S_8008DA80_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_8;   /* ((S_8008DA80_1 *)entry)->unk_04 * 8 + vertices in func_8008DA80 */

/* Finds the smallest eligible surface X coordinate across neighboring grid tiles. */
s16 func_8008DA80(s32 query_x, s32 query_y, s32 query_z)
{
    Scratch80090320 *scratch;
    Grid80090320 *grid;
    u16 *occupancy;
    u8 *grid_data;
    u8 *vertices;
    u8 *entry;
    u8 *plane;
    u8 *vertex;
    s16 block_base;
    s16 tile;
    s16 candidate_x;
    s16 x;
    u16 y;
    s32 row_y;
    s32 plane_x;
    s16 column_x;

    x = query_x;
    y = query_y;
    scratch = (Scratch80090320 *)0x1F800000;
    scratch->best = 0x7FFF;
    block_base = query_x & ~0x3F;
    scratch->block_base = block_base;
    scratch->lower_bound = (s16)query_x - block_base - 0x14;
    scratch->origin_y = query_y & 0x3F;
    scratch->origin_z = query_z;
    grid_data = D_80083160;
    grid = (Grid80090320 *)(grid_data + 0x1DC);
    ASM_USE(query_x);   /* MATCH pin: keeps a statement from moving across a call/branch */
    scratch->result = (query_x &= 0x3F);
    scratch->saved_y = query_y & 0x3F;
    scratch->height_data = grid->height_data;
    occupancy = ((S_8008DA80_0 *)grid_data)->unk_1DC;
    vertices = grid->vertices;
    if (query_x >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }
    if ((s16)*(volatile u16 *)((u8 *)scratch + 0x1E) >= 0x20) {
        s32 y_step_pos = 0x40;
        scratch->y_step = y_step_pos;
    } else {
        s32 y_step_neg = -0x40;
        scratch->y_step = y_step_neg;
    }

    scratch->outer_count = 0;
    scratch->start_x = x;
    scratch->start_y = y;
    scratch->outer_offset = 0;
    while (scratch->outer_count < 2) {
        row_y = (u16)scratch->start_y + (u16)scratch->outer_offset;
        y = row_y;
        if (scratch->y_step >= 0) {
            if ((s16)row_y >= D_800FE484)
                goto outer_done;
        } else if ((s16)row_y < 0) {
            goto outer_done;
        }
        scratch->inner_count = 0;
        scratch->inner_offset = 0;
        scratch->origin_y = scratch->saved_y - (u16)scratch->outer_offset;
        while (scratch->inner_count < 2) {
            column_x = (u16)scratch->start_x + (u16)scratch->inner_offset;
            x = column_x;
            if (scratch->x_step >= 0) {
                if ((s16)column_x >= D_800FE480)
                    goto inner_done;
            } else if ((s16)column_x < 0) {
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
                    if (((S_8008DA80_4 *)(((S_8008DA80_1 *)entry)->unk_10 * 8 + scratch->height_data))->unk_00 < 0 &&
                        !(((S_8008DA80_1 *)entry)->unk_16.at01.v & 1)) {
                        scratch->d0 = ((S_8008DA80_5 *)(((S_8008DA80_1 *)entry)->unk_00 * 8 + vertices))->unk_02 - scratch->origin_y;
                        scratch->d1 = ((S_8008DA80_5 *)(((S_8008DA80_1 *)entry)->unk_00 * 8 + vertices))->unk_04 - scratch->origin_z;
                        scratch->d2 = ((S_8008DA80_6 *)(((S_8008DA80_1 *)entry)->unk_02 * 8 + vertices))->unk_02 - scratch->origin_y;
                        scratch->d3 = ((S_8008DA80_6 *)(((S_8008DA80_1 *)entry)->unk_02 * 8 + vertices))->unk_04 - scratch->origin_z;
                        scratch->d4 = ((S_8008DA80_7 *)(((S_8008DA80_1 *)entry)->unk_06 * 8 + vertices))->unk_02 - scratch->origin_y;
                        scratch->d5 = ((S_8008DA80_7 *)(((S_8008DA80_1 *)entry)->unk_06 * 8 + vertices))->unk_04 - scratch->origin_z;
                        scratch->d6 = ((S_8008DA80_8 *)(((S_8008DA80_1 *)entry)->unk_04 * 8 + vertices))->unk_02 - scratch->origin_y;
                        scratch->d7 = ((S_8008DA80_8 *)(((S_8008DA80_1 *)entry)->unk_04 * 8 + vertices))->unk_04 - scratch->origin_z;

                        if (func_8008CE08(scratch) != 0) {
                            plane = (u8 *)(((S_8008DA80_1 *)entry)->unk_10 * 8 +
                                           (u32)scratch->height_data);
                            vertex = (u8 *)(((S_8008DA80_1 *)entry)->unk_00 * 8 +
                                            (u32)vertices);
                            plane_x =
                                (((S_8008DA80_2 *)plane)->unk_02 *
                                     (((S_8008DA80_3 *)vertex)->unk_02 -
                                      (s16)*(volatile u16 *)((u8 *)scratch + 0x1E)) +
                                 ((S_8008DA80_2 *)plane)->unk_04 *
                                     (((S_8008DA80_3 *)vertex)->unk_04 -
                                      (s16)*(volatile u16 *)((u8 *)scratch + 0x20)) +
                                 ((S_8008DA80_2 *)plane)->unk_00 * ((S_8008DA80_3 *)vertex)->unk_00) /
                                ((S_8008DA80_2 *)plane)->unk_00;
                            scratch->result = plane_x;
                            plane_x += scratch->inner_index;
                            scratch->result = plane_x;
                            candidate_x = plane_x;
                            if (candidate_x >= scratch->lower_bound && candidate_x < scratch->best)
                                scratch->best = candidate_x;
                        }
                    }
                    if ((((S_8008DA80_1 *)entry)->unk_16.at00.v & 0x80FF) == 0x8001)
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
