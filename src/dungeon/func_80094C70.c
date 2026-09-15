#include "common.h"

typedef struct {
    u8 pad[4];
    u16 flags;
} DungeonCell;

typedef struct {
    u8 pad[0x1DC];
    DungeonCell *cells;
} DungeonState;

extern DungeonState D_80083160;
s32 func_800A6E10(s32, s32);

/* Clears selected cell flags or decrements their encoded value, clamping at zero. */
void func_8009A3D0(s32 x, s32 y, s32 flag_mask)
{
    s32 flags;
    s8 *config;
    DungeonCell *cells;
    s32 checked_x;
    s32 checked_y;
    s32 cell_x;
    s32 cell_y;
    s32 matched_flags;
    s32 cell_index;
    register DungeonCell *cell ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    flags = flag_mask;
    cells = D_80083160.cells;
    config = (s8 *)&D_80083160.cells;

    matched_flags = flags & 0x8832;
    if (matched_flags) {
        matched_flags = flags & 0x800;
        if (matched_flags) {
            s32 query_x;

            checked_x = (s16)x;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            checked_y = (s16)y;
            query_x = checked_x;
            if ((s16)func_800A6E10(query_x, checked_y) >= 2) {
                goto done;
            }
            cell = (DungeonCell *)(*(s16 *)(config + 0x14));
            cell = (DungeonCell *)(checked_y << (s32)cell);
            cell_index = checked_x + (s32)cell;
        } else {
            ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            cell_index = (s16)x +
                    ((s16)y << *(s16 *)(config + 0x14));
        }

        cells[cell_index].flags &= ~flags;
        goto done;
    }

    {
        u32 raw_remainder;
        register s32 remainder ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        s32 flag_cell_index;
        s32 old_flags;

        cell_x = (s16)x;
        cell_y = (s16)y;
        flag_cell_index = cell_x + (cell_y << *(s16 *)(config + 0x14));
        cell = (DungeonCell *)((flag_cell_index * sizeof(DungeonCell)) +
                               (unsigned long)cells);
        old_flags = cell->flags;
        raw_remainder = (old_flags & flags) - (flags & 0x1100);
        remainder = raw_remainder;
        old_flags &= ~flags;
        cell->flags = old_flags;
        raw_remainder <<= 16;
        if ((s32)raw_remainder < 0) {
            remainder = 0;
        }

        flag_cell_index = cell_x + (cell_y << *(s16 *)(config + 0x14));
        cell = (DungeonCell *)((flag_cell_index * sizeof(DungeonCell)) +
                               (unsigned long)cells);
        cell->flags |= remainder;
    }

done:
}

/* MECHANISM: Recover the true-space internal joins as one CFG, not phantom calls.
   Keep flags, config/table bases, and call-path x/y live to induce s0-s4. */
