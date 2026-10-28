#include "common.h"
#include "shared/sprite_frame_state.h"

extern void advance_overlay_actor_action(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_81264D6C. */
const void *const D_8015E860[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_overlay_actor_action + 0x114),
    ((u8 *)advance_overlay_actor_action + 0x10C),
    ((u8 *)advance_overlay_actor_action + 0x104),
    ((u8 *)advance_overlay_actor_action + 0x11C),
    ((u8 *)advance_overlay_actor_action + 0xC0),
    ((u8 *)advance_overlay_actor_action + 0xB8),
    ((u8 *)advance_overlay_actor_action + 0xB0)
};
