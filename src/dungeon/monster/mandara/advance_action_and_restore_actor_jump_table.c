#include "common.h"

extern void advance_action_and_restore_actor(void);

/* jump_table; owner: dungeon/func_80FB95EC. */
const void *const D_8016A850[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_action_and_restore_actor + 0x11C),
    ((u8 *)advance_action_and_restore_actor + 0x114),
    ((u8 *)advance_action_and_restore_actor + 0x10C),
    ((u8 *)advance_action_and_restore_actor + 0x124),
    ((u8 *)advance_action_and_restore_actor + 0xCC),
    ((u8 *)advance_action_and_restore_actor + 0xC4),
    ((u8 *)advance_action_and_restore_actor + 0xBC)
};
