#include "common.h"

extern void update_actor_movement_variant(void);

/* jump_table; owner: dungeon/func_80F45694. */
const u32 D_8015E808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_movement_variant + 0x3E4),
    (u32)((u8 *)update_actor_movement_variant + 0x3E4),
    (u32)((u8 *)update_actor_movement_variant + 0x3E4),
    (u32)((u8 *)update_actor_movement_variant + 0x410),
    (u32)((u8 *)update_actor_movement_variant + 0x390),
    (u32)((u8 *)update_actor_movement_variant + 0x390),
    (u32)((u8 *)update_actor_movement_variant + 0x390),
    (u32)((u8 *)update_actor_movement_variant + 0x33C),
    (u32)((u8 *)update_actor_movement_variant + 0x374),
    (u32)((u8 *)update_actor_movement_variant + 0x410),
    (u32)((u8 *)update_actor_movement_variant + 0x410),
    (u32)((u8 *)update_actor_movement_variant + 0x3D4)
};
