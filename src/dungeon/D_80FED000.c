#include "common.h"

extern void allocate_and_initialize_node(void);

/* entry; owner: dungeon/func_80FED000. */
const u32 D_8015E800[1] __attribute__((aligned(4))) = {
    (u32)allocate_and_initialize_node
};
