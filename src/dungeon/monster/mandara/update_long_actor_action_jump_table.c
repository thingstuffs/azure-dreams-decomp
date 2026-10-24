#include "common.h"

extern void update_long_actor_action(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB176C. */
const void *const mandara_slot_g_behavior_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)update_long_actor_action + 0x1C0),
    ((u8 *)update_long_actor_action + 0x22C),
    ((u8 *)update_long_actor_action + 0x300),
    ((u8 *)update_long_actor_action + 0x490),
    ((u8 *)update_long_actor_action + 0x4D8)
};
