#include "common.h"

extern void advance_actor_ability_action(void);

/* jump_table; owner: dungeon/func_80FC55EC. */
const void *const D_8015E850[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_ability_action + 0x11C),
    ((u8 *)advance_actor_ability_action + 0x114),
    ((u8 *)advance_actor_ability_action + 0x10C),
    ((u8 *)advance_actor_ability_action + 0x124),
    ((u8 *)advance_actor_ability_action + 0xCC),
    ((u8 *)advance_actor_ability_action + 0xC4),
    ((u8 *)advance_actor_ability_action + 0xBC)
};
