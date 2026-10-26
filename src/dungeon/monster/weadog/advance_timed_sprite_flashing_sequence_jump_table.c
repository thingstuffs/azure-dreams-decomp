#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

void advance_timed_sprite_flashing_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EE1D14. */
const void *const D_80170870[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_timed_sprite_flashing_sequence + 0x48),
    ((u8 *)advance_timed_sprite_flashing_sequence + 0xD4),
    ((u8 *)advance_timed_sprite_flashing_sequence + 0x118),
    ((u8 *)advance_timed_sprite_flashing_sequence + 0x178),
    ((u8 *)advance_timed_sprite_flashing_sequence + 0x23C)
};
