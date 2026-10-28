#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_ability(ActorRecord *action_state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80D97070. */
const void *const dreamin_slot_f_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_ability + 0x11C),
    ((u8 *)advance_actor_ability + 0x114),
    ((u8 *)advance_actor_ability + 0x10C),
    ((u8 *)advance_actor_ability + 0x124),
    ((u8 *)advance_actor_ability + 0xCC),
    ((u8 *)advance_actor_ability + 0xC4),
    ((u8 *)advance_actor_ability + 0xBC)
};
