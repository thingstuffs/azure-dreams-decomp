#include "common.h"

extern void damp_effect_motion_and_fade_sprite(void);

/* entry; owner: dungeon/func_80DA7000. */
const u32 D_80158800[1] __attribute__((aligned(4))) = {
    (u32)damp_effect_motion_and_fade_sprite
};
