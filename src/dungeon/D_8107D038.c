#include "common.h"

extern void advance_actor_animation_and_reset_movement(void);

/* jump_table; owner: dungeon/func_8107F1D4. */
const u32 D_8014C838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0x11C),
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0x114),
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0x10C),
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0x124),
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0xCC),
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0xC4),
    (u32)((u8 *)advance_actor_animation_and_reset_movement + 0xBC)
};
