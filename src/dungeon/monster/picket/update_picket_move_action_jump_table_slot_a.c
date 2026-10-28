#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_picket_move_action_slot_a(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EB1490. */
const void *const picket_slot_a_action_targets[17] __attribute__((aligned(4))) = {
    ((u8 *)update_picket_move_action_slot_a + 0xA0),
    ((u8 *)update_picket_move_action_slot_a + 0x364),
    ((u8 *)update_picket_move_action_slot_a + 0x3E4),
    ((u8 *)update_picket_move_action_slot_a + 0x428),
    ((u8 *)update_picket_move_action_slot_a + 0x48C),
    ((u8 *)update_picket_move_action_slot_a + 0x558),
    ((u8 *)update_picket_move_action_slot_a + 0x604),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x760),
    ((u8 *)update_picket_move_action_slot_a + 0x674)
};
