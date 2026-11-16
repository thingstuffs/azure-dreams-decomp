#include "common.h"

extern void *spawn_viper_slot_d(s16, s16, s16, s16);

/* entry; owner: dungeon/func_80F45000. */
const void *const viper_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_viper_slot_d
};
