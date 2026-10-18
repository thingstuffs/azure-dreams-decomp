#include "common.h"

extern void update_moving_object_landing(void);

/* jump_table; owner: dungeon/func_80EE5000. */
const u32 D_8016A828[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_moving_object_landing + 0x12C),
    (u32)((u8 *)update_moving_object_landing + 0x134),
    (u32)((u8 *)update_moving_object_landing + 0x13C),
    (u32)((u8 *)update_moving_object_landing + 0x144),
    (u32)((u8 *)update_moving_object_landing + 0x14C)
};
