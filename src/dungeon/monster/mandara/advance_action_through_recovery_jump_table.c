#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct ActorRecord;
struct ObjectPosition;
struct SpriteFrameState;
#include "common.h"
#include "dungeon/monster/mandara.h"

/* Exact jump_table span; dispatch consumer dungeon/func_80FB35EC. */
const void *const D_80170850[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_action_through_recovery + 0x11C),
    ((u8 *)advance_action_through_recovery + 0x114),
    ((u8 *)advance_action_through_recovery + 0x10C),
    ((u8 *)advance_action_through_recovery + 0x124),
    ((u8 *)advance_action_through_recovery + 0xCC),
    ((u8 *)advance_action_through_recovery + 0xC4),
    ((u8 *)advance_action_through_recovery + 0xBC)
};
