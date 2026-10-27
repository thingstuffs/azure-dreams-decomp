#include "common.h"
#include "shared/sprite_frame_state.h"
struct ActorMotion;
struct PairAction;

extern void restore_bank_actor_callback(struct PairAction *actor, struct ActorMotion *motion, SpriteFrameState *sprite, void *entity);

/* jump_table; owner: dungeon/func_8100E664. */
const void *const D_8016A878[5] __attribute__((aligned(4))) = {
    ((u8 *)restore_bank_actor_callback + 0x7C),
    ((u8 *)restore_bank_actor_callback + 0x294),
    ((u8 *)restore_bank_actor_callback + 0x3A0),
    ((u8 *)restore_bank_actor_callback + 0x694),
    ((u8 *)restore_bank_actor_callback + 0x804)
};
