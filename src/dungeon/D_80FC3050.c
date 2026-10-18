#include "common.h"

extern void advance_actor_ability_action(void);

/* jump_table; owner: dungeon/func_80FC55EC. */
const u32 D_8015E850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_ability_action + 0x11C),
    (u32)((u8 *)advance_actor_ability_action + 0x114),
    (u32)((u8 *)advance_actor_ability_action + 0x10C),
    (u32)((u8 *)advance_actor_ability_action + 0x124),
    (u32)((u8 *)advance_actor_ability_action + 0xCC),
    (u32)((u8 *)advance_actor_ability_action + 0xC4),
    (u32)((u8 *)advance_actor_ability_action + 0xBC)
};
