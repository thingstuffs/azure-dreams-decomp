#include "common.h"

extern void advance_targeted_actor_action(void);

/* jump_table; owner: dungeon/func_80EE7FB0. */
const u32 D_8016A8A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_targeted_actor_action + 0x110),
    (u32)((u8 *)advance_targeted_actor_action + 0x108),
    (u32)((u8 *)advance_targeted_actor_action + 0x100),
    (u32)((u8 *)advance_targeted_actor_action + 0x118),
    (u32)((u8 *)advance_targeted_actor_action + 0xBC),
    (u32)((u8 *)advance_targeted_actor_action + 0xB4),
    (u32)((u8 *)advance_targeted_actor_action + 0xAC)
};
