#include "common.h"

extern void create_masked_effect_node(void);

/* entry; owner: dungeon/func_80F9F000. */
const u32 zu_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)create_masked_effect_node
};
