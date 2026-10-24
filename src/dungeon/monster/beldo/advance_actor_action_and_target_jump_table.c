#include "common.h"

extern void advance_actor_action_and_target(void);

/* jump_table; owner: dungeon/func_81252D6C. */
const void *const D_80170860[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_and_target + 0x114),
    ((u8 *)advance_actor_action_and_target + 0x10C),
    ((u8 *)advance_actor_action_and_target + 0x104),
    ((u8 *)advance_actor_action_and_target + 0x11C),
    ((u8 *)advance_actor_action_and_target + 0xC0),
    ((u8 *)advance_actor_action_and_target + 0xB8),
    ((u8 *)advance_actor_action_and_target + 0xB0)
};
