#include "common.h"

extern void allocate_actor_parts(void);

/* entry; owner: dungeon/func_80F45000. */
const u32 viper_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)allocate_actor_parts
};
