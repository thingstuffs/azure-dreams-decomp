#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_8016CA40(ActorRecord *owner_input, ObjectPosition *motion_input, SpriteFrameState *actor_input, ActorRecord *object);

/* jump_table; owner: dungeon/func_80F8F240. */
const void *const zu_slot_f_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)func_8016CA40 + 0x11C),
    ((u8 *)func_8016CA40 + 0x114),
    ((u8 *)func_8016CA40 + 0x10C),
    ((u8 *)func_8016CA40 + 0x124),
    ((u8 *)func_8016CA40 + 0xCC),
    ((u8 *)func_8016CA40 + 0xC4),
    ((u8 *)func_8016CA40 + 0xBC)
};
