#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_facing_effect_sequence(ActorRecord *action, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor);

/* jump_table; owner: dungeon/func_812776C4. */
const void *const D_8014C880[6] __attribute__((aligned(4))) = {
    ((u8 *)advance_facing_effect_sequence + 0x5C),
    ((u8 *)advance_facing_effect_sequence + 0xCC),
    ((u8 *)advance_facing_effect_sequence + 0xE4),
    ((u8 *)advance_facing_effect_sequence + 0x110),
    ((u8 *)advance_facing_effect_sequence + 0x38C),
    ((u8 *)advance_facing_effect_sequence + 0x3FC)
};
