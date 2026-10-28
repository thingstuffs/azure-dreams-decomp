#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_80152EA8(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80FF96A8. */
const void *const D_80152808[12] __attribute__((aligned(4))) = {
    ((u8 *)func_80152EA8 + 0x410),
    ((u8 *)func_80152EA8 + 0x410),
    ((u8 *)func_80152EA8 + 0x410),
    ((u8 *)func_80152EA8 + 0x43C),
    ((u8 *)func_80152EA8 + 0x3BC),
    ((u8 *)func_80152EA8 + 0x3BC),
    ((u8 *)func_80152EA8 + 0x3BC),
    ((u8 *)func_80152EA8 + 0x34C),
    ((u8 *)func_80152EA8 + 0x33C),
    ((u8 *)func_80152EA8 + 0x43C),
    ((u8 *)func_80152EA8 + 0x43C),
    ((u8 *)func_80152EA8 + 0x400)
};
