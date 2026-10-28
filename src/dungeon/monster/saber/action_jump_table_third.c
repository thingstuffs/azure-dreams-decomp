#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_80161230(void *action_in, ObjectPosition *motion_in, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_80AD9A30. */
const void *const D_8015E850[5] __attribute__((aligned(4))) = {
    ((u8 *)func_80161230 + 0x6C),
    ((u8 *)func_80161230 + 0x29C),
    ((u8 *)func_80161230 + 0x2E4),
    ((u8 *)func_80161230 + 0x514),
    ((u8 *)func_80161230 + 0x59C)
};
