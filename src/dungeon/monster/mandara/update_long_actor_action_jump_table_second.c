#include "common.h"

extern void update_long_actor_action(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB176C. */
const void *const D_80170820[12] __attribute__((aligned(4))) = {
    ((u8 *)update_long_actor_action + 0x828),
    ((u8 *)update_long_actor_action + 0x828),
    ((u8 *)update_long_actor_action + 0x828),
    ((u8 *)update_long_actor_action + 0x854),
    ((u8 *)update_long_actor_action + 0x7D4),
    ((u8 *)update_long_actor_action + 0x7D4),
    ((u8 *)update_long_actor_action + 0x7D4),
    ((u8 *)update_long_actor_action + 0x76C),
    ((u8 *)update_long_actor_action + 0x76C),
    ((u8 *)update_long_actor_action + 0x854),
    ((u8 *)update_long_actor_action + 0x854),
    ((u8 *)update_long_actor_action + 0x818)
};
