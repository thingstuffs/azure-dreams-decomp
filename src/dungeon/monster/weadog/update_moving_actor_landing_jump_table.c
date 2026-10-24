#include "common.h"

extern void update_moving_actor_landing(void);

/* jump_table; owner: dungeon/func_80F03000. */
const void *const D_8014C828[5] __attribute__((aligned(4))) = {
    ((u8 *)update_moving_actor_landing + 0x12C),
    ((u8 *)update_moving_actor_landing + 0x134),
    ((u8 *)update_moving_actor_landing + 0x13C),
    ((u8 *)update_moving_actor_landing + 0x144),
    ((u8 *)update_moving_actor_landing + 0x14C)
};
