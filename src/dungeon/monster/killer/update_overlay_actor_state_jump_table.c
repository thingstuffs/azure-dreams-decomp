#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_overlay_actor_state(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80FE76A8. */
const void *const D_80164808[12] __attribute__((aligned(4))) = {
    ((u8 *)update_overlay_actor_state + 0x410),
    ((u8 *)update_overlay_actor_state + 0x410),
    ((u8 *)update_overlay_actor_state + 0x410),
    ((u8 *)update_overlay_actor_state + 0x43C),
    ((u8 *)update_overlay_actor_state + 0x3BC),
    ((u8 *)update_overlay_actor_state + 0x3BC),
    ((u8 *)update_overlay_actor_state + 0x3BC),
    ((u8 *)update_overlay_actor_state + 0x34C),
    ((u8 *)update_overlay_actor_state + 0x33C),
    ((u8 *)update_overlay_actor_state + 0x43C),
    ((u8 *)update_overlay_actor_state + 0x43C),
    ((u8 *)update_overlay_actor_state + 0x400)
};
