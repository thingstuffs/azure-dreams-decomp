#include "common.h"

extern void spawn_killer(void);

/* Exact entry span; owner-unresolved. */
const u32 D_80170800[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer
};
