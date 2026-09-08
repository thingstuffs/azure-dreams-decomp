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

void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 flags;
    s8 *config;
    DungeonCell *cells;
    s32 call_x;
    s32 call_y;
    s32 row_x;
    s32 row_y;
    s32 test;
    s32 index;

    flags = arg2;
    cells = D_80083160.cells;
    config = (s8 *)&D_80083160.cells;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    test = flags & 0x8832;
    if (test) {
        test = flags & 0x800;
        if (test) {
            s32 call_arg0;
            register s32 shifted_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            call_x = (s16)arg0;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            call_y = (s16)arg1;
            call_arg0 = call_x;
            ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            if ((s16)func_800A6E10(call_arg0, call_y) >= 2) {
                goto done;
            }
            shifted_y = *(s16 *)(config + 0x14);
            shifted_y = call_y << shifted_y;
            index = call_x + shifted_y;
        } else {
            ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            index = (s16)arg0 +
                    ((s16)arg1 << *(s16 *)(config + 0x14));
        }

        cells[index].flags &= ~flags;
        goto done;
    }

    {
        u32 raw_value;
        register s32 value ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        s32 row_index;
        register DungeonCell *cell ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 old_flags ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        row_x = (s16)arg0;
        row_y = (s16)arg1;
        row_index = row_x + (row_y << *(s16 *)(config + 0x14));
        cell = (DungeonCell *)((row_index * sizeof(DungeonCell)) +
                               (unsigned long)cells);
        old_flags = cell->flags;
        raw_value = (old_flags & flags) - (flags & 0x1100);
        value = raw_value;
        old_flags &= ~flags;
        cell->flags = old_flags;
        raw_value <<= 16;
        if ((s32)raw_value < 0) {
            value = 0;
        }

        row_index = row_x + (row_y << *(s16 *)(config + 0x14));
        cell = (DungeonCell *)((row_index * sizeof(DungeonCell)) +
                               (unsigned long)cells);
        cell->flags |= value;
    }

done:
    ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: Recover the true-space internal joins as one CFG, not phantom calls.
   Keep flags, config/table bases, and call-path x/y live to induce s0-s4. */
