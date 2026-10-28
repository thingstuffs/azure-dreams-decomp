#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_80152E68(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);

/* jump_table; owner: dungeon/func_80DAD668. */
const void *const D_80152808[12] __attribute__((aligned(4))) = {
    ((u8 *)func_80152E68 + 0x3A0),
    ((u8 *)func_80152E68 + 0x3A0),
    ((u8 *)func_80152E68 + 0x3A0),
    ((u8 *)func_80152E68 + 0x3CC),
    ((u8 *)func_80152E68 + 0x34C),
    ((u8 *)func_80152E68 + 0x34C),
    ((u8 *)func_80152E68 + 0x34C),
    ((u8 *)func_80152E68 + 0x2DC),
    ((u8 *)func_80152E68 + 0x2CC),
    ((u8 *)func_80152E68 + 0x3CC),
    ((u8 *)func_80152E68 + 0x3CC),
    ((u8 *)func_80152E68 + 0x390)
};
