#include "common.h"

extern void dungeonCreateEntityAndInitializePlacement(void);

/* entry; owner-unresolved. */
const u32 D_80170800[1] __attribute__((aligned(4))) = {
    (u32)dungeonCreateEntityAndInitializePlacement
};
