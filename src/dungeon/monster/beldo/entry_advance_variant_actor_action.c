#include "common.h"
#include "shared/sprite_frame_state.h"

extern void advance_variant_actor_action(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_8126AD6C. */
const void *const beldo_slot_c_action_targets[9] __attribute__((aligned(4))) = {
    ((u8 *)advance_variant_actor_action + 0x64),
    ((u8 *)advance_variant_actor_action + 0x2A8),
    ((u8 *)advance_variant_actor_action + 0x2F0),
    ((u8 *)advance_variant_actor_action + 0x330),
    ((u8 *)advance_variant_actor_action + 0x3D0),
    ((u8 *)advance_variant_actor_action + 0x43C),
    ((u8 *)advance_variant_actor_action + 0x4A4),
    ((u8 *)advance_variant_actor_action + 0x4C4),
    ((u8 *)advance_variant_actor_action + 0x558)
};
