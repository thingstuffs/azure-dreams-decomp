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
    register s32 flags ASM_REG("$16");
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
    ASM_SCHED_BARRIER();

    test = flags & 0x8832;
    if (test) {
        test = flags & 0x800;
        if (test) {
            register s32 call_arg0 ASM_REG("$4");
            register s32 shifted_y ASM_REG("$3");

            call_x = (s16)arg0;
            ASM_SCHED_BARRIER();
            call_y = (s16)arg1;
            ASM_USE(call_y);
            call_arg0 = call_x;
            ASM_KEEP(call_arg0);
            if ((s16)func_800A6E10(call_arg0, call_y) >= 2) {
                goto done;
            }
            shifted_y = *(s16 *)(config + 0x14);
            shifted_y = call_y << shifted_y;
            index = call_x + shifted_y;
        } else {
            ASM_CLOBBER("$2");
            index = (s16)arg0 +
                    ((s16)arg1 << *(s16 *)(config + 0x14));
        }

        cells[index].flags &= ~flags;
        goto done;
    }

    {
        u32 raw_value;
        register s32 value ASM_REG("$6");
        register s32 row_index ASM_REG("$2");
        register DungeonCell *cell ASM_REG("$3");
        register u16 old_flags ASM_REG("$5");

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
        ASM_USE(raw_value);

        row_index = row_x + (row_y << *(s16 *)(config + 0x14));
        cell = (DungeonCell *)((row_index * sizeof(DungeonCell)) +
                               (unsigned long)cells);
        cell->flags |= value;
        ASM_KEEP(value);
    }

done:
    ASM_KEEP(flags);
}

/* MECHANISM: Recover the true-space internal joins as one CFG, not phantom calls.
   Keep flags, config/table bases, and call-path x/y live to induce s0-s4. */
