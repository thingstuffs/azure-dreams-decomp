#include "common.h"

extern void update_actor_movement_and_height(void);

/* vector; owner-unresolved. */
const u32 D_80170804[1] __attribute__((aligned(4))) = {
    (u32)update_actor_movement_and_height
};
