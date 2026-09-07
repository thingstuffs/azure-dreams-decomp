#include "common.h"

typedef struct S_8001DC34_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8001DC34_0;   /* argp in func_8001DC34 */

typedef struct S_8001DC34_1_pre {
    s16 unk_00;
} S_8001DC34_1_pre;   /* the 0x2 bytes before var_a0 in func_8001DC34, addressed as var_a0[-1] */

typedef struct S_8001DC34_1 {
    s16 unk_00;
} S_8001DC34_1;   /* var_a0 in func_8001DC34 */



extern u8 D_8008333C[32];
extern u8 D_800E9FFA[];

/* Clear a padded rectangle of grid entries and reset the region state. */
void func_8001DC34(void *region_data)
{
    S_8001DC34_0 *region;
    s16 row;
    s16 cells_left;
    s16 *cell;
    u8 *cell_tail;
    s32 row_shifted;
    s16 *grid_config;
    u32 grid_base;
    s16 first_row;
    s16 next_row;
    s16 end_row;
    s16 remaining;
    s32 row_width;
    region = region_data;
    grid_config = (s16 *)D_8008333C;
    region->unk_0A = 0;
    first_row = region->unk_02 - 1;
    row = first_row;
    ASM_KEEP_NV(row);   /* MATCH pin: retail register colouring depends on it */
    end_row = first_row + region->unk_06 + 2;
    if ((first_row << 16) < (end_row << 16)) {
        grid_base = (u32)D_800E9FFA;
        do {
            row_shifted = row << 16;
            cell = (s16 *)(((((row_shifted >> 16) << grid_config[10]) +
                  region->unk_00) * 6) + grid_base);
            row_width = region->unk_04 + 2;
            cells_left = row_width;
            if ((row_width << 16) > 0) {
                cell_tail = (u8 *)cell + 4;
                do {
                    remaining = cells_left - 1;
                    cells_left = remaining;
                    *cell = 0;
                    ((S_8001DC34_1_pre *)cell_tail)[-1].unk_00 = 0;
                    ((S_8001DC34_1 *)cell_tail)->unk_00 = 0;
                    cell_tail += 6;
                    cell = (s16 *)((u8 *)cell + 6);
                } while ((remaining << 16) > 0);
            }
            next_row = row + 1;
            row = next_row;
        } while (next_row < end_row);
    }
}

/* MECHANISM: Frameless true-name leaf; runtime pins preserve a3/a2/a1 and v1/a0 roles.
   Narrow inner counters plus top-of-loop sign rematerialization recover both loop shapes.
   Integer-address D_800E9FFA with scaled-index-first addition closes the final addu. */
