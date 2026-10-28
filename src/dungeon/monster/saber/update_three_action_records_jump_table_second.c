#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_three_action_records(void *action_in, ObjectPosition *motion_in, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_80ACDA30. */
const void *const saber_slot_f_extra_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)update_three_action_records + 0x11C),
    ((u8 *)update_three_action_records + 0x114),
    ((u8 *)update_three_action_records + 0x10C),
    ((u8 *)update_three_action_records + 0x124),
    ((u8 *)update_three_action_records + 0xC8),
    ((u8 *)update_three_action_records + 0xC0),
    ((u8 *)update_three_action_records + 0xB8)
};
