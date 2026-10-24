#include "common.h"

extern void update_actor_action_variant(void);

/* jump_table; owner: dungeon/func_80BFD814. */
const void *const clown_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_variant + 0x45C),
    ((u8 *)update_actor_action_variant + 0x45C),
    ((u8 *)update_actor_action_variant + 0x45C),
    ((u8 *)update_actor_action_variant + 0x488),
    ((u8 *)update_actor_action_variant + 0x408),
    ((u8 *)update_actor_action_variant + 0x408),
    ((u8 *)update_actor_action_variant + 0x408),
    ((u8 *)update_actor_action_variant + 0x3D0),
    ((u8 *)update_actor_action_variant + 0x3D0),
    ((u8 *)update_actor_action_variant + 0x488),
    ((u8 *)update_actor_action_variant + 0x488),
    ((u8 *)update_actor_action_variant + 0x44C)
};
