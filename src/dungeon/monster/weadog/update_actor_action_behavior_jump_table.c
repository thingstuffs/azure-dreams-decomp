#include "common.h"

extern void update_actor_action_behavior(void);

/* jump_table; owner: dungeon/func_80F044E8. */
const void *const D_8014C840[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_behavior + 0x3E4),
    ((u8 *)update_actor_action_behavior + 0x3E4),
    ((u8 *)update_actor_action_behavior + 0x3E4),
    ((u8 *)update_actor_action_behavior + 0x410),
    ((u8 *)update_actor_action_behavior + 0x390),
    ((u8 *)update_actor_action_behavior + 0x390),
    ((u8 *)update_actor_action_behavior + 0x390),
    ((u8 *)update_actor_action_behavior + 0x33C),
    ((u8 *)update_actor_action_behavior + 0x374),
    ((u8 *)update_actor_action_behavior + 0x410),
    ((u8 *)update_actor_action_behavior + 0x410),
    ((u8 *)update_actor_action_behavior + 0x3D4)
};
