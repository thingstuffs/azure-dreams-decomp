#include "common.h"

extern void update_actor_behavior_variant(void);

/* jump_table; owner: dungeon/func_80F46FB4. */
const u32 D_8015E860[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_behavior_variant + 0x100),
    (u32)((u8 *)update_actor_behavior_variant + 0x208),
    (u32)((u8 *)update_actor_behavior_variant + 0x270),
    (u32)((u8 *)update_actor_behavior_variant + 0x30C),
    (u32)((u8 *)update_actor_behavior_variant + 0x5DC),
    (u32)((u8 *)update_actor_behavior_variant + 0x660)
};
