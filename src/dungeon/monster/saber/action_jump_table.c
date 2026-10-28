#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_8015F728(ActorRecord *actor_in, ObjectPosition *context_in, SpriteFrameState *sprite, ActorRecord *creature_in);

/* jump_table; owner: dungeon/func_80AD7F28. */
const void *const saber_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)func_8015F728 + 0x42C),
    ((u8 *)func_8015F728 + 0x42C),
    ((u8 *)func_8015F728 + 0x42C),
    ((u8 *)func_8015F728 + 0x458),
    ((u8 *)func_8015F728 + 0x3D8),
    ((u8 *)func_8015F728 + 0x3D8),
    ((u8 *)func_8015F728 + 0x3D8),
    ((u8 *)func_8015F728 + 0x384),
    ((u8 *)func_8015F728 + 0x3BC),
    ((u8 *)func_8015F728 + 0x458),
    ((u8 *)func_8015F728 + 0x458),
    ((u8 *)func_8015F728 + 0x41C)
};
