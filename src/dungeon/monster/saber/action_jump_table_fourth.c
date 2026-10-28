#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_80161230(void *action_in, ObjectPosition *motion_in, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_80AD9A30. */
const void *const saber_slot_d_extra_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)func_80161230 + 0x11C),
    ((u8 *)func_80161230 + 0x114),
    ((u8 *)func_80161230 + 0x10C),
    ((u8 *)func_80161230 + 0x124),
    ((u8 *)func_80161230 + 0xC8),
    ((u8 *)func_80161230 + 0xC0),
    ((u8 *)func_80161230 + 0xB8)
};
