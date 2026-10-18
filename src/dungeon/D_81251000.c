#include "common.h"

extern void create_entity_and_initialize_placement(void);

/* entry; owner-unresolved. */
const u32 D_80170800[1] __attribute__((aligned(4))) = {
    (u32)create_entity_and_initialize_placement
};
