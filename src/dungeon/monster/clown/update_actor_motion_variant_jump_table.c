#include "common.h"

extern void update_actor_motion_variant(void);

/* jump_table; owner: dungeon/func_80BFEDA4. */
const u32 clown_slot_d_action_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_motion_variant + 0x11C),
    (u32)((u8 *)update_actor_motion_variant + 0x114),
    (u32)((u8 *)update_actor_motion_variant + 0x10C),
    (u32)((u8 *)update_actor_motion_variant + 0x124),
    (u32)((u8 *)update_actor_motion_variant + 0xCC),
    (u32)((u8 *)update_actor_motion_variant + 0xC4),
    (u32)((u8 *)update_actor_motion_variant + 0xBC)
};
