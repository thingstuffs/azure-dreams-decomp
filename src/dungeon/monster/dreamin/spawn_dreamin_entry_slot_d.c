#include "common.h"

extern void move_and_fade_effect_sprite(void);

/* entry; owner: dungeon/func_80DA1000. */
const u32 D_8015E800[1] __attribute__((aligned(4))) = {
    (u32)move_and_fade_effect_sprite
};
