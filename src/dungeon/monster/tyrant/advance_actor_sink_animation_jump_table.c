#include "common.h"

extern void advance_actor_sink_animation(void);

/* jump_table; owner: dungeon/func_8106E45C. */
const void *const D_8015E878[8] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_sink_animation + 0x60),
    ((u8 *)advance_actor_sink_animation + 0x104),
    ((u8 *)advance_actor_sink_animation + 0x17C),
    ((u8 *)advance_actor_sink_animation + 0x1B4),
    ((u8 *)advance_actor_sink_animation + 0x60),
    ((u8 *)advance_actor_sink_animation + 0x104),
    ((u8 *)advance_actor_sink_animation + 0x17C),
    ((u8 *)advance_actor_sink_animation + 0x214)
};
