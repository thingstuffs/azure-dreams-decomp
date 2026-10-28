#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void dispatch_dungeon_actor_behavior_and_facing(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);

/* jump_table; owner: dungeon/func_80DB3668. */
const void *const dreamin_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3A0),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3A0),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3A0),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3CC),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x34C),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x34C),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x34C),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x2DC),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x2CC),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3CC),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3CC),
    ((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x390)
};
