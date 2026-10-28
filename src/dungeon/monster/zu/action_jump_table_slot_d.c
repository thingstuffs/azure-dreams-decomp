#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_8015F138(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats_in);

/* jump_table; owner: dungeon/func_80F99938. */
const void *const zu_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)func_8015F138 + 0x434),
    ((u8 *)func_8015F138 + 0x434),
    ((u8 *)func_8015F138 + 0x434),
    ((u8 *)func_8015F138 + 0x460),
    ((u8 *)func_8015F138 + 0x3E0),
    ((u8 *)func_8015F138 + 0x3E0),
    ((u8 *)func_8015F138 + 0x3E0),
    ((u8 *)func_8015F138 + 0x3A8),
    ((u8 *)func_8015F138 + 0x38C),
    ((u8 *)func_8015F138 + 0x460),
    ((u8 *)func_8015F138 + 0x460),
    ((u8 *)func_8015F138 + 0x424)
};
