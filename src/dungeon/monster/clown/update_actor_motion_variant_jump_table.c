#include "common.h"

extern void update_actor_motion_variant(void);

/* jump_table; owner: dungeon/func_80BFEDA4. */
const void *const clown_slot_d_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_motion_variant + 0x11C),
    ((u8 *)update_actor_motion_variant + 0x114),
    ((u8 *)update_actor_motion_variant + 0x10C),
    ((u8 *)update_actor_motion_variant + 0x124),
    ((u8 *)update_actor_motion_variant + 0xCC),
    ((u8 *)update_actor_motion_variant + 0xC4),
    ((u8 *)update_actor_motion_variant + 0xBC)
};
