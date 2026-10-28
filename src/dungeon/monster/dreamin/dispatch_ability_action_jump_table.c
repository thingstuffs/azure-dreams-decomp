#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void dispatch_ability_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);

/* jump_table; owner: dungeon/func_80DA7668. */
const void *const dreamin_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)dispatch_ability_action + 0x3A0),
    ((u8 *)dispatch_ability_action + 0x3A0),
    ((u8 *)dispatch_ability_action + 0x3A0),
    ((u8 *)dispatch_ability_action + 0x3CC),
    ((u8 *)dispatch_ability_action + 0x34C),
    ((u8 *)dispatch_ability_action + 0x34C),
    ((u8 *)dispatch_ability_action + 0x34C),
    ((u8 *)dispatch_ability_action + 0x2DC),
    ((u8 *)dispatch_ability_action + 0x2CC),
    ((u8 *)dispatch_ability_action + 0x3CC),
    ((u8 *)dispatch_ability_action + 0x3CC),
    ((u8 *)dispatch_ability_action + 0x390)
};
