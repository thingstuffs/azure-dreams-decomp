#include "common.h"

extern void advance_variant_actor_action(void);

/* jump_table; owner: dungeon/func_8126AD6C. */
const u32 D_80158860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_variant_actor_action + 0x114),
    (u32)((u8 *)advance_variant_actor_action + 0x10C),
    (u32)((u8 *)advance_variant_actor_action + 0x104),
    (u32)((u8 *)advance_variant_actor_action + 0x11C),
    (u32)((u8 *)advance_variant_actor_action + 0xC0),
    (u32)((u8 *)advance_variant_actor_action + 0xB8),
    (u32)((u8 *)advance_variant_actor_action + 0xB0)
};
