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

    flags = flag_mask;
    cells = D_80083160.cells;
    config = (s8 *)&D_80083160.cells;
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */

    matched_flags = flags & 0x8832;
    if (matched_flags) {
        matched_flags = flags & 0x800;
        if (matched_flags) {
            s32 query_x;
            register s32 row_offset ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

            checked_x = (s16)x;
            ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
            checked_y = (s16)y;
            query_x = checked_x;
            ASM_KEEP(query_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
            if ((s16)func_800A6E10(query_x, checked_y) >= 2) {
                goto done;
            }
            row_offset = *(s16 *)(config + 0x14);
            row_offset = checked_y << row_offset;
            cell_index = checked_x + row_offset;
        } else {
            ASM_CLOBBER("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            cell_index = (s16)x +
                    ((s16)y << *(s16 *)(config + 0x14));
        }

        cells[cell_index].flags &= ~flags;
        goto done;
    }

    {
        u32 raw_remainder;
        register s32 remainder ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 flag_cell_index;
        register DungeonCell *cell ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register u16 old_flags ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */

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
    ASM_KEEP(flags);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
}

/* MECHANISM: Recover the true-space internal joins as one CFG, not phantom calls.
   Keep flags, config/table bases, and call-path x/y live to induce s0-s4. */
