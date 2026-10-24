#include "common.h"

extern void update_actor_sequence_variant(void);

/* jump_table; owner: dungeon/func_80C004EC. */
const void *const D_8015E858[8] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_sequence_variant + 0x60),
    ((u8 *)update_actor_sequence_variant + 0x74),
    ((u8 *)update_actor_sequence_variant + 0xB8),
    ((u8 *)update_actor_sequence_variant + 0x198),
    ((u8 *)update_actor_sequence_variant + 0x26C),
    ((u8 *)update_actor_sequence_variant + 0x3D0),
    ((u8 *)update_actor_sequence_variant + 0x46C),
    ((u8 *)update_actor_sequence_variant + 0x4EC)
};
