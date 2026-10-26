#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

void update_object_animation(ActorRecord *obj, ObjectPosition *motion, SpriteFrameState *part, ActorRecord *state);

/* jump_table; owner: dungeon/func_81251D14. */
const void *const beldo_slot_g_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_object_animation + 0x3AC),
    ((u8 *)update_object_animation + 0x3AC),
    ((u8 *)update_object_animation + 0x3AC),
    ((u8 *)update_object_animation + 0x3D4),
    ((u8 *)update_object_animation + 0x380),
    ((u8 *)update_object_animation + 0x380),
    ((u8 *)update_object_animation + 0x380),
    ((u8 *)update_object_animation + 0x380),
    ((u8 *)update_object_animation + 0x380),
    ((u8 *)update_object_animation + 0x3D4),
    ((u8 *)update_object_animation + 0x3D4),
    ((u8 *)update_object_animation + 0x370)
};
