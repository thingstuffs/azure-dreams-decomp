#include "common.h"

extern void advance_targeted_actor_action(void);

/* jump_table; owner: dungeon/func_80EE7FB0. */
const u32 D_8016A888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_targeted_actor_action + 0x60),
    (u32)((u8 *)advance_targeted_actor_action + 0x298),
    (u32)((u8 *)advance_targeted_actor_action + 0x2E0),
    (u32)((u8 *)advance_targeted_actor_action + 0x434),
    (u32)((u8 *)advance_targeted_actor_action + 0x448)
};
