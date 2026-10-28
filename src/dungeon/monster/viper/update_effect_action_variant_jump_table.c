#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_effect_action_variant(ActorRecord *state, ObjectPosition *transform, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80F4775C. */
const void *const D_8015E878[7] __attribute__((aligned(4))) = {
    ((u8 *)update_effect_action_variant + 0x11C),
    ((u8 *)update_effect_action_variant + 0x114),
    ((u8 *)update_effect_action_variant + 0x10C),
    ((u8 *)update_effect_action_variant + 0x124),
    ((u8 *)update_effect_action_variant + 0xCC),
    ((u8 *)update_effect_action_variant + 0xC4),
    ((u8 *)update_effect_action_variant + 0xBC)
};
