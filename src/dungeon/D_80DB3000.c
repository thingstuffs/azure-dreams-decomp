#include "common.h"

extern void move_expand_and_fade_effect_sprite(void);

/* entry; owner: dungeon/func_80DB3000. */
const u32 D_8014C800[1] __attribute__((aligned(4))) = {
    (u32)move_expand_and_fade_effect_sprite
};
