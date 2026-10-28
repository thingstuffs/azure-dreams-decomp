#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_dungeon_action_behavior_and_facing(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80E9D8F4. */
const void *const picket_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x410),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x410),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x410),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x43C),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x3BC),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x3BC),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x3BC),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x33C),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x390),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x374),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x43C),
    ((u8 *)update_dungeon_action_behavior_and_facing + 0x400)
};
