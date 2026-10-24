
struct ActorRecord;
struct ObjectPosition;
struct SpriteFrameState;
#include "common.h"

extern void advance_action_through_recovery(void *action_state, struct ObjectPosition *transform,struct SpriteFrameState *sprite, struct ActorRecord *actor);

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
