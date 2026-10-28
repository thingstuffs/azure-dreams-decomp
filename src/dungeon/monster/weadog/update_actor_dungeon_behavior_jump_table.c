#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_dungeon_behavior(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in);

/* jump_table; owner: dungeon/func_80EE64E8. */
const void *const D_8016A840[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_dungeon_behavior + 0x3E4),
    ((u8 *)update_actor_dungeon_behavior + 0x3E4),
    ((u8 *)update_actor_dungeon_behavior + 0x3E4),
    ((u8 *)update_actor_dungeon_behavior + 0x410),
    ((u8 *)update_actor_dungeon_behavior + 0x390),
    ((u8 *)update_actor_dungeon_behavior + 0x390),
    ((u8 *)update_actor_dungeon_behavior + 0x390),
    ((u8 *)update_actor_dungeon_behavior + 0x33C),
    ((u8 *)update_actor_dungeon_behavior + 0x374),
    ((u8 *)update_actor_dungeon_behavior + 0x410),
    ((u8 *)update_actor_dungeon_behavior + 0x410),
    ((u8 *)update_actor_dungeon_behavior + 0x3D4)
};
