#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_multi_slot_action_sequence(void *action_in, ObjectPosition *motion_in, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_80AEBA30. */
const void *const D_8014C850[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_multi_slot_action_sequence + 0x6C),
    ((u8 *)advance_multi_slot_action_sequence + 0x29C),
    ((u8 *)advance_multi_slot_action_sequence + 0x2E4),
    ((u8 *)advance_multi_slot_action_sequence + 0x514),
    ((u8 *)advance_multi_slot_action_sequence + 0x59C)
};
