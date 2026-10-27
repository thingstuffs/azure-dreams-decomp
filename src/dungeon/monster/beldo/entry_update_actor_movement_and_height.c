#include "common.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_movement_and_height(void *entity_arg, void *motion_arg, SpriteFrameState *monster_arg);

/* vector; owner-unresolved. */
const void *const D_80170804[1] __attribute__((aligned(4))) = {
    update_actor_movement_and_height
};
