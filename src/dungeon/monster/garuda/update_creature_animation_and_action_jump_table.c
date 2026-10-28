#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_creature_animation_and_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *creature);

/* jump_table; owner: dungeon/func_81029858. */
const void *const garuda_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_animation_and_action + 0x494),
    ((u8 *)update_creature_animation_and_action + 0x494),
    ((u8 *)update_creature_animation_and_action + 0x494),
    ((u8 *)update_creature_animation_and_action + 0x4C0),
    ((u8 *)update_creature_animation_and_action + 0x440),
    ((u8 *)update_creature_animation_and_action + 0x440),
    ((u8 *)update_creature_animation_and_action + 0x440),
    ((u8 *)update_creature_animation_and_action + 0x408),
    ((u8 *)update_creature_animation_and_action + 0x3AC),
    ((u8 *)update_creature_animation_and_action + 0x4C0),
    ((u8 *)update_creature_animation_and_action + 0x4C0),
    ((u8 *)update_creature_animation_and_action + 0x484)
};
