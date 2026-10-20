#include "common.h"

extern void update_directional_actor_effect(void);

/* Exact entry span; owner-unresolved. */
const u32 D_80024000[1] __attribute__((aligned(4))) = {
    (u32)update_directional_actor_effect
};
