#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_multi_slot_action_sequence(void *action_in, ObjectPosition *motion_in, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_80AEBA30. */
const void *const saber_slot_a_extra_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_multi_slot_action_sequence + 0x11C),
    ((u8 *)advance_multi_slot_action_sequence + 0x114),
    ((u8 *)advance_multi_slot_action_sequence + 0x10C),
    ((u8 *)advance_multi_slot_action_sequence + 0x124),
    ((u8 *)advance_multi_slot_action_sequence + 0xC8),
    ((u8 *)advance_multi_slot_action_sequence + 0xC0),
    ((u8 *)advance_multi_slot_action_sequence + 0xB8)
};
