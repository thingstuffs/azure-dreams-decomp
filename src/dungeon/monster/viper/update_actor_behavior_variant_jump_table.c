#include "common.h"

extern void update_actor_behavior_variant(void);

/* jump_table; owner: dungeon/func_80F46FB4. */
const void *const D_8015E860[6] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_behavior_variant + 0x100),
    ((u8 *)update_actor_behavior_variant + 0x208),
    ((u8 *)update_actor_behavior_variant + 0x270),
    ((u8 *)update_actor_behavior_variant + 0x30C),
    ((u8 *)update_actor_behavior_variant + 0x5DC),
    ((u8 *)update_actor_behavior_variant + 0x660)
};
