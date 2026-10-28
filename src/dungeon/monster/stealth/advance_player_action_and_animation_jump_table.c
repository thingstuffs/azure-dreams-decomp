#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_player_action_and_animation(void *motion_state, void *transform, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80F2F2A8. */
const void *const stealth_slot_a_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_player_action_and_animation + 0x11C),
    ((u8 *)advance_player_action_and_animation + 0x114),
    ((u8 *)advance_player_action_and_animation + 0x10C),
    ((u8 *)advance_player_action_and_animation + 0x124),
    ((u8 *)advance_player_action_and_animation + 0xCC),
    ((u8 *)advance_player_action_and_animation + 0xC4),
    ((u8 *)advance_player_action_and_animation + 0xBC)
};
