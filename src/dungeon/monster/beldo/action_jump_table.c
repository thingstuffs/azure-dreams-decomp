#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void func_8014D514(ActorRecord *obj, ObjectPosition *motion, SpriteFrameState *part, ActorRecord *state);

/* jump_table; owner: dungeon/func_81275D14. */
const void *const beldo_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)func_8014D514 + 0x3AC),
    ((u8 *)func_8014D514 + 0x3AC),
    ((u8 *)func_8014D514 + 0x3AC),
    ((u8 *)func_8014D514 + 0x3D4),
    ((u8 *)func_8014D514 + 0x380),
    ((u8 *)func_8014D514 + 0x380),
    ((u8 *)func_8014D514 + 0x380),
    ((u8 *)func_8014D514 + 0x380),
    ((u8 *)func_8014D514 + 0x380),
    ((u8 *)func_8014D514 + 0x3D4),
    ((u8 *)func_8014D514 + 0x3D4),
    ((u8 *)func_8014D514 + 0x370)
};
