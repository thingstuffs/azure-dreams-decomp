#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_picket_move_action_slot_a(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EB1490. */
const void *const D_8014C880[7] __attribute__((aligned(4))) = {
    ((u8 *)update_picket_move_action_slot_a + 0x15C),
    ((u8 *)update_picket_move_action_slot_a + 0x154),
    ((u8 *)update_picket_move_action_slot_a + 0x14C),
    ((u8 *)update_picket_move_action_slot_a + 0x164),
    ((u8 *)update_picket_move_action_slot_a + 0x108),
    ((u8 *)update_picket_move_action_slot_a + 0x100),
    ((u8 *)update_picket_move_action_slot_a + 0xF8)
};
