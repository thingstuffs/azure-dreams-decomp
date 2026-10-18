#include "common.h"

extern void update_actor_sequence_third(void);

/* jump_table; owner: dungeon/func_80F95240. */
const u32 D_80164838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_sequence_third + 0x11C),
    (u32)((u8 *)update_actor_sequence_third + 0x114),
    (u32)((u8 *)update_actor_sequence_third + 0x10C),
    (u32)((u8 *)update_actor_sequence_third + 0x124),
    (u32)((u8 *)update_actor_sequence_third + 0xCC),
    (u32)((u8 *)update_actor_sequence_third + 0xC4),
    (u32)((u8 *)update_actor_sequence_third + 0xBC)
};
