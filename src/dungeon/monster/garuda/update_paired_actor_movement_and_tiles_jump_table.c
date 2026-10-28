#include "common.h"
#include "shared/sprite_frame_state.h"
struct ActorMotion;
struct PairAction;

extern void update_paired_actor_movement_and_tiles(struct PairAction *actor, struct ActorMotion *motion, SpriteFrameState *sprite, void *entity);

/* jump_table; owner: dungeon/func_8102C664. */
const void *const D_8014C878[5] __attribute__((aligned(4))) = {
    ((u8 *)update_paired_actor_movement_and_tiles + 0x7C),
    ((u8 *)update_paired_actor_movement_and_tiles + 0x294),
    ((u8 *)update_paired_actor_movement_and_tiles + 0x3A0),
    ((u8 *)update_paired_actor_movement_and_tiles + 0x694),
    ((u8 *)update_paired_actor_movement_and_tiles + 0x804)
};
