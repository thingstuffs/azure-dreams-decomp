#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_overlay_actor_facing_effects(ActorRecord *action, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor);

/* jump_table; owner: dungeon/func_812656C4. */
const void *const D_8015E880[6] __attribute__((aligned(4))) = {
    ((u8 *)advance_overlay_actor_facing_effects + 0x5C),
    ((u8 *)advance_overlay_actor_facing_effects + 0xCC),
    ((u8 *)advance_overlay_actor_facing_effects + 0xE4),
    ((u8 *)advance_overlay_actor_facing_effects + 0x110),
    ((u8 *)advance_overlay_actor_facing_effects + 0x38C),
    ((u8 *)advance_overlay_actor_facing_effects + 0x3FC)
};
