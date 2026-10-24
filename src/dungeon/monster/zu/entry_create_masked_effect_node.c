#include "common.h"

extern void create_masked_effect_node(void);

/* entry; owner: dungeon/func_80F9F000. */
const void *const zu_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    create_masked_effect_node
};
