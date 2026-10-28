#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_entity_movement_and_recovery_animation(void *state, ObjectPosition *motion, SpriteFrameState *actor, void *object);

/* jump_table; owner: dungeon/func_80EA0C28. */
const void *const D_8015E8F0[6] __attribute__((aligned(4))) = {
    ((u8 *)update_entity_movement_and_recovery_animation + 0x90),
    ((u8 *)update_entity_movement_and_recovery_animation + 0x130),
    ((u8 *)update_entity_movement_and_recovery_animation + 0x1C0),
    ((u8 *)update_entity_movement_and_recovery_animation + 0x24C),
    ((u8 *)update_entity_movement_and_recovery_animation + 0x2BC),
    ((u8 *)update_entity_movement_and_recovery_animation + 0x39C)
};
