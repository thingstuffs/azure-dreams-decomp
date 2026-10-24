#include "common.h"

extern void update_actor_movement_recovery(void);

/* jump_table; owner: dungeon/func_80EB2C28. */
const void *const D_8014C8F0[6] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_movement_recovery + 0x90),
    ((u8 *)update_actor_movement_recovery + 0x130),
    ((u8 *)update_actor_movement_recovery + 0x1C0),
    ((u8 *)update_actor_movement_recovery + 0x24C),
    ((u8 *)update_actor_movement_recovery + 0x2BC),
    ((u8 *)update_actor_movement_recovery + 0x39C)
};
