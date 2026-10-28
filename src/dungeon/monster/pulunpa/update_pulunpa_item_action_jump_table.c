#include "common.h"
#include "shared/entity.h"

extern void func_80175480(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80CC1C80. */
const void *const D_80170888[7] __attribute__((aligned(4))) = {
    ((u8 *)func_80175480 + 0x11C),
    ((u8 *)func_80175480 + 0x114),
    ((u8 *)func_80175480 + 0x10C),
    ((u8 *)func_80175480 + 0x124),
    ((u8 *)func_80175480 + 0xCC),
    ((u8 *)func_80175480 + 0xC4),
    ((u8 *)func_80175480 + 0xBC)
};
