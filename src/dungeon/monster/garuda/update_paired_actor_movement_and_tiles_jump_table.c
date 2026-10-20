#include "common.h"

extern void update_paired_actor_movement_and_tiles(void);

/* jump_table; owner: dungeon/func_8102C664. */
const u32 D_8014C878[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_paired_actor_movement_and_tiles + 0x7C),
    (u32)((u8 *)update_paired_actor_movement_and_tiles + 0x294),
    (u32)((u8 *)update_paired_actor_movement_and_tiles + 0x3A0),
    (u32)((u8 *)update_paired_actor_movement_and_tiles + 0x694),
    (u32)((u8 *)update_paired_actor_movement_and_tiles + 0x804)
};
