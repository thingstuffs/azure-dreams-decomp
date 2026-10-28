#include "common.h"
#include "shared/sprite_frame_state.h"
struct ActorMotion;
struct PairAction;

extern void update_paired_actor_movement_tile_placement_animations_restored_flags(struct PairAction *actor, struct ActorMotion *motion, SpriteFrameState *sprite, void *entity);

/* jump_table; owner: dungeon/func_8101A664. */
const void *const D_8015E878[5] __attribute__((aligned(4))) = {
    ((u8 *)update_paired_actor_movement_tile_placement_animations_restored_flags + 0x7C),
    ((u8 *)update_paired_actor_movement_tile_placement_animations_restored_flags + 0x294),
    ((u8 *)update_paired_actor_movement_tile_placement_animations_restored_flags + 0x3A0),
    ((u8 *)update_paired_actor_movement_tile_placement_animations_restored_flags + 0x694),
    ((u8 *)update_paired_actor_movement_tile_placement_animations_restored_flags + 0x804)
};
