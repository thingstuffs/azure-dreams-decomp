#include "common.h"

extern void update_actor_special_action(void);

/* jump_table; owner: dungeon/func_80FC976C. */
const u32 D_80158808[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_special_action + 0x1C0),
    (u32)((u8 *)update_actor_special_action + 0x22C),
    (u32)((u8 *)update_actor_special_action + 0x300),
    (u32)((u8 *)update_actor_special_action + 0x490),
    (u32)((u8 *)update_actor_special_action + 0x4D8)
};
