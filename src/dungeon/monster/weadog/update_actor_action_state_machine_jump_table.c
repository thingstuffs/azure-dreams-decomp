#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_action_state_machine(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80F05D14. */
const void *const D_8014C870[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_state_machine + 0x48),
    ((u8 *)update_actor_action_state_machine + 0xD4),
    ((u8 *)update_actor_action_state_machine + 0x118),
    ((u8 *)update_actor_action_state_machine + 0x178),
    ((u8 *)update_actor_action_state_machine + 0x23C)
};
