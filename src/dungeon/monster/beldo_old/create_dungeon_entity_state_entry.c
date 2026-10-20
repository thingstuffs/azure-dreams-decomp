#include "common.h"

extern void create_dungeon_entity_state(void);

/* entry; owner-unresolved. */
const u32 D_8016F800[1] __attribute__((aligned(4))) = {
    (u32)create_dungeon_entity_state
};
