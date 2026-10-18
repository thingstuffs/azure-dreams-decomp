#include "common.h"

extern void update_actor_targeted_action(void);

/* jump_table; owner: dungeon/func_80EE1FB0. */
const u32 D_80170888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_targeted_action + 0x60),
    (u32)((u8 *)update_actor_targeted_action + 0x298),
    (u32)((u8 *)update_actor_targeted_action + 0x2E0),
    (u32)((u8 *)update_actor_targeted_action + 0x434),
    (u32)((u8 *)update_actor_targeted_action + 0x448)
};
