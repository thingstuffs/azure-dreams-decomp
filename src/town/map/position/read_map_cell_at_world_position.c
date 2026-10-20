#include "common.h"

extern s32 read_map_cell_at_tile(s32, s32);

/* Read the map entry value at world coordinates converted to tiles. */
s32 read_map_cell_at_world_position(s16 world_x, s16 world_y) {
    return read_map_cell_at_tile(world_x / 0x40, world_y / 0x40) & 0xFFFF;
}

/* MECHANISM: Signed s16 arguments divided by 0x40 produce GCC's bgez/addiu/sra
   round-toward-zero expansions in argument order, including both call delay slots.
   The call-only 0x18 frame saves just $ra; the return mask emits the final andi. */
