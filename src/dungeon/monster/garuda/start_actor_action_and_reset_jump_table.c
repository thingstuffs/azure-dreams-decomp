#include "common.h"

extern void start_actor_action_and_reset(void);

/* jump_table; owner: dungeon/func_8102B034. */
const u32 D_8014C858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)start_actor_action_and_reset + 0x11C),
    (u32)((u8 *)start_actor_action_and_reset + 0x114),
    (u32)((u8 *)start_actor_action_and_reset + 0x10C),
    (u32)((u8 *)start_actor_action_and_reset + 0x124),
    (u32)((u8 *)start_actor_action_and_reset + 0xCC),
    (u32)((u8 *)start_actor_action_and_reset + 0xC4),
    (u32)((u8 *)start_actor_action_and_reset + 0xBC)
};
